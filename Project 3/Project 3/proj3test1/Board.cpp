//
//  Board.cpp
//  Project 3
//
//  Created by Melody Chen on 5/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if(nHoles<=0)
        m_holes = 1;
    else
        m_holes = nHoles;
    if(nInitialBeansPerHole < 0)
        m_initialBeansPerHole  = 0;
    else
        m_initialBeansPerHole = nInitialBeansPerHole;
    north_holes = new int[m_holes+1]; //initialize each hole to designated size + add a slot for pot
    south_holes = new int[m_holes+1];
    for(int k = 0; k<m_holes; k++){ //initialize beans in each hole, slot 0 is reserved for pot
        north_holes[k+1] = m_initialBeansPerHole;
        south_holes[k+1] = m_initialBeansPerHole;
    }
    //intialize pot values to 0
    north_holes[0] = 0;
    south_holes[0] = 0;
}

Board::Board(const Board& other) //appropriate assignment operator
{
    m_holes = other.m_holes;
    m_initialBeansPerHole = other.m_initialBeansPerHole;
    north_holes = new int[m_holes+1];
    south_holes = new int[m_holes+1];
    for(int k = 0; k<m_holes+1; k++){
        north_holes[k] = other.north_holes[k];
        south_holes[k] = other.south_holes[k];
    }
}

Board::~Board()
{
    delete[] north_holes;
    delete[] south_holes;
}

int Board::holes() const
{
    return m_holes;
}

int Board::beans(Side s, int hole) const
{ //be careful of numbeing of holes
    if(hole<0||hole>m_holes) //invalid hole #
        return -1;
    return s==Side::NORTH?north_holes[hole]:south_holes[hole];
}

int Board::beansInPlay(Side s) const
{
    int count = 0;
    int* temp = s==Side::NORTH?north_holes:south_holes;
    for(int k = 0; k<m_holes; k++)
        count+=temp[k+1];
    return count;
}

int Board::totalBeans() const
{
    int count = 0;
    count+=beansInPlay(Side::NORTH);
    count+=beansInPlay(Side::SOUTH);
    count+=north_holes[0];
    count+=south_holes[0];
    return count;
}

void Board::addBeans(Side s, int hole, int beans) //helper function that adds beans to a hole
{
    int* temp = s==Side::NORTH?north_holes:south_holes;
    temp[hole]+=beans;
}

bool Board::shiftBeansOneSide(Side sorg, Side& s, int& beans_to_move, int hole, int& endHole, Side& endSide)
{
    int beans_moved;
    int hole_index = s==Side::NORTH?hole-1:hole+1;
    if(s==Side::NORTH&&endHole==0){
        hole_index = 1;
        s=Side::SOUTH;
    }else if(s==Side::SOUTH&&endHole==m_holes){
        hole_index = m_holes;
        //special condition when you reach end of south
        if(s==sorg&&sorg==Side::SOUTH){ //when you DONT skip south's pot and dump into it
            addBeans(s, 0, 1);
            beans_to_move--;
        }
        if(beans_to_move==0) //when you dump last seed into south's pot, don't need to switch sides
            hole_index=1;
        else //switch sides otherwise
            s=Side::NORTH;
    }
    //move beans until no beans left or hit end of one side
    //if you're south, increment index; if you're north deccrement index
    for(beans_moved = 0; beans_moved<beans_to_move&&(s==Side::NORTH?hole_index>=0:hole_index<=m_holes);
        beans_moved++, s==Side::NORTH?hole_index--:hole_index++){
        if(s==Side::NORTH&&sorg==Side::SOUTH&&hole_index==0){
            beans_moved--;
            continue;
        }
        addBeans(s, hole_index, 1);
    }
    if(beans_moved==beans_to_move){ //if you've moved all the beans, you're done
        endHole = s==Side::NORTH?hole_index+1:hole_index-1;
        endSide = s;
        return true;
    }
    beans_to_move -= beans_moved;
    //if you still have beans left to move
    endHole = s==Side::NORTH?0:m_holes;
    return false;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if(hole==0||beans(s, hole)==-1||beans(s, hole)==0) //nothing changed
        return false;
    int beans_to_move = beans(s, hole);
    Side sorg = s;
    if(!shiftBeansOneSide(sorg, s, beans_to_move, hole, endHole, endSide)){
        while(!shiftBeansOneSide(sorg, s, beans_to_move, endHole, endHole, endSide))
        {}
    }
    int* temp = sorg==Side::NORTH?north_holes:south_holes;
    temp[hole] = 0; //set current hole to no beans
    return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if(hole==0||beans(s, hole)==-1)
        return false;
    addBeans(potOwner, 0, beans(s, hole));
    int* temp = s==Side::NORTH?north_holes:south_holes;
    temp[hole]=0;
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    if(Board::beans(s, hole)==-1||beans<0)
        return false;
    int* temp = s==Side::NORTH?north_holes:south_holes;
    temp[hole]= beans;
    return true;
}
