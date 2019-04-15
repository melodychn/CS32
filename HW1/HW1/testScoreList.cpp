//
//  main.cpp
//  HW1
//
//  Created by Melody Chen on 4/10/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include "Sequence.h"
using namespace std;
int main(int argc, const char * argv[]) {

    // insert code here...
    
    Sequence h;
    Sequence g;
    h.insert(0, "hi");
    h.insert(0, "hey");
    h.insert(0, "sup");
    h.insert(3, "third");
    cout<<"h: "<<endl;
    h.dump();
    g.insert(0, "hii");
    g.insert(0, "heyy");
    g.insert(0, "supp");
    g.insert(0, "difdifj");
    cout<<"g: "<<endl;
    g.dump();
    h.swap(g);
    cout<<"gswap: "<<endl;
    g.dump();
    cout<<"hswap: "<<endl;
    h.dump();
    
    Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
           s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
    Sequence s;
    s.insert(0, "dosa");
    s.insert(1, "pita");
    s.insert(2, "");
    s.insert(3, "matzo");
    assert(s.find("") == 2);
    s.remove("dosa");
    assert(s.size() == 3  &&  s.find("pita") == 0  &&  s.find("") == 1  &&
           s.find("matzo") == 2);
    return 0;
 
//    ScoreList k;
//    k.add(15);
//    k.add(10);
//    k.add(15);
//    k.add(15);
//    k.add(0);
//    k.add(-10);
//    k.remove(15);
//    k.add(100);
//    k.dump();
//    cout<<k.maximum()<<endl;

}

