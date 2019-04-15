////
////  testnewSequence.cpp
////  HW1
////
////  Created by Melody Chen on 4/11/19.
////  Copyright © 2019 Melody Chen. All rights reserved.
////
//
//
//#include <iostream>
//#include "newSequence.h"
//
//using namespace std;
//int main(int argc, const char * argv[]) {
//    
//    Sequence a(1000);   // a can hold at most 1000 items
//    Sequence b(5);      // b can hold at most 5 items
//    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
//    ItemType v = 0;
//    
//    // No failures inserting 5 items into b
//    for (int k = 0; k < 5; k++)
//        assert(b.insert(v) != -1);
//    
//    // Failure if we try to insert a sixth item into b
//    assert(b.insert(v) == -1);
//    b.erase(0); //erase one item
//    assert(b.insert(v) != -1);  //able to insert now
//    // When two Sequences' contents are swapped, their capacities are
//    // swapped as well:
//    a.swap(b);
//    assert(a.size()==5); //check if their sizes are swapped
//    assert(b.size()==0); //check if sizes are swapped
//    assert(b.find(v)==-1);
//    assert(b.insert(v) != -1); //check if you're able to insert stuff into b now
//    assert(b.find(v)==0); //check if the first instance of v is at 0
//    assert(a.insert(v) == -1);
//    Sequence d = a;
//    assert(d.insert(v) == -1);
//    a = b;
//    assert(a.insert(v) != -1);
//    assert(a.find(0)==0);
//    assert(a.size()==2);
//    
//     return 0;
//    
//}
