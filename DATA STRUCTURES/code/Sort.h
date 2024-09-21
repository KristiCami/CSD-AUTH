#ifndef SORT_H
#define SORT_H

#define InitialSize 10
#define Increment 5

#include <iostream>
using namespace std;

template <class X> class Sort
{
    public:
        //κατασκευαστης
        Sort()
        {
            qsize=0;
            maxSize = InitialSize;
            data = new X[maxSize];
            if (data==NULL)
                maxSize=0;

            SizeAp=0;
            maxSizeAp=InitialSize;
            ap = new int[maxSizeAp];
            if (ap==NULL)
                maxSize=0;
        }
        //καταστροφεας
        ~Sort()
        {
            delete[] data;
            delete[] ap;
        }
        //ταξινομημενη εισαγωγη καθε λεξεις
        bool enQueue(X key)
        {
            //Ελεγχος αν ο πινακας ειναι γεματος
            if (qsize==maxSize)
            {
                X *temp;
                temp = new X[maxSize+Increment];
                if (temp!=NULL)
                {
                    for (int i=0;i<qsize;i++)
                        temp[i]=data[i];
                    maxSize+=Increment;
                    delete[] data;
                    data=temp;
                }
                else
                {
                    return false;
                }
            }

            //Ελεγχος αν ο παραλληλος πινακας ειναι γεματος
            if (SizeAp==maxSizeAp)
            {
                int *t;
                t = new int[maxSizeAp+Increment];
                if (t!=NULL)
                {
                    for (int i=0;i<SizeAp;i++)
                        t[i]=ap[i];
                    maxSizeAp+=Increment;
                    delete[] ap;
                    ap=t;
                }
                else
                {
                    return false;
                }
            }


            int pos=0;
            bool flag=false;

            //Ελεγχος αν η λεξει υπαρχει και αν οχι γινετε η εισαγωγη της στην καταληλη θεση
            while (pos<qsize && data[pos]<=key)
            {
                 if(data[pos]==key)
                 {
                    flag=true;
                    ap[pos]++;
                 }

                pos++;
            }

            if(!flag)
            {
                for (int i=qsize;i>pos;i--)
                {
                    data[i]=data[i-1];
                    ap[i]=ap[i-1];
                }

                data[pos] = key;
                ap[pos]=1;

                qsize++;
                SizeAp++;
            }

            return true;
        }

        void show()
        {
            cout<<"--------------"<<endl;
            for (int i=0;i<qsize;i++)
                cout<<i+1<<":"<<" "<<data[i]<<" "<<ap[i]<<endl;
            cout<<"--------------"<<endl;
        }

        int binarySearch(X *data, int l, int r, string x)
        {
            if (r >= l) {
                int mid = l + (r - l) / 2;

                if (data[mid] == x)
                    return mid;
                if (data[mid] > x)
                    return binarySearch(data, l, mid - 1, x);

                return binarySearch(data, mid + 1, r, x);
            }

            return -1;
        }

        bool Search(string s,int &p)
        {
            int result = binarySearch(data, 0, qsize - 1, s);

            if(result==-1)
                return false;
            else
            {
                p=result;
                return true;
            }
        }

        int appear(int pos){return ap[pos];}

        void delete_data()
        {
            delete [] data;
            delete [] ap;
            ap=nullptr;
            data=nullptr;
            qsize=0;
            maxSize=0;
            SizeAp=0;
            maxSizeAp=0;
        }

    private:
        X *data;
        int qsize;
        int maxSize;

        int *ap;
        int SizeAp;
        int maxSizeAp;

};

#endif // SORT_H

