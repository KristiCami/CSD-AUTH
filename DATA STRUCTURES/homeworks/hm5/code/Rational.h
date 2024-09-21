#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
using namespace std;
class Rational
{
public:
    Rational(int,int);
    Rational();//σε περιπτωση που κλυθει ο κενος κατασκευαστης ο ρητος αριθμος γινεται 0
    int gcd(int,int);
    Rational Simple();
    void set_m(int m){this->m=m;}
    void set_n(int n){this->n=n;}
    int get_m()const {return m;}
    int get_n()const {return n;}
    friend istream &operator>> (istream &, Rational &);
    Rational & operator *= (int);
    Rational & operator /= (const Rational &);
private:
    int m;
    int n;
};
ostream &operator<< (ostream &,Rational &);
bool operator==(const Rational &,const Rational &);
bool operator!=(const Rational &,const Rational &);
bool operator>(const Rational &,const Rational &);
bool operator<(const Rational &,const Rational &);
Rational operator+(const Rational &, const Rational &);
Rational operator-(const Rational &, const Rational &);
Rational &operator*(const Rational &,const Rational &);
Rational &operator/(const Rational &,const Rational &);

#endif // RATIONAL_H
