//
//  main.cpp
//  HW1
//
//  Created by Melody Chen on 4/10/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include "ScoreList.h"
using namespace std;
int main(int argc, const char * argv[]) {

    // insert code here...
    /*
    Sequence h;
    Sequence g;
    h.insert(0, "hi");
    h.insert(0, "hey");
    h.insert(0, "sup");
    cout<<"h: "<<endl;
    h.dump();
    g.insert(0, "hii");
    g.insert(0, "heyy");
    g.insert(0, "supp");
    cout<<"g: "<<endl;
    g.dump();
    h.swap(g);
    cout<<"gswap: "<<endl;
    g.dump();
    cout<<"hswap: "<<endl;
    h.dump();
    return 0;
 */
    ScoreList k;
    k.add(15);
    k.add(10);
    k.add(15);
    k.add(15);
    k.add(0);
    k.add(-10);
    k.remove(15);
    k.add(100);
    k.dump();
    cout<<k.maximum()<<endl;

}

