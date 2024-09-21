#ifndef Vector_h
#define Vector_h
#include <iostream>
using namespace std;
class Vector
{
public:
    Vector(){x=y=0;}
    Vector(double x,double y){this->x=x;this->y=y;}
    void Setx(double x){this->x=x;}
    void Sety(double y){this->y=y;}
    double Getx(){return x;}
    double Gety(){return y;}

    double magnitude();
    double angle();
    double angleD();
    void print(){cout<<"("<<x<<","<<y<<")"<<endl<<magnitude()<<endl<<angleD()<<endl;}

    void multiply(double);
    Vector add(Vector&);
private:
    double x,y;
};
#endif // Vector_h
