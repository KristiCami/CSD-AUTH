#include <iostream>
using namespace std;

class Student
{
public:
    Student();
    void set_aem(int aem){this->aem=aem;}
    void set_name(char*name){this->name=name;}
    void set_degree(float degree){this->degree=degree;}

    int get_aem(){return aem;}
    float get_degree()const {return degree;}
    char* get_name(){return name;}

    friend istream &operator>> (istream &, Student &);
    Student(const Student &other);

    void help();
private:
    int aem;
    char *name;
    float degree;
};

bool readStudent(char*,Student&);
bool writeToStudent(char*,Student&);
ostream &operator<< (ostream &, Student &);
bool operator>(const Student &,const Student &);

