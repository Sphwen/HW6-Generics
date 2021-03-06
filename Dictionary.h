//
// Created by Aris  Emery on 4/3/17.
//

#ifndef HW6_DICTIONARY_H
#define HW6_DICTIONARY_H


#include "KeyValue.h"
#include <iostream>

template <class K, class V>
class Dictionary {
public:
    int numKeyValuePairs = 0;
    int currentKeyValuePairs=0;
    Dictionary();
    Dictionary(int x);
    KeyValue<K, V> getByKey(K key);
    V getValueByKey(K key);
    KeyValue<K, V> getByIndex(int n);
    int getNumKeyValuePairs(){return numKeyValuePairs;};
    int getCount(){return currentKeyValuePairs;};
    void add(K key, V value); //TODO: make dynamic expansion of memory
    void removeByKey(K key);
    void removeByIndex(int n);
    //bool operator == (V firstValue);
    bool operator == (std::string string2);
    ~Dictionary();
private:
    KeyValue<K, V>** keyValuePairs;

};
template <class K, class V>
bool Dictionary<K, V>::operator == (std::string string2){
    char convertedString1[50];
    char convertedString2[50];
    V string1=this;
    for(int i=0;i<string1.length();i++){
        convertedString1[i]=string1[i];
    }
    for(int j=0;j<string2.length();j++){
        convertedString2[j]=string2[j];
    }
    int size=0;
    if(string1.length()>string2.length()){
        size=string1.length();
    } else{
        size=string2.length();
    }
    if(!strncmp(convertedString1,convertedString2,size)){
        return true;
    }
    else{
        return false;
    }
}
/*
template <class K, class V>
bool Dictionary<K, V>:: operator == (V firstValue){
    std::string testString="asfd";
    if(typeid(this)== typeid(testString)){
        this.compare(firstValue);
        std::cout<<"at least it's working...\n";
    }


};
*/
template <class K, class V>
Dictionary<K, V>::Dictionary(){
    Dictionary(10);
}

template <class K, class V>
Dictionary<K, V>::Dictionary(int size){
    numKeyValuePairs=size;
    keyValuePairs = new KeyValue<K, V>*[size];
}

template <class K, class V>
KeyValue<K, V> Dictionary<K, V>::getByKey(K key){
    bool found=false;
    int i=0;
    for(;i<currentKeyValuePairs&&found==false;i++){
        if(keyValuePairs[i]->getKey()==key){
            found=true;
        }
    }
    if(found==false){
        std::cout<<"can't find item, doesn't exist.\n";
        throw std::invalid_argument( "Item to be found doesn't exist\n" );
    }
    return *keyValuePairs[i];
}

template <class K, class V>
KeyValue<K, V> Dictionary<K, V>::getByIndex(int key){
    if(key>currentKeyValuePairs||key<0){
        std::cout<<"can't find item, bad index given.\n";
        throw std::invalid_argument( "Item to be found because bad index given\n" );
    }
    return *keyValuePairs[key];
}


template <class K, class V>
V Dictionary<K, V>::getValueByKey(K key){
    bool found=false;
    for(int i=0;i<numKeyValuePairs&&found==false;i++){
        if(keyValuePairs[i]->getKey()==key){
            found=true;
            return keyValuePairs[i]->m_value;
        }
    }
    return nullptr;
}

template <class K, class V>
void Dictionary<K, V>::add(K key, V value) {
    if(currentKeyValuePairs>=numKeyValuePairs){
        int newSize=numKeyValuePairs*2;
        int oldSize=numKeyValuePairs;
        KeyValue<K, V>** tempKeyValuePairs;
        tempKeyValuePairs = new KeyValue<K, V>*[numKeyValuePairs];
        for(int i; i<numKeyValuePairs;i++){
            tempKeyValuePairs[i]=keyValuePairs[i];
        }
        keyValuePairs = new KeyValue<K, V>*[newSize];
        for(int i; i<numKeyValuePairs;i++){
            keyValuePairs[i]=tempKeyValuePairs[i];
        }
        numKeyValuePairs=newSize;
        for (int i=0; i<oldSize; i++)
            delete tempKeyValuePairs[i];
        delete[] tempKeyValuePairs;
    }
    KeyValue<K,V>* newKey = new KeyValue<K,V>(key, value);
    keyValuePairs[currentKeyValuePairs] = newKey;
    currentKeyValuePairs++;
}

template <class K, class V>
void Dictionary<K, V>::removeByKey(K key){
    bool found=false;
    int i;
    for(i=0;i<currentKeyValuePairs&&found==false;i++){
        if(keyValuePairs[i]->getKey()==key){
            found=true;
            //TODO: heavy testing on this one;
        }
    }
    if(found==false){

        std::cout<<"can't remove item, doesn't exist.\n";
        throw std::invalid_argument( "Tried to remove non-existent item\n" );

    }
    else if(found==true){
        removeByIndex(i);
        return;
    }
};
template <class K, class V>
void Dictionary<K, V>::removeByIndex(int key){
    if(key>currentKeyValuePairs||key<0){
        std::cout<<"can't remove item, bad index given.\n";
        throw std::invalid_argument( "Item can't be found because bad index given\n" );
    }
    int i=key;
    keyValuePairs[i]= nullptr;         //TODO: heavy testing on this one;

    for(;i<currentKeyValuePairs;i++){
        keyValuePairs[i-1]=keyValuePairs[i];
    }
    //TODO:Test if i should be incremented again righ abou her
    keyValuePairs[i]= nullptr;

};

template <class K, class V>
Dictionary<K, V>::~Dictionary()
{
    for (int i=0; i<numKeyValuePairs; i++)
        keyValuePairs[i]= nullptr;
    for (int i=0; i<numKeyValuePairs; i++)
        delete keyValuePairs[i];
    delete[] keyValuePairs;
}

#endif //HW6_DICTIONARY_H
