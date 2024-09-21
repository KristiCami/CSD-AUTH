clc; clear all ; close all;

f = @(x) 54.*x.^6 + 45.*x.^5 -102.*x.^4 - 69.*x.^3 +35.*x.^2 +16.*x -4 ;

x=(-2:0.1:2);
plot(x,f(x))

a=0.4;
b=0.9; 

k=0;
while abs(b-a) > eps*abs(b)
	x=a + (b-a).*rand(1,1);
    if sign(f(x)) == sign(f(b)) 
        b=x;
    else
        a=x;
    end 
k=k+1;
end

fprintf('The Root is : %f \n',a);
fprintf('No. of Iterations : %d\n',k-1);





