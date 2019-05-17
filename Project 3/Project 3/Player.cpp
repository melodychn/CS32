//
//  Player.cpp
//  Project 3
//
//  Created by Melody Chen on 5/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "Player.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

Player::Player(string name):m_name(name)
{
}

string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
{
    return false;
}

Player::~Player()
{
}

HumanPlayer::HumanPlayer(string name):Player(name)
{
}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    int response = -999;
    bool cont = true; //whether to keep asking for response
    while(cont){
        cout<<"Select a hole, "<<name()<<": ";
        cin>>response;
        if(!(response>0&&response<=b.holes())){ //if hole is out of range
            cont = true;
            cout<<"The hole must be from 1 to "<<b.holes()<<"."<<endl;
        }else if(b.beans(s, response)==0){ //if hole is empty
            cout<<"There are no beans in that hole."<<endl;
            cont = true;
        }else{
            cont = false;
        }
    }
    return response;
}

BadPlayer::BadPlayer(string name):Player(name)
{
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
//    srand(time(0)); //initialize random number generator
//    int r = (rand()%b.holes())+1; //pick a random hole within range of holes
//    while(b.beans(s, r)==0) //if hole is empty, then pick another hole
//        r = (rand()%b.holes())+1;
//    cout<<Player::name()<<" chooses hole "<<r<<"."<<endl;
//    return r;
    for(int i = 1; i < b.holes()+1; i++){
        if(b.beans(s, i)!=0){
            cout<<Player::name()<<" chooses hole "<<i<<"."<<endl;
            return i;
        }
    }
    
    return 1;
}

SmartPlayer::SmartPlayer(string name):Player(name)
{
    
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int besthole=-2, value=0, deepness = 0;
    chooseMove1(b, s, s, besthole, value, deepness);
    cout<<"Besthole: "<<besthole<<" Value: "<<value<<endl;
    return besthole;
}

//void chooseMove(in: player, board; out: bestHole, value):
//if no move for player exists (i.e., game is over),
//bestHole = -1
//value = value of this position (i.e., +∞, -∞, or 0)
//return
//if the criterion says we should not search below this node
//bestHole = -1
//value = value of this position
//return
//for every hole h the player can choose
//"make" the move h
//chooseMove(opponent, h2, v2)
//"unmake" the move
//if v2 is better for the player than best seen so far,
//bestHole = h
//value = v2
//return

void SmartPlayer::chooseMove1(const Board&b, Side original, Side player, int& besthole, int& value, int& deepness) const
{
    Side opp = original==Side::NORTH?Side::SOUTH:Side::NORTH;
    int opp_beans_tot = (b.beans(opp, 0)+b.beansInPlay(opp));
    if(b.beansInPlay(Side::SOUTH)==0||b.beansInPlay(Side::NORTH)==0){
        besthole = -1;
        Board temp(b); //need a temp board
        //need to move all beans to pot
        for(int k = 0; k<b.holes(); k++){
            temp.moveToPot(Side::SOUTH, k+1, Side::SOUTH);
            temp.moveToPot(Side::NORTH, k+1, Side::NORTH);
        }
        //need to get value of this location, determine whether you have won or not
        if(temp.beans(player, 0) == temp.beans(player==Side::NORTH?Side::SOUTH:Side::NORTH, 0))
            value = 0;
        else if(temp.beans(original, 0) > temp.beans(opp, 0))
            value = 9999;
        else
            value = -9999;
        return;
    }else if(deepness>2){ //60% of beans belongs to opponents side, should give up
        besthole = -1;
        value = b.beans(original, 0) - b.beans(opp, 0); //THIS NEEDS TO SOMEHOW BE CHANGED
        return;
    }
    //if doesn't fit above two criterions
    for(int k=0; k<b.holes(); k++){
        if(b.beans(player, k+1)!=0){
            //"make" the move
            Board temp(b);
            Side temp_s;
            int temp_hole = -1, temp_value=0, temp_besthole=-2, tempdeep = deepness +1;
            temp.sow(player, k+1, temp_s, temp_hole);
            //if you sow and end up in your own hole, you will choose again for yourself
            if(player==temp_s && temp_hole ==0){
                
            }
            //opposite should be opposite of player
            Side temp_opp = player==Side::NORTH?Side::SOUTH:Side::NORTH;
            chooseMove1(temp, original, temp_opp, temp_besthole, temp_value, tempdeep);
            //What if you sow and its your turn again?
            //depends on who the player is
            //for when you're the original player
            //first time you go through, need at least one besthole value but PROBLEM
            //PLEASE UPDATE BEST HOLE == VALUE TMR
            if(besthole==-2||(original==player&&temp_value>value)){
                besthole = k+1;
                value = temp_value;
            }else if(original!=player&&temp_value<value){
                besthole = k+1;
                value = temp_value;
            }
        }
    }
    return;
}
