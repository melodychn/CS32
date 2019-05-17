//
//  main.cpp
//  Project 3
//
//  Created by Melody Chen on 5/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;
#include "Board.h"
#include "Player.h"
#include "Game.h"
int main() {
    Board h(4,3); //board with 5 holes each with 3 beans
    SmartPlayer Josh("Josh");
//Josh.chooseMove(h, Side::SOUTH);
//    assert(h.holes()==5);
//    assert(h.beans(Side::NORTH, 0)==0);
//    assert(h.beans(Side::SOUTH, 0)==0);
//    assert(h.beans(Side::NORTH, 1)==3);
//    assert(h.beans(Side::NORTH, 3)==3);
//    assert(h.beans(Side::NORTH, 5)==3);
//    assert(h.beans(Side::NORTH, 6)==-1);
//    assert(h.beansInPlay(Side::NORTH)==15);
//    assert(h.beansInPlay(Side::SOUTH)==15);
//    assert(h.totalBeans()==30);
//    Side s;
//    int end=-1;;
//    Board z(6,15);
//    z.sow(Side::NORTH, 1, s, end);
//    assert(z.beans(Side::SOUTH, 0)==0);
//    assert(z.beans(Side::NORTH, 0)==2);
//    assert(end==1);
//    assert(s==Side::SOUTH);
//    assert(z.beans(Side::NORTH, 1)==0);
//    assert(z.beans(Side::NORTH, 4)==16);
//    assert(z.beans(Side::SOUTH, 1)==17);
//    Board c(6,20);
//    c.sow(Side::SOUTH, 2, s, end);
//    assert(c.beans(Side::NORTH, 0)==0);
//    assert(end==5);
//    assert(s==Side::NORTH);
//    assert(c.beans(Side::NORTH, 3)==21);
//    assert(c.beans(Side::SOUTH, 2)==0);
//    cerr<<"Passed all test cases!"<<endl;
//    SmartPlayer Josh("Josh");
    BadPlayer Melody("Melody");
    Game test(h, &Josh, &Melody);
    test.play();
    return 0;
}

