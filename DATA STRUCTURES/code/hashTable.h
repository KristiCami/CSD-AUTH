#ifndef hashTable_h
#define hashTable_h

//Δημιουργεια κλασης myPair για την αποθηκευση (λεξη,εμφανισεις)
template <typename dataType, typename keyType>
class myPair
{
    public:
        myPair(dataType d, keyType k)
        {
            data=d;
            key=k;
        }
        dataType data;
        keyType key;
};

template <typename dataType, typename keyType>
class hashTable
{
    private:
        int size;
        int elements;
        myPair<dataType,keyType> **A;
        void *deleted;

        unsigned int hash(const keyType &);
        unsigned int hash2(unsigned int );
        myPair<dataType,keyType> *& search(const keyType &);

        myPair<dataType,keyType> *& add(const keyType &);

    public:
        hashTable();
        hashTable(int n);
        ~hashTable();
        bool insert(const dataType &, const keyType &);
        bool search(const keyType &, dataType &data);
        bool remove(const keyType &);

        bool add(const keyType &, dataType &data);

};
template <typename dataType, typename keyType>
hashTable<dataType,keyType>::hashTable()
{
    size=10;
    elements=0;

    deleted = this;//new int();

    A = new myPair<dataType,keyType> *[size];
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}
template <typename dataType, typename keyType>
hashTable<dataType,keyType>::hashTable(int n)
{
    deleted = this;//new int();

    size=n;
    elements=0;
    A = new myPair<dataType,keyType> *[size];
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}
template <typename dataType, typename keyType>
hashTable<dataType,keyType>::~hashTable()
{
    delete[] A;
    A=nullptr;
    elements=0;
    size=0;
}

template <typename dataType, typename keyType>
unsigned int hashTable<dataType,keyType>::hash(const keyType &d)
{
    return d%6700417%size;
}

template <typename dataType, typename keyType>
unsigned int hashTable<dataType,keyType>::hash2(unsigned int d)
{
    return (d+1)%6700417%size;
}


template <typename dataType, typename keyType>
bool hashTable<dataType,keyType>::insert (const dataType &d, const keyType &key)
{
    if (search(key)!=nullptr)
        return false;
    if (elements>=size/2)
    {
        myPair<dataType,keyType> **temp;
        size*=2;
        temp = new myPair<dataType,keyType>*[size];
        for(int i=0;i<size;i++)
            temp[i]=nullptr;

        for (int i=0;i<size/2;i++)
        {
            if (A[i]!=nullptr && A[i]!=deleted)
            {
                unsigned int p = hash(A[i]->key);
                while (temp[p]!=nullptr)
                    p = hash2(p);
                temp[p]=A[i];
                A[i]=nullptr;
            }
        }
        delete[]A;
        A=temp;
    }
    unsigned int p = hash(key);
    while (A[p]!=nullptr && A[p]!=deleted)
        p = hash2(p);
    A[p]=new  myPair<dataType,keyType> (d,key);
    elements++;
    return true;
}
template <typename dataType, typename keyType>
myPair<dataType,keyType> *& hashTable<dataType,keyType>::search(const keyType &key)
{
    unsigned int p = hash(key);
    while (A[p]==deleted || (A[p]!=nullptr && A[p]->key!=key))
        p = hash2(p);
    return A[p];
}


template <typename dataType, typename keyType>
bool hashTable<dataType,keyType>::search(const keyType &key, dataType &data)
{
    myPair<dataType,keyType> *p = search(key);

    if (p==nullptr)
        return false;

    data = p->data;

    return true;
}

template <typename dataType, typename keyType>
bool hashTable<dataType,keyType>::remove(const keyType &key)
{
    myPair<dataType,keyType> * &p = search(key);
    if (p==nullptr)
        return false;

    elements--;
    delete p;
    p = (myPair<dataType,keyType> *) deleted;

    return true;
}
//----------------------------------------------------------------
template <typename dataType, typename keyType>
myPair<dataType,keyType> *& hashTable<dataType,keyType>::add(const keyType &key)
{
    unsigned int p = hash(key);
    while (A[p]==deleted || (A[p]!=nullptr && A[p]->key!=key))
        p = hash2(p);
    return A[p];
}


template <typename dataType, typename keyType>
bool hashTable<dataType,keyType>::add(const keyType &key, dataType &data)
{
    myPair<dataType,keyType> *p = add(key);

    if (p==nullptr)
        return false;

    data = p->data++;

    return true;
}

#endif

