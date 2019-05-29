//
//  bad.cpp
//  HW4
//
//  Created by Melody Chen on 5/25/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

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
