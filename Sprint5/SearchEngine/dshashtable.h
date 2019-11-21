#ifndef DSHASHTABLE_H
#define DSHASHTABLE_H
#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>

using namespace std;

template<class K, class V>

class DSHashtable{

private:
    //struct holds key-value pair
    struct info{
        K key;
        V value;
        info(K newKey, V newValue){
            key = newKey;
            value = newValue;
        }
        K getkey(){
            return key;
        }
        V& getValue(){
            return value;
        }
    };

    //hash table implements array of vector
    int size;
    vector<info>* listData;

public:
    DSHashtable();
    DSHashtable(int);

    DSHashtable(DSHashtable &rhs);
    DSHashtable& operator=(DSHashtable &rhs);

    ~DSHashtable();

    void insert(K, V);

    V& find(K);
    bool contains(K);

    int getSize();
    bool isDSHashtableEmpty();

    void print();

};

//default constr: initalizes predetermined size
template<class K, class V>
DSHashtable<K, V>::DSHashtable(): size(10000)
{
    listData = new vector<info>[size];
}

//constr that takes in parameter as size to initialize by
template<class K, class V>
DSHashtable<K, V>::DSHashtable(int newSize)
{
    if(newSize<20){
        size=20;
    }
    else
    {
        size=newSize;
    }
    listData = new vector<info>[size];
}

//copy constr for deep copy
template<class K, class V>
DSHashtable<K, V>::DSHashtable(DSHashtable &rhs)
{
    size=rhs.size;
    listData=new vector<info> [size];
    for(int i =0; i<size; i++)
    {
        listData[i]=rhs.listData[i];
    }
}

//overloaded equals operator for deep copy
template<class K, class V>
DSHashtable<K, V>& DSHashtable<K, V>::operator=(DSHashtable<K, V> &otherList)
{
    size=otherList.size;
    if(listData !=nullptr)
    {
        delete [] listData;
    }
    listData=new vector<V> [size];
    for(int i =0; i<size; i++)
    {
        listData[i]=otherList.listData[i];
    }
    return *this;
}

//destructor to free and release memory
template<class K, class V>
DSHashtable<K, V>::~DSHashtable()
{
    delete[] listData;
    listData=nullptr;
}

//uses key to determine where to insert the hash value
template<class K, class V>
void DSHashtable<K, V>::insert(K key, V value)
{
    int index = hash<K>()(key) % size;
    info obj(key, value);
    listData[index].push_back(obj);
}


//uses key to find corresponding value
template<class K, class V>
V& DSHashtable<K, V>::find(K keyToFind)
{
    int index=hash<K>()(keyToFind) % size;
    for(int j=0; j<listData[index].size(); j++)
    {
        if(listData[index][j].getkey() == keyToFind){
            return listData[index][j].getValue();
        }
    }
}

//use key to go to index of hash value and confirm if data is present or not
template<class K, class V>
bool DSHashtable<K, V>::contains(K newKey)
{
    int index=hash<K>()(newKey) % size;
    for(int j=0; j<listData[index].size(); j++)
    {
        if(listData[index][j].getkey() == newKey){
            return true;
        }
    }
    return false;
}


template<class K, class V>
int DSHashtable<K, V>::getSize()
{
    return size;
}

//is hash table empty
template<class K, class V>
bool DSHashtable<K, V>::isDSHashtableEmpty()
{
    for(int i=0; i<size; i++)
    {
        if(listData[i].size()!=0){
            return false;
        }
    }
    return true;
}

//print values of table
template<class K, class V>
void DSHashtable<K, V>::print()
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<listData[i].size(); j++)
        {
        cout<<listData[i][j].getValue();
        }
    }
}
#endif // HASHTABLE_H
