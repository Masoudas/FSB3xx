%% Code initilization
close all
clear all
clc

%% Input parameters
Music_Path = 'C:\Music\02F02.wav';
Compressed_Music_Path = 'C:\Music\39MA11.wav';

% Start and finish of music file
seconds_from_start = 0;
seconds_from_finish = 0;

% Sampling rate change
upsample_rate = 1;
downsample_rate = 1;


%% Main commands
% Determine start and finish sample based on given sampling frequency
[original_music, Fs]= audioread(Music_Path); % Read the given audio file.
Fs

start_sample = round(Fs*seconds_from_start);
final_sample = round(Fs*seconds_from_finish);


%% Upsampling and downsampling
% Cutting the music file from the begining and end
original_music = original_music(start_sample+1:(end-final_sample));

upsampled_music = zeros(1,upsample_rate*length(original_music)); % This vector contains the upsampled music content.

for i = 1:upsample_rate
    upsampled_music(i:upsample_rate:end) = original_music;
end
downsampled_music = upsampled_music(1:downsample_rate:end);


%% Finalization
audiowrite(Compressed_Music_Path,downsampled_music,round(Fs*upsample_rate/downsample_rate),'BitsPerSample',8) % Write the new music file
round(Fs*upsample_rate/downsample_rate)
downsampled_music_object = audioplayer(downsampled_music,round(Fs*upsample_rate/downsample_rate),8); % Prepare to play the new music
play(downsampled_music_object) % Play the new music