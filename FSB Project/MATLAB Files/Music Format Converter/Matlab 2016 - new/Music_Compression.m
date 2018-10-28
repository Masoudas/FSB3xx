function downsampled_music_object = Music_Compression()
%% Input parameters
global Music_Path
global File_number
global board_type
global seconds_from_start
global seconds_from_finish
global Compressed_Music_Path
global File_Format

% Other paramters
Fs_desired = 32e3;  % The new sampling frequency for the FSB board.
Music_Path_String = [Music_Path,'\',File_number,'.',File_Format];
Compressed_Music_Path_String = [Compressed_Music_Path,'\',File_number,'.wav'];

% Check to see if destination folders exist.
if (exist(Music_Path,'dir') ~= 7)
    msgbox('The specified music folder does not exist. Be sure the input path has the form "C:\Music" with all the characters. No unnecessary spaces should be added. Backslash is necessary.');
    error('Music path is incorrect');
elseif (exist(Compressed_Music_Path,'dir') ~= 7)
    msgbox('The specified destination folder does not exist. Be sure the input path has the form "C:\FSB Music" with all the characters. No unnecessary spaces should be added. Backslash is necessary.');
    error('Destination path is incorrect');
end

% Check to see if thr given file does belong to a board.
if (strcmp(board_type,'FSB310'))
    Check_File_Num_FSB310();  %% Return an error if file number is not between 00 to 150 for FSB310
elseif (strcmp(board_type,'FSB300'))
    Check_File_Num_FSB300();  %% Check if file numbers are valid for FSB300
else
    msgbox('Please choose a board type (FSB300 or FSB310)')
    error('No board type is given as input')
end

if (exist(Music_Path_String, 'file') ~= 2)
    msgbox('This file does not exist in the original folder. Make sure to put it in the folder, or do not enter this file number if you do not want it on the FSB board.')
    error('File does not exist');
end

% Reading the corresponding file
[original_music, Fs]= audioread(Music_Path_String); % Read the given audio file.

%% Main commands
if (isempty(seconds_from_start))
    seconds_from_start = 0;
end

if (isempty(seconds_from_finish))
    seconds_from_finish = 0;
end

if ((Fs*seconds_from_start) > length(original_music) || (Fs*seconds_from_finish) > length(original_music) || ((Fs*seconds_from_start)+(Fs*seconds_from_finish)) > length(original_music))
    msgbox('The seconds chosen to be eliminated from the beginning or the end exceeds the length of the file.')
    error('Seconds exceed');
else
    % Determine the start and finish samples based on the given sampling frequency
    start_sample = round(Fs*seconds_from_start);
    final_sample = round(Fs*seconds_from_finish);
end

% Cutting the music file from the begining and end
original_music = original_music(start_sample+1:(end-final_sample));

% Music filtering
% Generating the filter
if (Fs > Fs_desired)   % If the sampling rate of the input file equals the desired rate, ignore the filtering part.
    n_L = 8;                       % Order of lowpass filter
    Fn_L = Fs_desired/Fs;                % Normalized 3dB bandwidth (i.e, filter is set at 8kHz).
    [b_L,a_L] = butter(n_L,Fn_L);  % Butterworth lowpass filter
    
    % Filtering
    filtered_music = filter(b_L,a_L,original_music);
elseif (Fs < Fs_desired)
     msgbox('The quality of the chosen file is not good enough for the FSB board. Please change the music file.')
     error('File does not exist');
else 
    
    filtered_music = original_music;
end

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

function Check_File_Num_FSB310()
global File_number
switch (File_number)
    case ('00')
        
    case ('01')
        
    case ('02')
        
    case ('03')
        
    case ('04')
        
    case ('05')
        
    case ('06')
        
    case ('07')
        
    case ('08')
        
    case ('09')
        
    case ('10')
        
    case ('11')
        
    case ('12')
        
    case ('13')
        
    case ('14')
        
    case ('15')
        
    case ('16')
        
    case ('17')
        
    case ('18')
        
    case ('19')
        
    case ('20')
        
    case ('21')
        
    case ('22')
        
    case ('23')
        
    case ('24')
        
    case ('25')
        
    case ('26')
        
    case ('27')
        
    case ('28')
        
    case ('29')
        
    case ('30')
        
    case ('31')
        
    case ('32')
        
    case ('33')
        
    case ('34')
        
    case ('35')
        
    case ('36')
        
    case ('37')
        
    case ('38')
        
    case ('39')
        
    case ('40')
        
    case ('41')
        
    case ('42')
        
    case ('43')
        
    case ('44')
        
    case ('45')
        
    case ('46')
        
    case ('47')
        
    case ('48')
        
    case ('49')
        
    case ('50')
        
    case ('51')
        
    case ('52')
        
    case ('53')
        
    case ('54')
        
    case ('55')
        
    case ('56')
        
    case ('57')
        
    case ('58')
        
    case ('59')
        
    case ('60')
        
    case ('61')
        
    case ('62')
        
    case ('63')
        
    case ('64')
        
    case ('65')
        
    case ('66')
        
    case ('67')
        
    case ('68')
        
    case ('69')
        
    case ('70')
        
    case ('71')
        
    case ('72')
        
    case ('73')
        
    case ('74')
        
    case ('75')
        
    case ('76')
        
    case ('77')
        
    case ('78')
        
    case ('79')
        
    case ('80')
        
    case ('81')
        
    case ('82')
        
    case ('83')
        
    case ('84')
        
    case ('85')
        
    case ('86')
        
    case ('87')
        
    case ('88')
        
    case ('89')
        
    case ('90')
        
    case ('91')
        
    case ('92')
        
    case ('93')
        
    case ('94')
        
    case ('95')
        
    case ('96')
        
    case ('97')
        
    case ('98')
        
    case ('99')
        
    case ('100')
        
    case ('101')
        
    case ('102')
        
    case ('103')
        
    case ('104')
        
    case ('105')
        
    case ('106')
        
    case ('107')
        
    case ('108')
        
    case ('109')
        
    case ('110')
        
    case ('111')
        
    case ('112')
        
    case ('113')
        
    case ('114')
        
    case ('115')
        
    case ('116')
        
    case ('117')
        
    case ('118')
        
    case ('119')
        
    case ('120')
        
    case ('121')
        
    case ('122')
        
    case ('123')
        
    case ('124')
        
    case ('125')
        
    case ('126')
        
    case ('127')
        
    case ('128')
        
    case ('129')
        
    case ('130')
        
    case ('131')
        
    case ('132')
        
    case ('133')
        
    case ('134')
        
    case ('135')
        
    case ('136')
        
    case ('137')
        
    case ('138')
        
    case ('139')
        
    case ('140')
        
    case ('141')
        
    case ('142')
        
    case ('143')
        
    case ('144')
        
    case ('145')
        
    case ('146')
        
    case ('147')
        
    case ('148')
        
    case ('149')
        
    case ('150')
        
    otherwise
        msgbox('The given file number is not valid for FSB310. Refer to table for correct file numbers.')
        error('Invalid file number')
        
end
end

function Check_File_Num_FSB300()
global File_number
switch (File_number)
    case ('00')
        
    case ('01')
        
    case ('02')
        
    case ('03')
        
    case ('04')
        
    case ('05')
        
    case ('06')
        
    case ('07')
        
    case ('08')
        
    case ('09')
        
    case ('10')
        
    case ('11')
        
    case ('12')
        
    case ('13')
        
    case ('14')
        
    case ('15')
        
    case ('16')
        
    case ('17')
        
    case ('18')
        
    case ('19')
        
    case ('20')
        
    case ('21')
        
    case ('22')
        
    case ('23')
        
    case ('24')
        
    case ('25')
        
    case ('47')
        
    case ('48')
        
    case ('49')
        
    case ('50')
        
    case ('51')
        
    case ('52')
        
    case ('53')
        
    case ('54')
        
    case ('55')
        
    case ('56')
        
    case ('66')
        
    case ('67')
        
    case ('71')
        
    case ('79')
        
    case ('80')
        
    otherwise
        msgbox('The given file number is not valid for FSB300. Refer to table for correct file numbers.')
        error('Invalid file number')
        
end
end