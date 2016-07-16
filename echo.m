[flute,fs]=audioread('1.wav');
leftout = flute;
N=10000; %echo starts after N samples
for n = N+1:length(flute)
    leftout(n)=flute(n)+ 0.6*flute(n-N);
end
soundsc(leftout,fs);
t= 1: length(flute);
subplot(2,1,1),plot(t,flute),title('Original Sound');
subplot(2,1,2),plot(t,leftout),title('Echo Sound');
