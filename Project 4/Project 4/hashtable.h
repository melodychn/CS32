//
//  hashtable.h
//  Project 4
//
//  Created by Melody Chen on 6/4/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

#ifndef hashtable_h
#define hashtable_h

struct Node{
    string s;
    int offset;
};

class hashTable{
public:
    hashTable(size_t size);
    ~hashTable();
    void insert(string s, int offset);
    bool search(string s, int& offset); //gives you the earliest offset if the string exists in hashtable
    bool find(string s, int offset); //tries to find a SPECIFIC string at given offset
    int nextOffset(string s, int oldoffset);
private:
    size_t m_size;
    hash<string> h;
    int hashFunc(string s);
    vector<Node*>* m_buckets;
};

#endif /* hashtable_h */

hashTable::hashTable(size_t size){
    m_size = size*1.5; //number of buckets depend on size of given probem
    if(m_size%2==0) //make m_size an odd number so its easier to hash
        m_size++;
    m_buckets = new vector<Node*>[m_size]; //m_buckets is a dynamic array of pointers to vectors, and each vector contains pointer to a Node object
}

hashTable::~hashTable()
//destroys all dynamic variables used
{
    for(int k = 0; k<m_size; k++){
        vector<Node*>::iterator it;
        it = m_buckets[k].begin();
        while(it!=m_buckets[k].end()){
            vector<Node*>::iterator temp = it;
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
//given the string, if found, will return true and output offset, if not found return false
{
    int bucket = hashFunc(s);
    vector<Node*>::iterator it;
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
//will find the nextOffset given a string and oldoffset, if cannot find nextOffset return -999
{
    int bucket = hashFunc(s);
    vector<Node*>::iterator it;
    it = m_buckets[bucket].begin();
    while(it!=m_buckets[bucket].end()){
        if((*it)->s==s && (*it)->offset>oldoffset){ //if you found a greater offset
            return (*it)->offset;
        }
        it++;
    }
    return -999; //cannot find any more offsets
}

bool hashTable::find(string s, int offset)
//given an offset and a string, will determine if this combo exists in the hashtable
{
    int bucket = hashFunc(s);
    vector<Node*>::iterator it;
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
//creates a bucket object with given string and offset and adds it into the hashtable
{
    int bucket = hashFunc(s);
    if(m_buckets[bucket].size()>200) //upper limit for amount of nodes in one bucket, or else the whole hashtable will take too long to search and run
        return; //need to break out of function if you don't want to add a new node
    Node* temp = new Node;
    temp->s = s;
    temp->offset = offset;
    m_buckets[bucket].push_back(temp);
}

