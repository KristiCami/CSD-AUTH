
#ifndef Date_h
#define Date_h
class Date
{
public:
    int getDay(){return d;};
    int getMonth(){return m;};
    int getYear(){return y;};
    //implementation file
    bool setDate(int,int,int);
    bool leapYear();
    void dayOfWeek(int&);
private:
    int d,m,y;
};
#endif // Date_h
