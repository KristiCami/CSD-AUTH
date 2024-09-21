#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>

//������� ���������������
#include "hashTable.h"
//�����������; �������
#include "Bag.h"
//������������� �������
#include "Sort.h"

//������� ������� Q
#define qSize 5000

using namespace std;

//� ����������� ��� ����������� ���������� ��� �����
void removeSpaces(string&);
char to_lowercase(char);

//��������� ��� ������������� �� ��������� ��������
unsigned long long int operator% (string s, int k)
{
    int sum =0;
    for (int i=0;i<s.length();i++)
        sum+=s[i];


    return sum % k;
}

int main()
{

    /*������������ �������*/

    Bag A;
    string str,Q[qSize];
    int Count=0;

    //������� ��� ������ ��� �� ������ ��� ��� ��������� ���� ����������� ������
    ifstream ifs;
    ifs.open("small-file.txt");
    if (ifs.is_open())
    {
        cout<<"File open ok"<<endl;
        while (ifs>>str)
        {
            //���� ��� ��������� ��� �� �������� �� ������ ������� ��� ��� ����
            removeSpaces(str);
            for (char &c: str)
            {
                //��������� ���� ���������� ������ ��� ��� ���� �� ����
                c = to_lowercase(c);
            }
            //������ ��� ������ Q �� ��� ������ qSize ������
            if(Count<qSize)
                Q[Count++]=str;
            A.push_back(str);
        }
        ifs.close();
    }
    else
        cout<<"File error"<<endl;

    //A.show();

    //������ �� ������ ��� ����� ��� ��������� � ���� ��� �� �������� ��� ������� ����� ����� ������������ � ������ ��� ������� Q
    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<qSize;i++)
    {
        int pos;
        //������� ���� ����� ��� ������� Q ��� ��������� ��� ����� ��� �������
        A.Search(Q[i],pos);
        cout<<"The word "<<"("<<Q[i]<<")"<<" appear "<<A.appear(pos)<<" times"<<endl;
    }

    //����� ��������������
    auto finish = std::chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";

    //��������� ��� ������������ ������
    A.delete_data();

//-----------------------------------------------------------------------------------------
    /*������������� �������*/

    /*� ���������� ��� ����������� ��� ���
    ������������ ������ ����� �������� �� ���
    �����������*/


    Sort <string>B;
    string s1;

    ifstream file;
    file.open("small-file.txt");
    if (file.is_open())
    {
        cout<<"File open ok"<<endl;
        while (file>>s1)
        {
            removeSpaces(s1);
            for (char &c: s1)
            {
                c = to_lowercase(c);
            }
            //� ���������� ��� � ������� �� � ����� ���� ���� ������ ������� ���� ���� ����� Sort
            B.enQueue(s1);
        }
        file.close();
    }
    else
        cout<<"File error"<<endl;

    //B.show();

    auto strt = chrono::high_resolution_clock::now();

    for(int i=0;i<qSize;i++)
    {
        int pos;
        B.Search(Q[i],pos);
        cout<<"The word "<<"("<<Q[i]<<")"<<" appear "<<B.appear(pos)<<" times"<<endl;
    }

    auto fin = std::chrono::high_resolution_clock::now();

    chrono::duration<double> elap = fin - strt;

    cout << "Elapsed time: " << elap.count() << " s\n";

    B.delete_data();

//---------------------------------------------------------------------------------------

    //������ ������ ���� ������ ��������������� 1000 ������
    hashTable<int ,string> H(1000);
    string sm;
    int i=1;
    //������� �� ������
    ifstream f;
    f.open("small-file.txt");
    if (f.is_open())
    {
        cout<<"File open ok"<<endl;
        while (f>>sm)
        {

            removeSpaces(sm);
            for (char &c: sm)
            {
                c = to_lowercase(c);
            }
            //��� ������� � ���� ������ �� ������ ���������� ������ �� �������� ���� ������
            if (H.search(sm,i))
            {
                H.add(sm,i);
            }
            else
                H.insert(i,sm);

        }
        f.close();
    }
    else
        cout<<"File error"<<endl;

    auto Start = chrono::high_resolution_clock::now();

    for(int i=0;i<qSize;i++)
    {
        int pos;
        H.search(Q[i],pos);
        cout<<"The word "<<"("<<Q[i]<<")"<<" appear "<<pos<<" times"<<endl;
    }

    auto Finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> Elapsed = Finish - Start;

    cout << "Elapsed time: " << Elapsed.count() << " s\n";

    return 0;
}

//��������� �� �������� �������� �� ����
char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;
    }

    return c;
}

//������ �� ������ �������
void removeSpaces(string& s)
{
    for (int i = 0, len = s.size(); i < len; i++)
    {
        if (ispunct(s[i]))
        {
            s.erase(i--, 1);
            len = s.size();
        }
    }
}
