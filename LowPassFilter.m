filename = '1.wav';
[y,fs] = audioread(filename);
%sound(20*y,fs); %play sound
t= 1:length(y);

alpha = 0.1;
xMan=zeros(size(y));

for i =2:length(y)
xMan(i)=alpha*(y(i)+(1-alpha)*xMan(i-1));
end;

figure;
subplot(2,1,1),plot(t,xMan),grid on;
title('LPF with Alpha = 0.1');
subplot(2,1,2),plot(t,2*y),grid on;
sound(20*xMan,fs);

