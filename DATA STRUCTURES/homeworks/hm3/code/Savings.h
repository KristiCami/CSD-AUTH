#ifndef Savings_h
#include "Account.h"
#define Savings_h

class Savings:public Account
{
public:
    Savings (char *,float);
    bool withdraw(float);
private:

};
#endif // Savings_h
