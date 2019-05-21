//
//  Game.cpp
//  Project 3
//
//  Created by Melody Chen on 5/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Side.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
    :m_board(b), m_south(south), m_north(north), current(south), s_current(Side::SOUTH), m_over(false)
//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
{
}

void Game::display() const
//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
{
    cout<<m_north->name()<<endl;
    string spaces = "  ";
    cout<<spaces;
    for(int k=0; k<m_board.holes(); k++)
        cout<<k+1<<spaces; //print out numbering
    cout<<endl;
    cout<<spaces;
    for(int k=0; k<m_board.holes(); k++)
        cout<<m_board.beans(Side::NORTH, k+1)<<spaces; //print out north holes excluding pots
    cout<<endl; //go to next line
    cout<<" "<<m_board.beans(Side::NORTH, 0);
    for(int k=0; k<m_board.holes()+2;k++)
        cout<<spaces;
    cout<<m_board.beans(Side::SOUTH, 0)<<endl;
    cout<<spaces;
    for(int k=0; k<m_board.holes(); k++)
        cout<<m_board.beans(Side::SOUTH, k+1)<<spaces; //print out south holes excluding pots
    cout<<endl;
    cout<<spaces;
    for(int k=0; k<m_board.holes(); k++)
        cout<<k+1<<spaces; //print out numbering
    cout<<endl;
    cout<<m_south->name()<<endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
{
    //determine if more moves are possible
    if(m_board.beansInPlay(Side::NORTH)==0&&m_board.beansInPlay(Side::SOUTH)==0){
        over = true;
        if(m_board.beans(Side::SOUTH, 0)==m_board.beans(Side::NORTH, 0))
            //tie if both sides have same # beans in pot
            hasWinner = false;
        else{ //there is no tie
            hasWinner = true;
            winner = m_board.beans(Side::SOUTH, 0)>m_board.beans(Side::NORTH, 0)?Side::SOUTH:Side::NORTH;
        }
    }else{
        over = false;
    }
}

bool Game::move()
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
{
    display();
    if(m_board.beansInPlay(Side::NORTH)==0||m_board.beansInPlay(Side::SOUTH)==0){
        moveAllBeansToPot();
        return false;
    }
    //if game is not over, make a complete move for current player
    int move = current->chooseMove(m_board, s_current), endHole;
    Side endSide;
    if(!m_board.sow(s_current, move, endSide, endHole)) //start sowing
        cerr << "Error with sowing!" <<endl;
    display();
    while (endSide==s_current) {
        if(m_board.beansInPlay(Side::NORTH)==0||m_board.beansInPlay(Side::SOUTH)==0){
            moveAllBeansToPot();
            return false;
        }
        //check for capture
        Side opp = endSide==Side::NORTH?Side::SOUTH:Side::NORTH;
        if(endHole!=0&&m_board.beans(endSide, endHole)==1&&m_board.beans(opp, endHole)!=0){ //check if the endHole
            //perform a capture
            cout<<current->name()<<" performed a capture."<<endl;
            m_board.moveToPot(opp, endHole, s_current); //move beans to ur own pot
            m_board.moveToPot(s_current, endHole, s_current);
            //NEED TO UPDATE THE CURRENT PLAYER WHENEVER TURN ENDS
            current = current==m_south?m_north:m_south;
            s_current = s_current==Side::SOUTH?Side::NORTH:Side::SOUTH;
            return true; //ends turn if you did a capture
        }else if(endHole==0){ //you land in ur own pot
            //player gets another turn
            cout<<current->name()<<" gets another turn!"<<endl;
            display(); //display
            move = current->chooseMove(m_board, s_current);
            endHole = -1; //reset endhole
            if(!m_board.sow(s_current, move, endSide, endHole)) //start sowing
                cerr << "Error with sowing!" <<endl;
            display(); //display
        }else{
            break;
        }
    }
    cout<<current->name()<<"'s turn ends."<<endl;
    current = current==m_south?m_north:m_south;
    s_current = s_current==Side::SOUTH?Side::NORTH:Side::SOUTH;
    return true;
}

void Game::play()
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
{
    do{
        move();
        cout<<"Press enter to continue.";
        cin.ignore(10000,'\n');
        cout<<endl;
        status(m_over, m_hasWinner, m_winner);
    }while(!m_over);
    display();
    if(m_hasWinner){
        string winner = m_winner==Side::NORTH?m_north->name():m_south->name();
        cout<<"The winner is "<<winner<<"."<<endl;
    }else
        cout<<"It is a tie."<<endl;
}

int Game::beans(Side s, int hole) const
//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
{
    return m_board.beans(s, hole);
}

void Game::moveAllBeansToPot()
{
    string winner = m_board.beansInPlay(Side::NORTH)==0?m_south->name():m_north->name();
    cout<<"Sweeping remaining beans into "<<winner<<"'s pot."<<endl;
    for(int k = 0; k<m_board.holes(); k++){
        m_board.moveToPot(Side::SOUTH, k+1, Side::SOUTH);
        m_board.moveToPot(Side::NORTH, k+1, Side::NORTH);
    }
}
