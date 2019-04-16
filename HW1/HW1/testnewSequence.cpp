//
//  testnewSequence.cpp
//  HW1
//
//  Created by Melody Chen on 4/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//


#include <iostream>
#include "newSequence.h"
#include <cassert>
using namespace std;
int main() {

    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 0;

    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);

    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
    b.erase(0); //erase one item
    assert(b.insert(v) != -1);  //able to insert now
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(a.size()==5); //check if their sizes are swapped
    assert(b.size()==0); //check if sizes are swapped
    assert(b.find(v)==-1);
    assert(b.insert(v) != -1); //check if you're able to insert stuff into b now
    assert(b.find(v)==0); //check if the first instance of v is at 0
    assert(a.insert(v) == -1);
    Sequence d = a; //check if copy constructor worked
    assert(d.insert(v) == -1);
    a = b; //check if assignment operator worked
    assert(a.insert(v) != -1);
    assert(a.find(0)==0);
    assert(a.size()==2);

    Sequence e = 3;
    e.insert(5);
    e.insert(1);
    e.insert(3);
    unsigned long index0;
    e.get(0, index0);
    assert(index0 == 1); //test if inserts sorts correctly
    unsigned long index1;
    e.get(1, index1);
    assert(index1 == 3);
    assert(e.erase(3)==false); //should be out of bounds
    assert(e.remove(1)==1);
    e.get(1,index1);
    assert(index1==5); //tests if remove shifts correctly
    assert(e.remove(1)==0);
    assert(e.size()==2);
    assert(e.erase(1)==true);
    assert(e.get(1, index1)==false);
    assert(e.size()==1);
    assert(e.remove(3)==1);
    assert(e.remove(10)==0);
    assert(e.erase(0)==false); //nothing left
    e.insert(0);
    e.insert(0);
    e.insert(0);
    assert(e.remove(0)==3); //should remove all zeroes
    assert(e.size()==0);

    Sequence f = 4;
    assert(f.set(1, 5)==false);
    f.insert(0);
    assert(f.set(0, 5)==true);
    f.get(0, index0);
    assert(index0==5);


    cerr<<"passed all test cases"<<endl;
     return 0;

}
