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

        //vector of values for single key
        vector<V> values;
        info(K newKey){
            key = newKey;
        }

        info(K newKey, V newValue){
            key = newKey;
            // value = newValue;
            values.push_back(newValue);

        }

        //add values to vector
        void addValue(V newValue){
            value = newValue;
            for(unsigned int i = 0 ; i < values.size();i++){
                if(!(newValue == values[i])){
                    values.push_back(newValue);
                }
            }
        }

        K getkey(){
            return key;
        }

        vector<V>& getValues(){
            return values;
        }
        V& getValue(){
            cout << key << " ";
            return value;
        }

    };
    //hash table implements array of vector
    int size;
    vector<info>* infoData;

public:
    DSHashtable();
    DSHashtable(int);

    DSHashtable(DSHashtable &other);
    DSHashtable& operator=(DSHashtable &other);

    ~DSHashtable();
    V& find(K);
    bool contains(K);
    bool isDSHashtableEmpty();

    void insert(K, V);
    int getSize();
    int getKeyIndex(K);
    int getIndex(K);
    void print();
};

//default constr: initalizes predetermined size
template<class K, class V>
DSHashtable<K, V>::DSHashtable(): size(10000) {
    infoData = new vector<info>[size];
}

//constr that takes in parameter as size to initialize by
template<class K, class V>
DSHashtable<K, V>::DSHashtable(int changedSize){
    if(changedSize<20){
        size=20;
    }
    else
    {
        size=changedSize;
    }
    infoData = new vector<info>[size];
}

//copy constr for deep copy
template<class K, class V>
DSHashtable<K, V>::DSHashtable(DSHashtable &other){
    size=other.size;
    infoData=new vector<info> [size];
    for(int i =0; i<size; i++){
        infoData[i]=other.infoData[i];
    }
}

//destructor to free and release memory
template<class K, class V>
DSHashtable<K, V>::~DSHashtable(){
    delete[] infoData;
    infoData=nullptr;
}

//uses key to determine where to insert the hash value
template<class K, class V>
void DSHashtable<K, V>::insert(K key, V value){
    int index = hash<K>()(key) % size;
    // info obj(key, value);
    info obj(key);
    obj.addValue(value);
    infoData[index].push_back(obj);
}

//overloaded equals operator for deep copy
template<class K, class V>
DSHashtable<K, V>& DSHashtable<K, V>::operator=(DSHashtable<K, V>& otherList)
{
    size=otherList.size;
    if(infoData !=nullptr)
    {
        delete [] infoData;
    }
    infoData=new vector<V> [size];
    for(int i =0; i<size; i++)
    {
        infoData[i]=otherList.infoData[i];
    }
    return *this;
}


//uses key to find corresponding value
template<class K, class V>
V& DSHashtable<K, V>::find(K keyToFind){
    int index=hash<K>()(keyToFind) % size;
    for(unsigned int j=0; j<infoData[index].size(); j++){
        if(infoData[index][j].getkey() == keyToFind){
            return infoData[index][j].getValue();
        }
    }
}

template<class K, class V>
int DSHashtable<K, V>::getSize(){
    return size;
}


template<class K, class V>
int DSHashtable<K, V>::getIndex(K keyToFind){
    int index=hash<K>()(keyToFind) % size;
    return index;
}

template<class K, class V>
int DSHashtable<K, V>::getKeyIndex(K keyToFind){
    int index=hash<K>()(keyToFind) % size;
    for(int j=0; j<infoData[index].size(); j++){
        if(infoData[index][j].getkey() == keyToFind){
            return j;
        }
    }
}

//use key to go to index of hash value and confirm if data is present or not
template<class K, class V>
bool DSHashtable<K, V>::contains(K newKey){
    int index=hash<K>()(newKey) % size;
    for(int j=0; j<infoData[index].size(); j++){
        if(infoData[index][j].getkey() == newKey){
            return true;
        }
    }
    return false;
}

//print values of table
template<class K, class V>
void DSHashtable<K, V>::print(){
    for(int i=0; i<size; i++){
        for(unsigned int j=0; j<infoData[i].size(); j++){
            //  cout <<  listData[i][j].getKey() << "\t";
            cout <<  infoData[i][j].getValue()<<endl;
            //  for(int k = 0 ; k < listData[i][j].getValue(); k++){
            // cout<<listData[i][j].getValue().at(k);
        }
    }
}


//is hash table empty
template<class K, class V>
bool DSHashtable<K, V>::isDSHashtableEmpty(){
    for(int i=0; i<size; i++){
        if(infoData[i].size()!=0){
            return false;
        }
    }
    return true;
}

#endif // HASHTABLE_H
