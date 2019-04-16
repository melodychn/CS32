//
//  ScoreList.cpp
//  HW1
//
//  Created by Melody Chen on 4/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList()
{
    
}

bool ScoreList::add(unsigned long score)
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
{
    if(score<=100 && m_list.insert(m_list.size(), score)!=-1)
        return true;
    return false;
}

bool ScoreList::remove(unsigned long score)
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
{
    int pos = m_list.find(score);
    if(pos!=-1){
        m_list.erase(pos);
        return true;
    }
    return false;
}

int ScoreList::size() const // Return the number of scores in the list.
{
    return m_list.size();
}

unsigned long ScoreList::minimum() const
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
{
    if(m_list.size()==0)
        return NO_SCORE;
    unsigned long min = NO_SCORE;
    unsigned long temp = 0;
    for(int k = 0; k<m_list.size(); k++){
        m_list.get(k, temp);
        if(temp < min)
            min = temp;
    }
    return min;
}

unsigned long ScoreList::maximum() const
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
{
    if(m_list.size()==0)
        return NO_SCORE;
    unsigned long min = 0;
    unsigned long temp = 0;
    for(int k = 0; k<m_list.size(); k++){
        m_list.get(k, temp);
        if(temp > min)
            min = temp;
    }
    return min;
}
