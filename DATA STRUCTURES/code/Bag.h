#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class Bag
{
    public:
        Bag();//����� �������������
        void delete_data();//�������� ���������
        int size(){return Size;}
        bool push_back (string);
        bool moreMemory(int);
        string str(int pos){return data[pos];}
        int appear(int pos){return ap[pos];}
        bool Search(string,int&);
        void show();
    private:
        string *data;
        int Size;
        int maxSize;

        //��� ��� ��������� ��� ���������� ��������������� ���������� �������

        int *ap;
        int SizeAp;
        int maxSizeAp;
};
