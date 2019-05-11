//
//  main.cpp
//  HW3
//
//  Created by Melody Chen on 5/4/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};

//declarations and implementations

class Medium
{
public:
    Medium(string id); //cannot have a default constructor
    virtual string connect() const = 0; //pure virtual, makes medium an abstract class
    string id() const; //same for all derived class, return id of particular kind of medium
    virtual string transmit(string msg) const; //don't need to be virtual, some class will just use base class version
    virtual ~Medium(); //virtual destructor
private:
    string m_id;
};

Medium::Medium(string id):m_id(id)
{}

string Medium::id() const
{
    return m_id;
}

string Medium::transmit(string msg) const
{
    return "text: " + msg;
};

Medium::~Medium() //need to implement, but nothing to delete or print
{}

class TwitterAccount: public Medium //derived class of Medium
{
public:
    TwitterAccount(string id);
    virtual string connect() const;
    virtual ~TwitterAccount();
};

TwitterAccount::TwitterAccount(string id):Medium(id)
{}

string TwitterAccount::connect() const
{
    return "Tweet";
}

TwitterAccount::~TwitterAccount()
{
    cout<<"Destroying the Twitter account " + id() +"."<<endl;
}

class Phone: public Medium //derived class of Medium
{
public:
    Phone(string id, CallType type);
    virtual string connect() const;
    virtual string transmit(string msg) const;
    virtual ~Phone();
private:
    CallType m_type;
};

Phone::Phone(string id, CallType type):Medium(id), m_type(type)
{}

string Phone::connect() const
{
    return "Call";
}

string Phone::transmit(string msg) const
{
    string temp;
    if(m_type==CallType::VOICE)
        temp = "voice";
    else
        temp = "text";
    return temp + ": " + msg;
}

Phone::~Phone()
{
    cout<<"Destroying the phone "<<id()<<"."<<endl;
}

class EmailAccount: public Medium //derived class of Medium
{
public:
    EmailAccount(string id);
    virtual string connect() const;
    virtual ~EmailAccount();
};

EmailAccount::EmailAccount(string id):Medium(id)
{}

string EmailAccount::connect() const
{
    return "Email";
}

EmailAccount::~EmailAccount()
{
    cout<<"Destroying the email account "<<id()<<"."<<endl;
}

void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
    << ", sending " << m->transmit(msg) << endl;
}

int main()
{
    Medium* media[4];
    media[0] = new TwitterAccount("UCLABruinAlert");
    // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");

    cout << "Send the message." << endl;
    for (int k = 0; k < 4; k++)
        send(media[k], "Major power outage in West L.A.");

    // Clean up the media before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete media[k];
}
