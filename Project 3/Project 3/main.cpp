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
    //test cases for board
//    Board h(5,3); //board with 5 holes each with 3 beans
//    assert(h.holes()==5); //test if holes work correctly
//    assert(h.beans(Side::NORTH, 0)==0); //check for initial number of beans in pot to be zero
//    assert(h.beans(Side::SOUTH, 0)==0);
//    assert(h.beans(Side::NORTH, 1)==3); //check holes for initial bean number to be 3
//    assert(h.beans(Side::NORTH, 3)==3);
//    assert(h.beans(Side::NORTH, 5)==3);
//    assert(h.beans(Side::NORTH, 6)==-1); //check when looking for beans in an invalid hole
//    assert(h.beansInPlay(Side::NORTH)==15); //correct beansInPlay number
//    assert(h.beansInPlay(Side::SOUTH)==15);
//    assert(h.totalBeans()==30); //correct total beans number
//    Side s;
//    int end;
//    Board z(6,15);
//    z.sow(Side::NORTH, 1, s, end); //check for sowing
//    assert(z.beans(Side::SOUTH, 0)==0); //test for if sowed correctly
//    assert(z.beans(Side::NORTH, 0)==2);
//    assert(end==1); //test for the right end spot
//    assert(s==Side::SOUTH); //test for the right end side
//    assert(z.beans(Side::NORTH, 1)==1); //test for correct number of beans sowed
//    assert(z.beans(Side::NORTH, 4)==16);
//    assert(z.beans(Side::SOUTH, 1)==17);
//    Board c(6,20); //check for sowing with large number
//    c.sow(Side::SOUTH, 2, s, end);
//    assert(c.beans(Side::NORTH, 0)==0); //no beans should be sowed into north's pot
//    assert(end==5); //check for correct sowing
//    assert(s==Side::NORTH);
//    assert(c.beans(Side::NORTH, 3)==21);
//    assert(c.beans(Side::SOUTH, 2)==1);
//    Board d(5, 4);
//    assert(d.moveToPot(Side::NORTH, 1, Side::SOUTH)==true); //test for moveToPot
//    assert(d.beans(Side::NORTH, 1)==0);
//    assert(d.beans(Side::SOUTH,0)==4);
//    assert(d.moveToPot(Side::NORTH, 0, Side::SOUTH)==false); //test for moveToPot faulty
//    assert(d.beans(Side::NORTH, 1)==0); //nothing should be changed
//    assert(d.beans(Side::SOUTH,0)==4);
//    assert(d.moveToPot(Side::NORTH, 1, Side::SOUTH)==true); //test for moveToPot
//    assert(d.beans(Side::NORTH, 1)==0); //no beans should be moved
//    assert(d.beans(Side::SOUTH,0)==4);
//    assert(d.setBeans(Side::SOUTH, 0, -10)==false); //test invalid num for set beans
//    assert(d.setBeans(Side::SOUTH, 0, 0)==true); //valid set bean number
//    assert(d.beans(Side::SOUTH,0)==0);
//    assert(d.setBeans(Side::SOUTH, 6, 5)==false); //test invalid num for set beans
//    Board aa(d); //check if copy constructor works correctly
//    assert(aa.totalBeans()==36); //check if number of beans corresponds to board d
//    assert(aa.beansInPlay(Side::SOUTH)==20);
//    assert(aa.beansInPlay(Side::NORTH)==16);
//    assert(aa.beans(Side::SOUTH, 0)==0);
//    assert(aa.moveToPot(Side::SOUTH, 1, Side::NORTH));
//    assert(aa.beans(Side::NORTH, 0)==4); //should be changed
//    assert(d.beans(Side::NORTH, 0)==0); //should not be changed
//    c = aa; //test if assignment operator works properly
//    assert(c.beans(Side::NORTH, 0)==4); //should be the same as aa
//    assert(c.setBeans(Side::NORTH, 1, 10)==true);
//    assert(c.beans(Side::NORTH, 1)==10); //c should be updated
//    assert(aa.beans(Side::NORTH, 1)==0); //aa should not change
//
//    //test cases for player
//    HumanPlayer e("Josh");
//    assert(e.isInteractive()==true); //human player should be interactive
//    assert(e.name()=="Josh"); //test if name works correctly
//    BadPlayer f("Josh");
//    assert(f.isInteractive()==false); //bad player should not be interactive
//    assert(f.name()=="Josh"); //test if name works correctly
//    assert(f.chooseMove(d, Side::NORTH)>1&&f.chooseMove(d, Side::NORTH)<=5); //choose move needs to choose move within range
//    SmartPlayer g("Josh");
//    assert(g.isInteractive()==false); //smart player should not be interactive
//    assert(g.name()=="Josh"); //test if name works correctly
//    assert(g.chooseMove(d, Side::NORTH)>1&&g.chooseMove(d, Side::NORTH)<=5); //choose move needs to choose move within range
//
//    //test cases for Game
//    Game i(c, &f, &g);
//    bool over, haswinner=false;
//    Side winner;
//    i.status(over, haswinner, winner); //test for status
//    assert(over==false);
//    assert(haswinner==false);
//    c.setBeans(Side::SOUTH, 0, 4); //set up for a tied scenario
//    for(int k=0; k<c.holes(); k++){
//        c.setBeans(Side::NORTH, k+1, 0);
//        c.setBeans(Side::SOUTH, k+1, 0);
//    }
//    Game j(c, &f, &g);
//    j.status(over, haswinner, winner); //check status on tied scenario
//    assert(over==true);
//    assert(haswinner==false); //should be no winners
//    c.setBeans(Side::SOUTH, 0, 5); //set up for scenario where there is a winner
//    Game k(c, &f, &g);
//    k.status(over, haswinner, winner); //check status on no tied scenario
//    assert(over==true);
//    assert(haswinner==true); //should be a winner
//    assert(winner==Side::SOUTH);
//    assert(k.move()==false); //test move method
//    c.setBeans(Side::NORTH, 1, 5);
//    Game l(c, &f, &g);
//    c.display();
//    assert(l.move()==false); //should not be able to move
//
//    cerr<<"Passed all test cases!"<<endl;
    return 0;
}


