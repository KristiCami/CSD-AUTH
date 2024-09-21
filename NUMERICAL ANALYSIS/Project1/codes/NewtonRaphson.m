clc; clear all ; close all;

syms x;
f=14.*x.*exp(x-2)-12.*exp(x-2)-7.*x.^3+20.*x.^2-26.*x+12; 
g=diff(f); 
epsilon = 5*10^-(5+1);
%x0 = 0;
x0 = 3;

for i=1:100
     f0=vpa(subs(f,x,x0)); 
     f0_der=vpa(subs(g,x,x0)); 
  y=x0-f0/f0_der; 
err=abs(y-x0);
if err<epsilon 
break
end
x0=y;
end

y = y - rem(y,10^-5); 
fprintf('The Root is : %.5f \n',y);
fprintf('No. of Iterations : %d\n',i);