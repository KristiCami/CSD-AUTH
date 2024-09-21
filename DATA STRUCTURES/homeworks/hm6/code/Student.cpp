#include "Student.h"
#include <fstream>
#include <cstring>

#include <iostream>
using namespace std;


bool readStudent(char*s,Student &a)
{
    ifstream ifs;
    ifs.open(s);

    int p;
    float d;
    char *onoma;

    onoma = new char[strlen(s)+1];

    if(ifs.is_open())
    {

        ifs>>p;
        a.set_aem(p);

        ifs>>onoma;
        a.set_name(onoma);

        ifs>>d;
        a.set_degree(d);
        return 1;
    }
    else
    {
        return 0;
    }
}

bool writeToStudent(char *s,Student &a)
{
    ofstream ofs;
    ofs.open(s,ios::out);

    //cout<<"To a einai: "<<a<<endl;

    if (ofs.is_open())
    {
        ofs<<a.get_aem()<<" "<<a.get_name()<<" "<<a.get_degree();
        ofs.close();
        return 1;
    }
    else
    {
        return 0;
    }

}

ostream &operator<<(ostream &o, Student &v)
{
    o<<v.get_aem()<<" "<<v.get_name()<<" "<<v.get_degree();
    return o;
}


Student::Student()
{
    aem=0;
    name=nullptr;
    degree=0.0;
}

istream &operator>>(istream &i, Student &v)
{
    int k;
    i>>k;
    v.set_aem(k);

    char *s;
    s=new char[50];
    i>>s;
    v.set_name(s);

    double t;
    i>>t;
    v.set_degree(t);
    return i;
}

bool operator>(const Student &a,const Student &b)
{
    if (a.get_degree()>b.get_degree())
        return 1;
    else
        return 0;
}
Student::Student(const Student &other)
{
    aem=other.aem;
    degree=other.degree;

    name= new char[strlen(other.name)+1];
    strcpy(name,other.name);
}
