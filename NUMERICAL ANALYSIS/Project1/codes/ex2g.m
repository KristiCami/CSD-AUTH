clc; clear all ; close all;

f = @(x) 54.*x.^6 + 45.*x.^5 -102.*x.^4 - 69.*x.^3 +35.*x.^2 +16.*x -4 ;
a = -2;
b = 1;
err = 0.0001;

x(1)=-2; x(2)=0; x(3)=2;

i=2;
while abs( x(i-1)-x(i) ) >= err
    i=i+1;
    x(i+1) = x(i-2)*f(x(i-1))*f(x(i))/((f(x(i-2))-f(x(i-1)))*(f(x(i-2))-f(x(i))))+ ...
             x(i-1)*f(x(i-2))*f(x(i))/((f(x(i-1))-f(x(i-2)))*(f(x(i-1))-f(x(i))))+ ...
             x(i)*f(x(i-2))*f(x(i-1))/((f(x(i))-f(x(i-2)))*(f(x(i))-f(x(i-1))));
         
    xx(i,1) = x(i+1);
    ii(i,1) = i;
         
end

disp(['Root X = ' num2str(x(i+1)) ' ,Iterations = ' num2str(i) ]);