//
//  maze.cpp
//  HW3
//
//  Created by Melody Chen on 5/10/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);


/*
 If the start location is equal to the ending location, then we've
 solved the maze, so return true.
 Mark the start location as visted.
 For each of the four directions,
 If the location one step in that direction (from the start
 location) is unvisited,
 then call pathExists starting from that location (and
 ending at the same ending location as in the
 current call).
 If that returned true,
 then return true.
 Return false.
 */
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if(sr==er && sc==ec) //if start loc = end loc
        return true;
    maze[sr][sc]='e';
    //move south
    if(maze[sr+1][sc]=='.'){
        if(pathExists(maze, sr+1, sc, er, ec))
            return true;
    }
    //move west
    if(maze[sr][sc-1]=='.'){
        if(pathExists(maze, sr, sc-1, er, ec))
            return true;
    }
    //move north
    if(maze[sr-1][sc]=='.'){
        if(pathExists(maze, sr-1, sc, er, ec))
            return true;
    }
    //move east
    if(maze[sr][sc+1]=='.'){
        if(pathExists(maze, sr, sc+1, er, ec))
            return true;
    }
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
