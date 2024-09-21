#ifndef CreditCard_h
#include "Account.h"
#define CreditCard_h

class CreditCard:public Account
{
public:
    CreditCard (char *,float,float);
    bool withdraw(float);
private:
    float LIMIT;
};
#endif // CreditCard_h
