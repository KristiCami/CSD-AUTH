#include "Bag.h"
#include <iostream>

using namespace std;

Bag::Bag()
{
    Size=0;
    maxSize=10;
    data = new string[10];

    ap = new int[10];
    SizeAp=0;
    maxSizeAp=10;
}
void Bag::delete_data()
{
    delete [] data;
    delete [] ap;
    ap=nullptr;
    data=nullptr;
    SizeAp=0;
    maxSizeAp=0;
    Size=0;
    maxSize=0;
}

bool Bag::push_back (string k)
{
    int pos;

    if (maxSize==Size)
    {
        if(!moreMemory(Size+5))
            cout<<"memory error"<<endl;
    }

    if (maxSizeAp==SizeAp)
    {
        if(!moreMemory(Size+5))
            cout<<"memory error"<<endl;
    }

    if(!Search(k,pos))
    {
        data[Size]=k;
        Size++;

        ap[SizeAp]=1;
        SizeAp++;
    }
    else
    {
        ap[pos]++;

    }
    return true;
}

//Η συγκεκρημενη συναρτηση αυξανει το μεγεθος του δυναμικου πινακα data και ap
bool Bag::moreMemory(int n)
{
    string *p;
    int *k;
    p=new string [n];
    k = new int[n];

    if (p==NULL || k==NULL)
        return false;
    for(int i=0;i<Size;i++)
    {
        p[i]=data[i];
    }
    delete[] data;
    data=p;
    maxSize=n;
    for(int i=0;i<SizeAp;i++)
    {
        k[i]=ap[i];
    }
    delete[] ap;
    ap=k;
    maxSizeAp=n;
    return true;
}

//Αναζητηση λεξεις και επιστροφη θεσης στην παραμετρο p
bool Bag::Search(string str,int &p)
{
    for(int i=0;i<Size;i++)
        if(str==data[i])
        {
            p=i;
            return true;
        }
    return false;
}

void Bag::show()
{
    cout<<"--------------"<<endl;
    for (int i=0;i<Size;i++)
        cout<<i+1<<":"<<" "<<data[i]<<" "<<ap[i]<<endl;
    cout<<"--------------"<<endl;
        }
