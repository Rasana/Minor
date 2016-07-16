[left,fs]=audioread('1.wav');
leftout = zeros(size(left));

for n = 1:length(left)
    N=(length(left)-n);
    leftout(n)=left(N+1);
end

soundsc(leftout,fs);

t=  1:length(leftout);
subplot(2,1,1),plot(t,left);
subplot(2,1,2),plot(t,leftout);
