//
//  main.cpp
//  HW2
//
//  Created by Melody Chen on 4/26/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};
/*
Push the starting coordinate (sr,sc) onto the coordinate stack and
update maze[sr][sc] to indicate that the algorithm has encountered
it (i.e., set maze[sr][sc] to have a value other than '.').
While the stack is not empty,
{   Pop the top coordinate off the stack. This gives you the current
    (r,c) location that your algorithm is exploring.
    If the current (r,c) coordinate is equal to the ending coordinate,
    then we've solved the maze so return true!
    Check each place you can move from the current cell as follows:
    If you can move SOUTH and haven't encountered that cell yet,
    then push the coordinate (r+1,c) onto the stack and update
    maze[r+1][c] to indicate the algorithm has encountered it.
    If you can move WEST and haven't encountered that cell yet,
    then push the coordinate (r,c-1) onto the stack and update
    maze[r][c-1] to indicate the algorithm has encountered it.
    If you can move NORTH and haven't encountered that cell yet,
    then push the coordinate (r-1,c) onto the stack and update
    maze[r-1][c] to indicate the algorithm has encountered it.
    If you can move EAST and haven't encountered that cell yet,
    then push the coordinate (r,c+1) onto the stack and update
    maze[r][c+1] to indicate the algorithm has encountered it.
}
There was no solution, so return false
*/
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    coordStack.push((Coord(sr, sc)));
    maze[sr][sc] = 'e';
    int x =0;
    while(!coordStack.empty())
    {
        x++;
        Coord current = coordStack.top();
        cout<<x<<" r: "<<current.r()<<" c: "<<current.c()<<endl;
        coordStack.pop();
        if(current.r()==er && current.c()==ec)
            return true; //maze solved
        //check if you can move south
        if(maze[current.r()+1][current.c()]=='.'){
            coordStack.push(Coord(current.r()+1, current.c()));
            maze[current.r()+1][current.c()]='e';
        }
        //move west
        if(maze[current.r()][current.c()-1]=='.'){
            coordStack.push(Coord(current.r(), current.c()-1));
            maze[current.r()][current.c()-1]='e';
        }
        //move north
        if(maze[current.r()-1][current.c()]=='.'){
            coordStack.push(Coord(current.r()-1, current.c()));
            maze[current.r()-1][current.c()]='e';
        }
        //move east
        if(maze[current.r()][current.c()+1]=='.'){
            coordStack.push(Coord(current.r(), current.c()+1));
            maze[current.r()][current.c()+1]='e';
        }
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
