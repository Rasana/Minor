filename = '1.wav';
[y,fs] = audioread(filename);
x=zeros(size(y));
t= 1:length(y);
%sound(20*y,fs); %play sound

p=7;
q=5;
r=q;
j=1;

%track values of j and thus signals
jc=zeros(size(y));

for i =1:length(y)
    if i<r
        x(j)=y(i);
        j=j+1;
        jc(i)=j;
    else
        i=p-q+1;
        r=r+p;
    end
end;

subplot(2,1,1),plot(t,x),grid on;
title('FastSpeed 7/5');
subplot(2,1,2),plot(t,y),grid on;
sound(20*x,fs);

x(1:15)
y(2:20)