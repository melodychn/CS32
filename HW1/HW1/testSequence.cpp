//
//  testSequence.cpp
//  HW1
//
//  Created by Melody Chen on 4/15/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//
#include "Sequence.h"
#include <cassert>
#include <iostream>
using namespace std;
int main() {
    
        Sequence a;   // a can hold at most 1000 items
        Sequence b;      // b can hold at most 5 items
        Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
        ItemType v = 0;
    
        // No failures inserting 5 items into b
        for (int k = 0; k < 250; k++)
            assert(b.insert(v) != -1);
    
        // Failure if we try to insert a sixth item into b
        assert(b.insert(v) == -1);
        b.erase(0); //erase one item
        assert(b.insert(v) != -1);  //able to insert now
        // When two Sequences' contents are swapped, their capacities are
        // swapped as well:
        a.swap(b);
        assert(a.size()==250); //check if their sizes are swapped
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
    
        Sequence e;
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
    
        Sequence f;
        assert(f.set(1, 5)==false);
        f.insert(0);
        assert(f.set(0, 5)==true);
        f.get(0, index0);
        assert(index0==5);
    
//        Sequence h;
//        Sequence g;
//        assert(h.insert(0, "hi")==0);
//        assert(h.insert(0, "hey")==0);
//        assert(h.insert(1, "sup")==1);
//        assert(h.insert(3, "third")==3);
//        assert(h.size()==4);
//        assert(h.erase(0)==true);
//        assert(h.size()==3);
//        assert(h.remove("hi")==1);
//        assert(h.remove("hey")==0);
//        assert(h.insert(0, "third")==0);
//        assert(h.remove("third")==2);
//        g.insert(0, "hii");
//        g.insert(0, "heyy");
//        g.insert(0, "supp");
//        g.insert(0, "difdifj");
//        h.swap(g);
//        assert(h.size()==4);
//        assert(g.size()==1);
//        assert(g.remove("sup")==1);
//        assert(h.remove("hii")==1);
//
//        Sequence s1;
//        s1.insert(0, "paratha");
//        s1.insert(0, "focaccia");
//        Sequence s2;
//        s2.insert(0, "roti");
//        s1.swap(s2);
//        assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
//               s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
//        Sequence s;
//        s.insert(0, "dosa");
//        s.insert(1, "pita");
//        s.insert(2, "");
//        s.insert(3, "matzo");
//        assert(s.find("") == 2);
//        s.remove("dosa");
//        assert(s.size() == 3  &&  s.find("pita") == 0  &&  s.find("") == 1  &&
//               s.find("matzo") == 2);
        cerr<<"Passed all test cases"<<endl;
        return 0;
    
}




