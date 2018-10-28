function replaceparams(template,outfile,entries)
% REPLACEPARAMS Replaces a template file's parameters with given values and
% stores the result in an output file.
    % Replaces a template file's parameters with given values and stores the
    % result in an output file.
    % Parameters:
    % template: Template file.
    % outfile:  Output file.
    % entries:  Array of structs with populated fields "param" and "value".

%% Preparing.
% Converting numeric parameter values to strings.
strentries=entries;
for j=1:length(strentries)
    if(isnumeric(strentries(j).value))
        strentries(j).value=num2str(strentries(j).value);
    end
end
    
%% Opening input/output files.
f1=fopen(template,'rt','n','UTF-8');
f2=fopen(outfile,'wt','n','UTF-8');

%% Reading, replacing, and writing.
tline=fgetl(f1);
while ischar(tline)        
    for j=1:length(strentries)
        tline=strrep(tline,strentries(j).param,strentries(j).value);
    end
    fprintf(f2,'%s\n',tline);
    tline = fgetl(f1);
end

%% Closing files.
fclose(f1);
fclose(f2);
end