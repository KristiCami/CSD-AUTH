#include "Rational.h"
#include <cmath>

#include <iostream>
using namespace std;

Rational::Rational(int m,int n)
{
    int GCD=gcd(m,n);
    this->m=m/GCD;
    this->n=n/GCD;

}
Rational::Rational()
{
    this->m=0;
    this->n=1;
}

int Rational::gcd(int a, int b)
{
    if (a == 0)
       return b;
    if (b == 0)
       return a;

    if (a == b)
        return a;

    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

Rational Rational::Simple()
{
    //cout<<"O MKD tou "<<this->m<<" kai tou "<<this->n<<" einai "<<gcd(this->m,this->n)<<endl;
    int GCD=gcd(this->m,this->n);
    this->m/=GCD;
    this->n/=GCD;
    return *this;

}

istream &operator>>(istream &i, Rational &obj)
{
    int m,n;

    i>>m>>n;
    int GCD=obj.gcd(m,n);
    obj.set_m(m/GCD);
    obj.set_n(n/GCD);

    return i;
}

ostream &operator<<(ostream &o, Rational &obj)
{
    o<<obj.get_m()<<"/"<<obj.get_n();
    return o;
}

bool operator==(const Rational &a,const Rational &b)
{
    return (a.get_m()*b.get_n())==(a.get_n()*b.get_m());
}

bool operator!=(const Rational &a,const Rational &b)
{
    return !(a==b);
}

bool operator>(const Rational &a,const Rational &b)
{
    return((1.0*a.get_m())/a.get_n())>(b.get_m()/b.get_n());
}

bool operator<(const Rational &a,const Rational &b)
{
    return b>a;
}

Rational operator+(const Rational &a, const Rational &b)
{

    Rational sum;

    sum.set_m(a.get_m() * b.get_n() + a.get_n() * b.get_m() );
    sum.set_n(a.get_n() * b.get_n());

    return sum;
}

Rational operator-(const Rational &a, const Rational &b)
{

    Rational sub;
    //cout<<"KOITA EDW"<<a.get_n() * b.get_n()<<endl;
    sub.set_m(a.get_m() * b.get_n() - a.get_n() * b.get_m() );
    sub.set_n(a.get_n() * b.get_n());
    //cout<<"KOITA EDW"<<sub.get_n()<<endl;

    return sub;
}

Rational &operator*(const Rational &a,const Rational &b)
{
    Rational *r;
    r = new Rational();

    r->set_m(a.get_m() * b.get_m());
    r->set_n(a.get_n() * b.get_n());

    int GCD = r->gcd(r->get_m(),r->get_n());

    r->set_m(r->get_m()/GCD);
    r->set_n(r->get_n()/GCD);

    return *r;
}

Rational &operator/(const Rational &a,const Rational &b)
{
    Rational *r;
    r = new Rational();

    r->set_m(a.get_m() * b.get_n());
    r->set_n(a.get_n() * b.get_m());

    int GCD = r->gcd(r->get_m(),r->get_n());

    r->set_m(r->get_m()/GCD);
    r->set_n(r->get_n()/GCD);

    return *r;
}

Rational & Rational::operator *= (int other)
{
    this->m *= other;
    //this->n *= other;
    return *this;

}
Rational & Rational::operator /= (const Rational &other)
{
    this->m *= other.n;
    this->n *= other.m;

    int GCD=gcd(this->m,this->n);
    this->m/=GCD;
    this->n/=GCD;


    return *this;

}

