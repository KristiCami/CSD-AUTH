#include "CreditCard.h"

#include <iostream>
using namespace std;
#include <cmath>

CreditCard::CreditCard(char *a,float b,float c):Account (a,b)
{
    LIMIT=c;
}

bool CreditCard::withdraw(float amount)
{

    int sum=balance-amount;

    if (sum>=(-LIMIT))
    {
        balance-=amount;
        return true;
    }
    return false;

}

