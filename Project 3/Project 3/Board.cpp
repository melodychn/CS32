//
//  Board.cpp
//  Project 3
//
//  Created by Melody Chen on 5/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole):m_holes(nHoles)
{
    
}

Board::~Board()
{
    
}

int Board::holes() const
{
    return -999;
}

int Board::beans(Side s, int hole) const
{
    return -999;
}

int Board::beansInPlay(Side s) const
{
    return -999;
}

int Board::totalBeans() const
{
    return -999;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    return false;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    return false;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    return false;
}
