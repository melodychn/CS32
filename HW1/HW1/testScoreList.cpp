//
//  main.cpp
//  HW1
//
//  Created by Melody Chen on 4/10/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include "ScoreList.h"
#include <cassert>
using namespace std;
int main() {
    ScoreList k;
    k.add(15);
    k.add(10);
    k.add(15);
    k.add(15);
    assert(k.maximum()==15);
    assert(k.minimum()==10);
    assert(k.size()==4);
    k.add(0);
    assert(k.minimum()==0);
    assert(k.add(-10)==false);
    assert(k.remove(0)==true);
    assert(k.size()==4);
    k.add(0);
    assert(k.minimum()==0);
    ScoreList b = k;
    assert(b.minimum()==0);
    ScoreList c;
    c = k;
    assert(c.maximum()==15);
    cerr<<"Passed all test cases"<<endl;
}

