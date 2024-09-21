#include "Savings.h"

#include <iostream>
using namespace std;

Savings::Savings(char *a,float b):Account(a,b){}

bool Savings::withdraw(float amount)
{
    static int counter=0;
    //cout<<"BALNCE IS: "<<balance<<endl;
    //cout<<"COUNTER IS: "<<counter<<endl;

    if(counter<=3)
    {
        if((balance-amount)>=0)
        {
            balance-=amount;
            counter++;
            return true;
        }
        else
        {
            counter++;
            return false;
        }
    }
    return false;

}
