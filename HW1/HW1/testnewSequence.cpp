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
//    
//    // When two Sequences' contents are swapped, their capacities are
//    // swapped as well:
//    a.swap(b);
//    a.dump();
//    cout<<"a size: "<<a.size()<<endl;
//    cout<<"b size: "<<b.size()<<endl;
//    b.dump();
//    assert(b.insert(v) != -1);
//    assert(a.insert(v) == -1);
//    
//    
//     return 0;
//    
//}
