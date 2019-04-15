//
//  Sequence.cpp
//  HW1
//
//  Created by Melody Chen on 4/10/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
using namespace std;
Sequence::Sequence():m_length(0)    // Create an empty sequence (i.e., one with no items)
{
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
    if(m_length<DEFAULT_MAX_ITEMS){
        if(pos >=0 && pos <= m_length){
            //shift everything backwards
            if(pos!=m_length){ //check if position == size
                for(int k = m_length; k>=pos; k--)
                    array[k+1]=array[k];
            }
            array[pos]= value;
            m_length++;
            return pos;
        }
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
    for(int i = 0; i < m_length; i++){
        if(value <= array[i]){
            p = i;
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
        for(int k = pos; k < m_length-1; k++){
            array[k]=array[k+1];
        }
        m_length--;
        return true;
    }
    return false;
}

int Sequence::remove(const ItemType& value)
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
    int count = 0;
    for(int k = 0; k<m_length; k++){
        if(array[k]==value){
            erase(k);
            count++;
            k--;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
{
    if(pos >=0 && pos < m_length){
        value = array[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
    if(pos >=0 && pos < m_length){
        array[pos]=value;
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
    for(int k=0; k<m_length; k++){
        if(array[k]==value){
            p = k;
            break;
        }
    }
    return p;
}

void Sequence::swap(Sequence& other)
// Exchange the contents of this sequence with the other one.
{
    for(int k = 0; k<DEFAULT_MAX_ITEMS; k++)
    {
        ItemType temp = other.array[k];
        other.array[k]=array[k];
        array[k] = temp;
    }
    int tempsize = other.size();
    other.m_length = m_length;
    m_length = tempsize;
}

void Sequence::dump()
{
    for(int k = 0; k<m_length; k++){
        cerr<<array[k]<<endl;
    }
}



