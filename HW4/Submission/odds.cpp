//
//  odds.cpp
//  HW4
//
//  Created by Melody Chen on 5/25/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

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
