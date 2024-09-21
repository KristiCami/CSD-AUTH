clc; clear all ; close all;

syms x;
f= 54.*x.^6 + 45.*x.^5 -102.*x.^4 - 69.*x.^3 +35.*x.^2 +16.*x -4 ;
g=diff(f); 
h=diff(g);
epsilon = 5*10^-(5+1);
x0 = 0.9;

for i=1:100
     f0=vpa(subs(f,x,x0));
     f0_der=vpa(subs(g,x,x0)); 
     f0_2der=vpa(subs(h,x,x0));
     y=x0-1/(f0_der/f0-1/2*f0_2der/f0_der); 
err=abs(y-x0);
if err<epsilon 
break
end
x0=y;
end

y = y - rem(y,10^-5); 
fprintf('The Root is : %f \n',y);
fprintf('No. of Iterations : %d\n',i);