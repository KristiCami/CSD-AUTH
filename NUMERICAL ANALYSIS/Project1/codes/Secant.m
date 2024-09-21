clc; clear all ; close all;

f =@(x)(14.*x.*exp(x-2)-12.*exp(x-2)-7.*x.^3+20.*x.^2-26.*x+12);

a=0;
b=1; 
%b=3;

k=0;
while abs(b-a) > eps*abs(b)
    c=a;
    a=b;
    b = b + (b-c)/(f(c)/f(b)-1);
    k=k+1;
end

fprintf('The Root is : %f \n',c);
fprintf('No. of Iterations : %d\n',k);


