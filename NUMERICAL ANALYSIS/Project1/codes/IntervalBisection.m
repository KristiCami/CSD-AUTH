clc; clear all ; close all;

f =@(x)(14.*x.*exp(x-2)-12.*exp(x-2)-7.*x.^3+20.*x.^2-26.*x+12);

x=(0:0.1:3);
plot(x,f(x));

a=1;
%b=1; 
b=3;

k=0;
while abs(b-a) > eps*abs(b)
	x=(a+b)/2;
    if sign(f(x)) == sign(f(b)) 
        b=x;
    else
        a=x;
    end 
k=k+1;
end

fprintf('The Root is : %.5f \n',a);
fprintf('No. of Iterations : %d\n',k);





