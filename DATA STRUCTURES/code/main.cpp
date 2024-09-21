#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>

//πινακας κατακερματισμου
#include "hashTable.h"
//Αταξινομητο; πινακας
#include "Bag.h"
//ταξινομημενος πινακας
#include "Sort.h"

//Μεγεθος συνολου Q
#define qSize 5000

using namespace std;

//Η λειτουργεια τον συναρτησεων αναφαιρετε στο τελος
void removeSpaces(string&);
char to_lowercase(char);

//μετατρεπω της συμβολοσειρες σε ακαιρεους αριθμους
unsigned long long int operator% (string s, int k)
{
    int sum =0;
    for (int i=0;i<s.length();i++)
        sum+=s[i];


    return sum % k;
}

int main()
{

    /*Αταξινόμητος πινακας*/

    Bag A;
    string str,Q[qSize];
    int Count=0;

    //Διαβαζω της λεξεις απο το αρχειο και της αποθηκευω στον αταξινομητο πινακα
    ifstream ifs;
    ifs.open("small-file.txt");
    if (ifs.is_open())
    {
        cout<<"File open ok"<<endl;
        while (ifs>>str)
        {
            //καλω την συναρτηση για να αφαιρεση τα σημεια στηξεις απο την λεξη
            removeSpaces(str);
            for (char &c: str)
            {
                //μετατρεπω καθε κεφαλαλαιο γραμμα απο την λεξη σε πεζο
                c = to_lowercase(c);
            }
            //γεμιζω τον πινακα Q με της πρωτες qSize λεξεις
            if(Count<qSize)
                Q[Count++]=str;
            A.push_back(str);
        }
        ifs.close();
    }
    else
        cout<<"File error"<<endl;

    //A.show();

    //Αρχιζω να μετραω τον χρονο που χριαζεται η δομη για να απαντηση στο ερωτημα ποσες φορες εμφανιστηκαν η λεξεις του συνολου Q
    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<qSize;i++)
    {
        int pos;
        //Αναζητω καθε λεξει του συνολου Q και επιστρεφω την θεσει που βρεθηκε
        A.Search(Q[i],pos);
        cout<<"The word "<<"("<<Q[i]<<")"<<" appear "<<A.appear(pos)<<" times"<<endl;
    }

    //Τελος χρονομετρησεις
    auto finish = std::chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";

    //διαγραφει του αταξινομητου πινακα
    A.delete_data();

//-----------------------------------------------------------------------------------------
    /*Ταξινομημενος πινακας*/

    /*Η διαδικασια που ακοουλουθει για τον
    ταξινομημενο πινακα ειναι παρομεια με τον
    αταξινομητο*/


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
            //Η ταξινομηση και ο ελεγχος αν η λεξει εχει ξανα βρεθει γινεται μεσα στην κλαση Sort
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

    //Αρχικα δηλωνω εναν πινακα κατακερματισμου 1000 θεσεων
    hashTable<int ,string> H(1000);
    string sm;
    int i=1;
    //διαβαζω το αρχειο
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
            //Εαν βρεθηκε η λεξη αυξανω το πληθος εμφανισεων αλλιως τη προσθετω στον πινακα
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

//Μετατρεπω τα κεφαλαια γραμματα σε πεζα
char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;
    }

    return c;
}

//Αφαιρω τα σημεια στιξεις
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
