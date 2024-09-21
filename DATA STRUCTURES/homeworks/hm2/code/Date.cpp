#include "Date.h"
#include <iostream>
using namespace std;

bool Date::leapYear()
{
    if (y%4==0)
    {
        if (y%100==0)
        {
            if (y%400==0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;

}
void Date::dayOfWeek(int &day)
{
    static int t[]={0,3,2,5,0,3,5,1,4,6,2,4};
    if(m<3){y-=1;}
    day=(y+y/4-y/100+y/400+t[m-1]+d)%7;
    if(m<3){y+=1;}
}
bool Date::setDate(int d,int m,int y)
{
    if(y>1899 && (d>=1&&d<=31)&&(m>=1&&m<=12)){

    if(m==1)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==2)
    {
        this->d=d;
        this->m=m;
        this->y=y;

        if(leapYear()==true)
        {
            if(d<=29)
            {
                return true;
            }
            else return false;
        }
        else
        {
            if(d<=28)
            {
                return true;
            }
            else return false;

        }


    }
    else if(m==3)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==4)
    {
        if(d<=30)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==5)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==6)
    {
        if(d<=30)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==7)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==8)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==9)
    {
        if(d<=30)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==10)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==11)
    {
        if(d<=30)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    else if(m==12)
    {
        if(d<=31)
        {
            this->d=d;
            this->m=m;
            this->y=y;
            return true;
        }
        else
            return false;

    }
    }
    return false;
}

