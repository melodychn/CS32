//
//  bad.cpp
//  HW4
//
//  Created by Melody Chen on 5/25/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

vector<int> destroyedOnes;

class Movie
{
public:
    Movie(int r) : m_rating(r) {}
    ~Movie() { destroyedOnes.push_back(m_rating); }
    int rating() const { return m_rating; }
private:
    int m_rating;
};

// Remove the movies in li with a rating below 55 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator p = li.end();
    p--;
    list<Movie*>::iterator z = li.begin();
    z--;
    while(p!=z)
    {
        if((*p)->rating()<55){
            list<Movie*>::iterator i = p;
            p--;
            delete *i;
            li.erase(i);
        }else{
            p--;
        }
    }
}

void test()
{
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    list<Movie*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes.size() == 4);
    vector<int> v;
    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
    {
        Movie* mp = *p;
        v.push_back(mp->rating());
    }
    // Aside:  In C++11, the above loop could be
    //     for (auto p = x.begin(); p != x.end(); p++)
    //     {
    //         Movie* mp = *p;
    //         v.push_back(mp->rating());
    //     }
    // or
    //     for (auto p = x.begin(); p != x.end(); p++)
    //     {
    //         auto mp = *p;
    //         v.push_back(mp->rating());
    //     }
    // or
    //     for (Movie* mp : x)
    //         v.push_back(mp->rating());
    // or
    //     for (auto mp : x)
    //         v.push_back(mp->rating());
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes.begin(), destroyedOnes.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes[k] == expectGone[k]);
    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
        delete *p;  // Deallocate remaining movies.
}

int main()
{
    test();
    cout << "Passed" << endl;
}

