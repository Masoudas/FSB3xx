%% Code initilization
close all
clear all
clc

%% Input parameters
global Music_Path;
global seconds_from_start;
global seconds_from_finish;
global File_Format


%% Main commands
if (isempty(seconds_from_start))
    seconds_from_start = 0;
end

if (isempty(seconds_from_finish))
    seconds_from_finish = 0;
end

% Reading the given audio file.
Music_Path_String = [Music_Path,'\',File_number,'.',File_Format];
[Music_vector, Fs] = audioread(Music_Path); 

% Determine the start and finish sample based on the given sampling frequency
start_sample = round(Fs*seconds_from_start);
final_sample = round(Fs*seconds_from_finish);


%% Finalization
% Play music
music_object = audioplayer(Music_vector(start_sample+1:end-final_sample),Fs,8);
play(music_object)
