%% Input parameters
global Compressed_Music_Path   % The path of the attached file.

% Other parameters
flash_page_size = 528;  % Page size of flash memory used in FSB.

% Generating the indexes corresponding to the file numbers.
for i = 1:40
    if (i<10)
        Index(i,:) = ['0',num2str(i)];
    else
        Index(i,:) = num2str(i);
    end
        initial_page_strings(i,:) = strcat('<param',Index(i,1:2),'1>');
        final_page_strings(i,:) = strcat('<param',Index(i,1:2),'2>');
end
Flash_vector = [];  % Denotes the content of the music file to be saved in flash memory.


%% Main Command
% Create the continuous music file
for i = 1:length(Index)
    Music_Path_String = [Compressed_Music_Path,'\',Index(i,:),'.wav'];
    if (exist(Music_Path_String, 'file') == 2)  % If this file exists,
    [Music_vector, Fs] = audioread(Music_Path_String); % Read the given audio file.
    Initial_page_index = round(length(Flash_vector)/flash_page_size+1); % Initial page index for the current file is derived based on the size of the current flash file.
    Final_page_index = round(Initial_page_index + length(Music_vector)/flash_page_size);   % Final page index is derived based on the length of the music file to be attached.
    else % Otherwise generate a null music.
    Music_vector = 0;
    Initial_page_index = 0; % Set the page size to zero
    Final_page_index = 0;  
    end    
    Flash_vector = [Flash_vector; Music_vector];    % Appended the current file to the flash file.
    
    entries(2*i-1) = struct('param',initial_page_strings(i,:),'value',Initial_page_index);  % Assign the parameters to be replaced in the header file.
    entries(2*i) = struct('param',final_page_strings(i,:),'value',Final_page_index); 
end


%% Finalization
% Generating the music file
Attached_Music_Path_String = [Compressed_Music_Path,'\Flash File.wav'];
audiowrite(Attached_Music_Path_String,Flash_vector,Fs,'BitsPerSample',8)

% Generating the corresponding header file
template = [pwd,'\Music_Pages.h'];
outfile = [Compressed_Music_Path,'\Music_Pages.h'];
replaceparams(template,outfile,entries);



