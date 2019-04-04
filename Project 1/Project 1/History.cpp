//
//  History.cpp
//  Project 1
//
//  Created by Melody Chen on 4/3/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "History.h"
#include "Arena.h"
#include <iostream>
using namespace std;
History::History(int nRows, int nCols):m_Rows(nRows), m_Cols(nCols)
{
    for(int r = 0; r<m_Rows;r++){
        for(int c = 0; c<m_Cols;c++){
            grid[r][c]=0;
        }
    }
    
}


bool History::record(int r, int c)
{
    
    if(r<=m_Rows && c<=m_Cols){
        cout<<"recording: "<<r-1<<", "<<c-1<<endl;
        grid[r-1][c-1]++;
        return true;
    }
    return false;
}

void History::display() const
{
    // Position (row,col) of the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char gridprint[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < m_Rows; r++){
        for (c = 0; c < m_Cols; c++){
            if(grid[r][c]>=1){
                gridprint[r][c]= 'A'+ grid[r][c] - 1;
            }else{
                gridprint[r][c] = '.';
            }
        }
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_Rows; r++)
    {
        for (c = 0; c < m_Cols; c++)
            cout << gridprint[r][c];
        cout << endl;
    }
    cout << endl;
}
