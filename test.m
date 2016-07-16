[flute,fs]=audioread('1.wav');
%soundsc(flute,fs)
%k=echo(flute,fs)
k=reverse(flute,fs)
%leftout(1165650);
%i=1;
%for n = 1: 19275
 %       leftout(i)= flute(i);
  %      if (mod (n,4) == 0)
   %         leftout(i)=leftout(i-1);
   % end
    %i=i+1;
%end
%soundsc(leftout,fs)