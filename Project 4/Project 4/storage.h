//
//  Storage.h
//  Project 4
//
//  Created by Melody Chen on 6/4/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

#ifndef storage_h
#define storage_h

struct Bucket{
    string s;
    int offset;
};

class hashTable{
public:
    hashTable(int size); //constructor
    ~hashTable();
    void insert(string s, int offset);
    bool search(string s, int& offset);
    bool find(string s, int offset);
    int nextOffset(string s, int oldoffset);
    string get(int offset);
private:
    int m_size;
    hash<string> h;
    int hashFunc(string s);
    vector<Bucket*>* m_buckets; //buckets
};

#endif /* storage_h */

hashTable::hashTable(int size){
    m_size = size*1.5;
    if(m_size%2==0)
        m_size++;
    m_buckets = new vector<Bucket*>[m_size];
}

hashTable::~hashTable(){
    for(int k = 0; k<m_size; k++){
        vector<Bucket*>::iterator it;
        it = m_buckets[k].begin();
        while(it!=m_buckets[k].end()){
            vector<Bucket*>::iterator temp = it;
            it++;
            delete *temp;
        }
    }
    delete[] m_buckets;
}

int hashTable::hashFunc(string s)
{
    return h(s)%m_size;
}

bool hashTable::search(string s, int& offset)
{
    int bucket = hashFunc(s);
    vector<Bucket*>::iterator it;
    it = m_buckets[bucket].begin();
    while(it!=m_buckets[bucket].end()){
        if((*it)->s==s){
            offset = (*it)->offset;
            return true;
        }
        it++;
    }
    offset=-999;
    return false;
}

int hashTable::nextOffset(string s, int oldoffset)
{
    int bucket = hashFunc(s);
    vector<Bucket*>::iterator it;
    it = m_buckets[bucket].begin();
    while(it!=m_buckets[bucket].end()){
        if((*it)->s==s && (*it)->offset>oldoffset){
            //oldoffset = (*it)->offset;
            return (*it)->offset;
        }
        it++;
    }
    
    return -999;
}

bool hashTable::find(string s, int offset)
{
    int bucket = hashFunc(s);
    vector<Bucket*>::iterator it;
    it = m_buckets[bucket].begin();
    while(it!=m_buckets[bucket].end()){
        if((*it)->s==s&&(*it)->offset==offset){
            return true;
        }
        it++;
    }
    return false;
}

void hashTable::insert(string s, int offset)
{
    Bucket* temp = new Bucket;
    temp->s = s;
    temp->offset = offset;
    int bucket = hashFunc(s);
    if(m_buckets[bucket].size()>300)
        return;
    m_buckets[bucket].push_back(temp);
}

string hashTable::get(int offset)
{
    //    int bucket = hashFunc(offset);
    //    if(m_buckets[bucket].empty())
    //        return "";
    //    vector<Bucket>::iterator it;
    //    it = m_buckets[bucket].begin();
    //    while(it!=m_buckets[bucket].end()){
    //        if(it->offset==offset)
    //            return it->s;
    //        it++;
    //    }
    return "";
}
