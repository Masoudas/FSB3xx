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
% Check to see if destination folders exist.
if (exist(Compressed_Music_Path,'dir') ~= 7)
    msgbox('The specified destination folder does not exist. Be sure the input path has the form "C:\FSB Music" with all the characters. No unnecessary spaces should be added. Backslash is necessary.');
    error('Destination path is incorrect');
end

% Delete the already existing files
delete([Compressed_Music_Path,'\Flash One File.wav']);
delete([Compressed_Music_Path,'\Flash Two File.wav']);

% Check if all files have the right format.
for i = 1:150
    if (i<11)
        Index = ['0',num2str(i-1)];
    else
        Index = num2str(i-1);
    end
    
    Music_Path_String = [Compressed_Music_Path,'\',Index,'.wav'];
    if (exist(Music_Path_String, 'file') == 2)  % If this file exists,
        audio_info = audioinfo(Music_Path_String);
        
        if ((audio_info.SampleRate ~= 16e3) || (audio_info.BitsPerSample ~= 8) || ~strcmp(audio_info.CompressionMethod,'Uncompressed'))
            msgbox(strcat('File "', Index,'" has not been modified to FSB board format. Modiy this file using the edit box of GUI.'));
            error('File has not been modified');
        end
    end
end

% Create the continuous music file
for i = 1:120
    % Generating the indexes corresponding to the file numbers.
    if (i<11)
        Index = ['0',num2str(i-1)];
    else
        Index = num2str(i-1);
    end
    Music_Path_String = [Compressed_Music_Path,'\',Index,'.wav'];
    
    if (exist(Music_Path_String, 'file') == 2)  % If this file exists,
        [Music_vector, Fs] = audioread(Music_Path_String); % Read the given audio file.
        zero_pad = (ceil(length(Music_vector)/528)*528) - length(Music_vector);    % The number of zeros to be padded at the end of current music (to make it a multiple of 528)
        Music_vector = [Music_vector; ones(zero_pad,1)];
        
        Initial_page = Final_page+1; % Initial page index for the current file is derived based on the size of the current flash file
        Final_page = Initial_page+length(Music_vector)/flash_page_size - 1;   % Final page index is derived based on the length of the music file to be attached.
        
        Page_index(4*i-3,1) = floor(Initial_page/256);    % The most significant bits of initial page.
        Page_index(4*i-2,1) = rem(Initial_page,256);      % The least significant bits of initial page.
        Page_index(4*i-1,1) = floor(Final_page/256);      % The most significant bits of final page.
        Page_index(4*i-0,1) = rem(Final_page,256);        % The least significant bits of final page.
        
    else % Otherwise generate a null music.
        Final_page = Final_page+1;
        Initial_page = Final_page;
        Music_vector = ones(528,1) ;
        Page_index(4*i-3,1) = floor(Final_page/256); % The length of null page is one, starting from the last page.
        Page_index(4*i-2,1) = rem(Final_page,256);
        Page_index(4*i-1,1) = floor(Final_page/256);
        Page_index(4*i-0,1) = rem(Final_page,256);
    end
    
    % Append the current file to the flash file.
    if (Final_page < 8192)  % If there is still room in flash one.
        Flash1_vector = [Flash1_vector; Music_vector];
    elseif (Initial_page < 8100 && Final_page > 8192 && ~isempty(Music_vector)) % If a file has to be divided between flash one and two
        remainder_length_flash_one = 8192 - Initial_page;
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
    Flash1_vector = uint8(ceil((Flash1_vector*0.5+0.5)*255));  % Resize the music samples to 255;
    Flash1_ciphered = Music_Ciphering(Flash1_vector);
    Flash1_Data = [Page_index; Flash1_ciphered];   % The data to be programmed in the flash memory.
    Attached_Music_Path_String = [Compressed_Music_Path,'\Flash One File.wav'];
    audiowrite(Attached_Music_Path_String,Flash1_Data,Fs,'BitsPerSample',8);
    
    if (Final_page >= 8100) % If there is data to be recorded on the second memory.
        Flash2_vector = uint8(ceil((Flash2_vector*0.5+0.5)*255));  % Resize the music samples to 255;
        Flash2_ciphered = Music_Ciphering(Flash2_vector);
        Flash2_Data = Flash2_ciphered;   % The data to be programmed in the flash memory.
        Attached_Music_Path_String = [Compressed_Music_Path,'\Flash Two File.wav'];
        audiowrite(Attached_Music_Path_String,Flash2_Data,Fs,'BitsPerSample',8);
    end
end


