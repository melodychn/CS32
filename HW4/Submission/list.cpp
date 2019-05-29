//
//  list.cpp
//  HW4
//
//  Created by Melody Chen on 5/25/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

void listAll(const Domain* d, string path) // two-parameter overload
{
    //You will write this code.
    for(int k=0; k< d->subdomains().size(); k++){
        listAll(d->subdomains()[k], d->subdomains()[k]->label()+(path==""?"":("."+path)));
    }
    if(d->subdomains().size()==0)
        cout<<path<<endl;
}
