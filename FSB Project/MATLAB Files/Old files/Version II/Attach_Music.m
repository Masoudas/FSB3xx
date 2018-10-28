%% Input parameters
global Compressed_Music_Path   % The path of the attached file.

% Other parameters
flash_page_size = 528;  % Page size of flash memory used in FSB.
Page_index = uint8(zeros(484,1));   % The addresses of the first and last page of each message/music in 8-bit form.

% Generating the indexes corresponding to the file numbers.
for i = 1:40
    if (i<10)
        Index(i,:) = ['0',num2str(i)];
    else
        Index(i,:) = num2str(i);
    end
end
Flash_vector = [];  % Denotes music samples altogether.


%% Main Command
% Create the continuous music file
for i = 1:length(Index)
    Music_Path_String = [Compressed_Music_Path,'\',Index(i,:),'.wav'];
    if (exist(Music_Path_String, 'file') == 2)  % If this file exists,
        [Music_vector, Fs] = audioread(Music_Path_String); % Read the given audio file.
        Initial_page = ceil(length(Flash_vector)/flash_page_size)+2; % Initial page index for the current file is derived based on the size of the current flash file 
                                                                     % First page is reserved for saving the page indexes.
                                                                     % Second page is reserved for beep.
        Final_page = floor(Initial_page + length(Music_vector)/flash_page_size);   % Final page index is derived based on the length of the music file to be attached.
                                                                                   % First page is reserved for saving the page indexes. 
        Page_index(4*i-3,1) = floor(Initial_page/256);    % The most significant bits of initial page.
        Page_index(4*i-2,1) = rem(Initial_page,256);      % The least significant bits of initial page.
        Page_index(4*i-1,1) = floor(Final_page/256);      % The most significant bits of final page.
        Page_index(4*i-0,1) = rem(Final_page,256);        % The least significant bits of final page.
    else % Otherwise generate a null music.
        Music_vector = 0;
        Page_index((4*i-3):4*i,1) = 0; % Set the page size to zero
    end
    Flash_vector = [Flash_vector; Music_vector];    % Appended the current file to the flash file.
end

% From the final vector saved in the flash
Flash_vector = (Flash_vector*0.5+0.5)*255;  % Resize the music samples to 255;
Flash_Data = [Page_index; uint8(Flash_vector)];   % The data to be programmed in the flash memory.

%% Finalization
% Generating the music file
Attached_Music_Path_String = [Compressed_Music_Path,'\Flash File.wav'];
audiowrite(Attached_Music_Path_String,Flash_Data,Fs,'BitsPerSample',8)




