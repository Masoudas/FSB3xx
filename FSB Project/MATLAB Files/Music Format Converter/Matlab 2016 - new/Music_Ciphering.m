function ciphered_music = Music_Ciphering(music_vector)

      music_vector_temp = music_vector; % Save a template for music vector.
      remainder_vector = rem(music_vector,16);  % Compute the lower 4 bits of each sample.
      music_vector_temp = (music_vector_temp - remainder_vector)/16;    % MSB bits are moved to the LSB bits.
      ciphered_music = remainder_vector*16+music_vector_temp;   % Bit swapping is completed here.
      ciphered_music = bitcmp(ciphered_music);    % Negate all bits here.
end
