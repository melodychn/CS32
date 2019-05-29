//
//  odds.cpp
//  HW4
//
//  Created by Melody Chen on 5/25/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector
void removeOdds(vector<int>& v)
{
    vector<int>::iterator p = v.end()-1;
    while(p!=v.begin()-1)
    {
        vector<int>::iterator temp = p;
        p--;
        if(*temp%2==1)
            v.erase(temp);
    }
}

void test()
{
    int b[1];
    vector<int> z(b,b);
    removeOdds(z);
    assert(z.size()==0);
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
