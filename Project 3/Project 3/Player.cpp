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
    chooseMove1(b, s, s, besthole, value, deepness); //run recursive tree to find the best move
    cout<<"Besthole: "<<besthole<<" Value: "<<value<<endl;
    return besthole;
}


void SmartPlayer::chooseMove1(const Board&b, Side original, Side player, int& besthole, int& value, int& deepness) const
{
    Side opp = original==Side::NORTH?Side::SOUTH:Side::NORTH; //original opposite, doesn't change throughout recursion
    if(b.beansInPlay(Side::SOUTH)==0||b.beansInPlay(Side::NORTH)==0){ //if one side is winner i.e. no more beans on one side
        besthole = -1;
        Board temp(b); //need a temp board
        for(int k = 0; k<b.holes(); k++){ //need to move all beans to pot, since there is a winner
            temp.moveToPot(Side::SOUTH, k+1, Side::SOUTH);
            temp.moveToPot(Side::NORTH, k+1, Side::NORTH);
        }
        if(temp.beans(player, 0) == temp.beans(player==Side::NORTH?Side::SOUTH:Side::NORTH, 0)) //if there's a tie
            value = 0;
        else if(temp.beans(original, 0) > temp.beans(opp, 0)) //check who won
            value = 9999;
        else
            value = -9999;
        return;
    }else if(deepness>3){ //deepness value can vary
        besthole = -1;
        //value = (b.beans(original, 0)) - (b.beans(opp, 0)); //heuristic
        value = (b.beans(original, 0)+0.5*b.beansInPlay(original)) - (b.beans(opp, 0)+b.beansInPlay(opp)); //heuristic
        return;
        
    }
    //if doesn't fit above two criterions above
    for(int k=0; k<b.holes(); k++){
        if(b.beans(player, k+1)!=0){ //check if hole is empty, only go ahead if hole is not empty
            //"make" the move
            Board temp(b); //temporary board
            Side temp_s; //temporary side
            int temp_hole = -1, temp_value=0, temp_besthole=-2; //temporary value to plug in later, besthole -2 to ensure no overlap with other hole values
            temp.sow(player, k+1, temp_s, temp_hole);
            //if you sow and end up in your own hole, you will choose again for yourself
            if(player==temp_s && temp_hole ==0){
                int tempdeep = deepness; //deepness is not incremented, because still same player's turn
                chooseMove1(temp, original, player, temp_besthole, temp_value, tempdeep); //go again
            }else{
                Side temp_opp = player==Side::NORTH?Side::SOUTH:Side::NORTH; //current opposite, depends on current player
                //capture code
                if(player==temp_s&&temp_hole!=0&&temp.beans(temp_s, temp_hole)==1
                   &&temp.beans(temp_opp, temp_hole)!=0){ //check for a capture
                    temp.moveToPot(temp_opp, temp_hole, player); //move opp beans to ur own pot
                    temp.moveToPot(player, temp_hole, player); //move ur own beans at that hole to ur pot
                }
                int tempdeep = deepness +1; //increment deepness for following recursion
                chooseMove1(temp, original, temp_opp, temp_besthole, temp_value, tempdeep); //do move for current player's opponent
            }
            //check whether to update value and besthole or not
            if(besthole==-2||(original==player&&temp_value>value)){ //for original player
                besthole = k+1;
                value = temp_value;
            }else if(original!=player&&temp_value<value){ //for not original player
                besthole = k+1;
                value = temp_value;
            }
        }
    }
    return;
}

SmartPlayer2::SmartPlayer2(string name):Player(name)
{
    
}

int SmartPlayer2::chooseMove(const Board& b, Side s) const
{
    int besthole=-2, value=0, deepness = 0;
    chooseMove1(b, s, s, besthole, value, deepness); //run recursive tree to find the best move
    cout<<"Besthole: "<<besthole<<" Value: "<<value<<endl;
    return besthole;
}


void SmartPlayer2::chooseMove1(const Board&b, Side original, Side player, int& besthole, int& value, int& deepness) const
{
    Side opp = original==Side::NORTH?Side::SOUTH:Side::NORTH; //original opposite, doesn't change throughout recursion
    if(b.beansInPlay(Side::SOUTH)==0||b.beansInPlay(Side::NORTH)==0){ //if one side is winner i.e. no more beans on one side
        besthole = -1;
        Board temp(b); //need a temp board
        for(int k = 0; k<b.holes(); k++){ //need to move all beans to pot, since there is a winner
            temp.moveToPot(Side::SOUTH, k+1, Side::SOUTH);
            temp.moveToPot(Side::NORTH, k+1, Side::NORTH);
        }
        if(temp.beans(player, 0) == temp.beans(player==Side::NORTH?Side::SOUTH:Side::NORTH, 0)) //if there's a tie
            value = 0;
        else if(temp.beans(original, 0) > temp.beans(opp, 0)) //check who won
            value = 9999;
        else
            value = -9999;
        return;
    }else if(deepness>3){ //deepness value can vary
        besthole = -1;
        //value = (b.beans(original, 0)) - (b.beans(opp, 0)); //heuristic
        value = (b.beans(original, 0)) - (b.beans(opp, 0)); //heuristic
        return;
    }
    //if doesn't fit above two criterions above
    for(int k=0; k<b.holes(); k++){
        if(b.beans(player, k+1)!=0){ //check if hole is empty, only go ahead if hole is not empty
            //"make" the move
            Board temp(b); //temporary board
            Side temp_s; //temporary side
            int temp_hole = -1, temp_value=0, temp_besthole=-2; //temporary value to plug in later, besthole -2 to ensure no overlap with other hole values
            temp.sow(player, k+1, temp_s, temp_hole);
            //if you sow and end up in your own hole, you will choose again for yourself
            if(player==temp_s && temp_hole ==0){
                int tempdeep = deepness; //deepness is not incremented, because still same player's turn
                chooseMove1(temp, original, player, temp_besthole, temp_value, tempdeep); //go again
            }else{
                Side temp_opp = player==Side::NORTH?Side::SOUTH:Side::NORTH; //current opposite, depends on current player
                //capture code
                if(player==temp_s&&temp_hole!=0&&temp.beans(temp_s, temp_hole)==1
                   &&temp.beans(temp_opp, temp_hole)!=0){ //check for a capture
                    temp.moveToPot(temp_opp, temp_hole, player); //move opp beans to ur own pot
                    temp.moveToPot(player, temp_hole, player); //move ur own beans at that hole to ur pot
                }
                int tempdeep = deepness +1; //increment deepness for following recursion
                chooseMove1(temp, original, temp_opp, temp_besthole, temp_value, tempdeep); //do move for current player's opponent
            }
            //check whether to update value and besthole or not
            if(besthole==-2||(original==player&&temp_value>value)){ //for original player
                besthole = k+1;
                value = temp_value;
            }else if(original!=player&&temp_value<value){ //for not original player
                besthole = k+1;
                value = temp_value;
            }
        }
    }
    return;
}
