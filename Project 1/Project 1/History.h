//
//  History.hpp
//  Project 1
//
//  Created by Melody Chen on 4/3/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class Arena;
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_Rows;
    int m_Cols;
    int grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
