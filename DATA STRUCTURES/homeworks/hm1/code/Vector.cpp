#include "Vector.h"
#include <cmath>
double Vector::magnitude(){return sqrt(x*x+y*y);}

void Vector::multiply(double f){x=x*f;y=y*f;}

double Vector::angle() {return atan(y/x);}

double Vector::angleD(){return (angle()*180)/(M_PI);}

Vector Vector::add(Vector &obj)
{
    Vector b;
    b.x=obj.x+x;
    b.y=obj.y+y;
    return b;
}
