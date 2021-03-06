%% Input parameters
global Compressed_Music_Path   % The path of the attached file.
Initial_page = 0; % Denotes the initial page of current message/music file
Final_page = 0; % Denotes the final page of current message/music file

% Other parameters
flash_page_size = 528;  % Page size of flash memory used in FSB.
Page_index = uint8(zeros(484,1));   % The addresses of the first and last page of each message/music in 8-bit form.

Flash1_vector = [];  % Denotes music samples altogether to be put in the first flash memory.
Flash2_vector = [];  % Denotes music samples altogether to be put in the second flash memory.


%% Main Command
% Create the continuous music file
for i = 1:150
    % Generating the indexes corresponding to the file numbers.
    if (i<11)
        Index = ['0',num2str(i-1)];
    else
        Index = num2str(i-1);
    end
    Music_Path_String = [Compressed_Music_Path,'\',Index,'.wav'];
    
    if (exist(Music_Path_String, 'file') == 2)  % If this file exists,
        [Music_vector, Fs] = audioread(Music_Path_String); % Read the given audio file.
        Initial_page = ceil((length(Flash1_vector)+length(Flash2_vector))/flash_page_size)+1; % Initial page index for the current file is derived based on the size of the current flash file
                                                                                              % First page is reserved for saving the page indexes.
        Final_page = floor(Initial_page + length(Music_vector)/flash_page_size);   % Final page index is derived based on the length of the music file to be attached.
                                                                                   % First page is reserved for saving the page indexes.
        
        Page_index(4*i-3,1) = floor(Initial_page/256);    % The most significant bits of initial page.
        Page_index(4*i-2,1) = rem(Initial_page,256);      % The least significant bits of initial page.
        Page_index(4*i-1,1) = floor(Final_page/256);      % The most significant bits of final page.
        Page_index(4*i-0,1) = rem(Final_page,256);        % The least significant bits of final page.
    else % Otherwise generate a null music.
        Music_vector = [];
        Page_index((4*i-3):4*i,1) = 0; % Set the page size to zero.
    end
    
    % Appended the current file to the flash file.
    if (Final_page < 8100)  % If there is still room in flash one.
        Flash1_vector = [Flash1_vector; Music_vector];
    elseif (Initial_page < 8100 && Final_page >= 8100 && ~isempty(Music_vector)) % If a file has to be divided between flash one and two
        remainder_length_flash_one = 8099 - Initial_page;
        Flash1_vector = [Flash1_vector; Music_vector(1:remainder_length_flash_one*flash_page_size)];
        Flash2_vector = [Flash2_vector; Music_vector(flash_page_size*remainder_length_flash_one+1:end)];
    else                    % There is need for the second flash.
        Flash2_vector = [Flash2_vector; Music_vector];
    end
end

% Show a dialog-box denoting how many memories are required.
if (Final_page < 8100)
    msgbox('One memory chip on FSB board is enough!')
elseif (Final_page >= 8100 && Final_page < 8300)
    msgbox('Two memory chips are required! However less than 100kByte of second memory is used. Try shortening the files if possible.')
elseif (Final_page >= 8300 && Final_page < 16200)
    msgbox('Two memory chip on FSB board are required!')
else
    msgbox('The files are larger than the capacity of both FSB flash memories combined!')
end


%% Finalization
% Generating the music file
if (Final_page <= 16200)
    % From the final vector saved in the flash
    Flash1_vector = (Flash1_vector*0.5+0.5)*255;  % Resize the music samples to 255;
    Flash1_Data = [Page_index; uint8(Flash1_vector)];   % The data to be programmed in the flash memory.
    Attached_Music_Path_String = [Compressed_Music_Path,'\Flash One File.wav'];
    audiowrite(Attached_Music_Path_String,Flash1_Data,Fs,'BitsPerSample',8);
    
    if (Final_page >= 8100) % If there is data to be recorded on the second memory.
        Flash2_vector = (Flash2_vector*0.5+0.5)*255;  % Resize the music samples to 255;
        Flash2_Data = uint8(Flash2_vector);   % The data to be programmed in the flash memory.
        Attached_Music_Path_String = [Compressed_Music_Path,'\Flash Two File.wav'];
        audiowrite(Attached_Music_Path_String,Flash2_Data,Fs,'BitsPerSample',8);
    end
end


