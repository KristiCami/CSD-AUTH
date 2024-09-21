#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char fn[50];
    char k;

    cin>>k;
    cin>>fn;

    int Count=0,count_k=0;
    char A[1000],c;

    ifstream ifs;
    ifs.open(fn);
    if( ifs.is_open())
    {

        while(ifs>>c)
        {
            A[Count++]=c;
        }

        ifs.close();
    }
    else
    {
        cout<<"File error"<<endl;
        exit(1);
    }
    for(int i=0;i<Count;i++)
    {
        //cout<<A[i];
        if(A[i]==k)
           {
                count_k++;
           }
    }

    cout<<count_k<<endl;
}
