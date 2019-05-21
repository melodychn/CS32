//
//  Player.hpp
//  Project 3
//
//  Created by Melody Chen on 5/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include <iostream>
#include "Board.h"
#include "Side.h"
using namespace std;

class Player
{
public:
    Player(std::string name);
    //Create a Player with the indicated name.
    std::string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    //Since this class is designed as a base class, it should have a virtual destructor.
private:
    std::string m_name;
};

class HumanPlayer: public Player
{
public:
    HumanPlayer(std::string name);
    bool isInteractive() const;
    int chooseMove(const Board& b, Side s) const;
};

class BadPlayer: public Player
{
public:
    BadPlayer(std::string name);
    int chooseMove(const Board& b, Side s) const;
private:
    void smartMove(const Board& board, const Side player, const Side& originalPlayer,
                              int& bestHole, int& value, int& counter) const;
};

//Alarm clock to limit how long a choose move runs
#include <chrono>
#include <future>
#include <atomic>
//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================
class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};

class SmartPlayer: public Player
{
public:
    SmartPlayer(std::string name);
    int chooseMove(const Board& b, Side s) const;
private:
    void chooseMove1(AlarmClock& ac,const Board&b, Side original, Side player, int& besthole, int& value, int& deepness) const;
};

////for testing purposes
//class SmartPlayer2: public Player
//{
//public:
//    SmartPlayer2(std::string name);
//    int chooseMove(const Board& b, Side s) const;
//private:
//    void chooseMove1(AlarmClock& ac, const Board& b, Side original, Side player, int& besthole, int& value, int& deepness) const;
//};

#endif /* Player_h */
