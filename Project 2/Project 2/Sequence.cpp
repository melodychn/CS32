//
//  NewSequence.cpp
//  HW1
//
//  Created by Melody Chen on 4/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "Sequence.h"

#include <iostream>
using namespace std;
Sequence::Sequence():m_length(0)
// Create an empty sequence (i.e., one with no items)
{
    dummy = new Node;
    dummy->next = dummy; //circular
    dummy->prev = dummy;
}

Sequence::~Sequence()
{
    Node* p = dummy;
    for(int k = m_length; k>=0; k--)
        erase(k);
    delete p;
}

Sequence::Sequence(const Sequence& other):m_length(0)
{
    dummy = new Node;
    dummy->next = dummy; //circular
    dummy->prev = dummy;
    for(int k = 0; k<other.size();k++)
    {
        ItemType temp;
        other.get(k, temp);
        insert(k, temp);
    }
}
Sequence & Sequence::operator=(const Sequence &other)
{
    Sequence temp(other);
    swap(temp);
    return *this;
}

bool Sequence::empty() const  // Return true if the sequence is empty, otherwise false.
{
    if(m_length == 0)
        return true;
    return false;
}

int Sequence::size() const    // Return the number of items in the sequence.
{
    return m_length;
}

int Sequence::insert(int pos, const ItemType& value)
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
{
    if(pos >=0 && pos <= m_length){
        Node* p = dummy->next;
        for(int k = 0; k<pos; p=p->next, k++)
            ;
        Node* newGuy = new Node;
        newGuy->value = value;
        newGuy->next = p;
        newGuy->prev = p->prev;
        p->prev->next = newGuy;
        p->prev = newGuy;
        m_length++;
        return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value)
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
{
    int p = m_length;
    Node* pp = dummy;
    for(int k = 0; k < m_length; pp = pp->next, k++){
        if(value <= pp->next->value){
            p = k;
            break;
        }
    }
    if(insert(p, value)!=-1)
        return p;
    return -1;
}

bool Sequence::erase(int pos)
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
{
    if(pos >=0 && pos < m_length){
        //remove item at position
        Node* p = dummy;
        for(int k = -1; k<pos; p=p->next, k++)
            ;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        m_length--;
        delete p;
        return true;
    }
    return false;
}

int Sequence::remove(const ItemType& value)
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
    int count = 0;
    Node* p = dummy;
    for(int k = 0; k<m_length; p=p->next, k++){
        if(p->next->value==value){
            erase(k);
            count++;
            k--;
            p=p->prev;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
{
    Node* p = dummy;
    if(pos >=0 && pos < m_length){
        for(int k = -1; k < pos; p = p->next, k++)
            ;
        value = p->value;
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
    Node* p = dummy;
    if(pos >=0 && pos < m_length){
        for(int k = -1; k<pos; k++, p=p->next)
            ;
        p->value=value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
{
    int p = -1;
    Node* pp = dummy;
    for(int k=0; k<m_length; pp=pp->next, k++){
        if(pp->next->value==value){
            p = k;
            break;
        }
    }
    return p;
}

void Sequence::swap(Sequence& other)
// Exchange the contents of this sequence with the other one.
{
    Node* temp = other.dummy;
    int tempsize = other.m_length;
    other.dummy = dummy;
    dummy = temp;
    other.m_length = m_length;
    m_length = tempsize;
}

void Sequence::dump() const
{
    Node* p = dummy;
    for(int k = 0; k < m_length; p = p->next, k++)
    {
        cout<<p->next->value<<endl;
    }
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq2.size()!=0 && !(seq2.size()>seq1.size()))
    {
        for(int k=0; k<seq1.size(); k++){
            ItemType temp1, head2;
            seq1.get(k, temp1);
            seq2.get(0, head2);
            if(temp1 == head2){
                for(int i=0, c=k; i<seq2.size(); i++, c++){
                    ItemType temp1_, temp2_;
                    seq1.get(c, temp1_);
                    seq2.get(i, temp2_);
                    if(temp1_!=temp2_){
                        break;
                    }else if(i==seq2.size()-1){
                        return k;
                    }
                }
            }
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    //check if result is empty
    Sequence temp;
    for(int k = 0; k<seq1.size()&&k<seq2.size(); k++){
        ItemType temp1, temp2;
        seq1.get(k, temp1);
        seq2.get(k, temp2);
        temp.insert(k*2, temp2);
        temp.insert(k*2, temp1);
    }
    if(temp.size()!=(seq1.size()+seq2.size())){
        if(seq1.size()>seq2.size()){
            int x = seq2.size();
            for(int k = temp.size(); k < (seq1.size()+seq2.size());k++){
                ItemType temp1;
                seq1.get(x, temp1);
                temp.insert(k, temp1);
                x++;
            }
        }else{
            int x = seq1.size();
            for(int k = temp.size(); k < (seq1.size()+seq2.size());k++){
                ItemType temp1;
                seq2.get(x, temp1);
                temp.insert(k, temp1);
                x++;
            }
        }
    }
    result = temp;
}




