function downsampled_music_object = Music_Compression()
%% Input parameters
global Music_Path;
global File_number
global seconds_from_start;
global seconds_from_finish;
global Compressed_Music_Path
global File_Format

% Other paramters
Fs_desired = 16e3;  % The new sampling frequency for the FSB board.
Music_Path_String = [Music_Path,'\',File_number,'.',File_Format];
Compressed_Music_Path_String = [Compressed_Music_Path,'\',File_number,'.wav'];

% Reading the corresponding file
[original_music, Fs]= audioread(Music_Path_String); % Read the given audio file.

%% Main commands
if (isempty(seconds_from_start))
    seconds_from_start = 0;
end

if (isempty(seconds_from_finish))
    seconds_from_finish = 0;
end

% Determine the start and finish samples based on the given sampling frequency
start_sample = round(Fs*seconds_from_start);
final_sample = round(Fs*seconds_from_finish);

% Cutting the music file from the begining and end
original_music = original_music(start_sample+1:(end-final_sample));

% Music filtering
% Generating the filter
n_L = 8;                       % Order of lowpass filter
Fn_L = Fs_desired/Fs;                % Normalized 3dB bandwidth (i.e, filter is set at 8kHz).
[b_L,a_L] = butter(n_L,Fn_L);  % Butterworth lowpass filter

% Filtering
filtered_music = filter(b_L,a_L,original_music);


%% Upsampling and downsampling
% Sampling rate change
[upsample_rate, downsample_rate]=rat(Fs_desired/Fs);  % Determine the upsample and downsampling rates.
upsampled_music = zeros(1,upsample_rate*length(original_music)); % This vector contains the upsampled music content.
for i = 1:upsample_rate
    upsampled_music(i:upsample_rate:end) = filtered_music;
end
downsampled_music = upsampled_music(1:downsample_rate:end);


%% Finalization
audiowrite(Compressed_Music_Path_String,downsampled_music,Fs_desired,'BitsPerSample',8) % Write the new music file
downsampled_music_object = audioplayer(downsampled_music,Fs_desired,8); % Prepare to play the new music
end
