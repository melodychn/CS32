//
//  linear.cpp
//  HW3
//
//  Created by Melody Chen on 5/9/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
int counter = 0; //keep track of how many times a certain comparator is called

bool somePredicate(string s)
{
    int nDigits = 0;
    for (int k = 0; k != s.size(); k++)
    {
        if (isdigit(s[k]))
            nDigits++;
    }
    return nDigits == 3;
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if(n>0){
        if(!somePredicate(a[0]))
            return false;
        return allTrue(a+1, n-1);
    }
    return true;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if(n<=0)
        return 0;
    if(!somePredicate(a[0]))
        return countFalse(a+1, n-1)+1;
    return countFalse(a+1,n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if(n<=0)
       return -1;
    if(!somePredicate(a[n-1])&&firstFalse(a, n-1)==-1)
        return n-1;
    return firstFalse(a, n-1);
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    if(n<=0)
        return -1;
    if(n==1)
        return 0;
    if(a[n-1]<a[0]){
        counter++;
        if(n==2)
            return n-1;
        else
            return indexOfLeast(a+1, n-1)+1;
    }
    return indexOfLeast(a, n-1);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if(n2<=0)
        return true;
    if(n1<=0)
        return false;
    if(a2[0]==a1[0]){
        counter++;
        return includes(a1+1, n1-1, a2+1, n2-1);
    }
    return includes(a1+1, n1-1, a2, n2);
}

int main()
{
    string a[10];
    a[0] = "1234567890";
    a[1] = "1234567890";
    a[2] = "abcdj";
    a[3] = "abcdefghij";
    a[4] = "abcdefghij";
    a[5] = "1234567890";
    a[6] = "1234567890";
    a[7] = "abcdefghij";
    assert(allTrue(a, 0)==1); //if no element should return true
    assert(allTrue(a, 1)==1);
    assert(allTrue(a, 2)==1);
    assert(allTrue(a, 3)==0);
    assert(allTrue(a, 4)==0);
    assert(countFalse(a, 8)==4);
    assert(countFalse(a, 7)==3);

    string b[10];
    b[0] = "1234567890";
    b[1] = "1234567890";
    b[2] = "12345678";
    b[3] = "";
    b[4] = "";
    assert(firstFalse(b, 0)==-1);
    assert(firstFalse(b, 1)==-1);
    assert(firstFalse(b, 2)==-1);
    assert(firstFalse(b, 3)==2);
    assert(firstFalse(b, 4)==2);
    assert(firstFalse(b, 5)==2);
    assert(firstFalse(a, 3)==2);
    assert(firstFalse(a, 8)==2);
    string c[]={"1234567890",""};
    assert(firstFalse(c, 1)==-1);
    assert(firstFalse(c, 2)==1);
    string d[]={"",""};
    assert(firstFalse(d, 1)==0);
    assert(firstFalse(d, 2)==0);
    std::string arr1[] = { "CS31", "CS32", "CS33", "", "CS33" };
    std::string arr2[] = { "", "", "", "" };
    std::string arr3[] = { "CS31", "", "", "" };
    std::string arr4[] = { "", "", "", "CS31" };
    std::string arr5[] = { "CS30", "CS31", "CS34", "CS32" };
    std::string arr5A[] = { "", "CS31", "" };
    std::string arr5B[] = { "CS33", "CS333", "CS32", "CS33", "CS31", "CS31" };
    assert(indexOfLeast(arr1, 5) == 3);
    cout<<5<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr2, 4) == 0);
    cout<<4<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr3, 4) == 1);
    cout<<4<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr4, 4) == 0);
    cout<<4<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr5A, 3) == 0);
    cout<<3<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr5A, 1) == 0);
    cout<<1<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr5B, 6) == 4);
    cout<<6<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr1, 0) == -1);
    cout<<0<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr1, -1) == -1);
    cout<<-1<<": "<<counter<<endl;
    counter = 0;
    assert(indexOfLeast(arr5B, 6) == 4);
    cout<<6<<": "<<counter<<endl;
    counter = 0;
    std::string arr6[] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
    std::string arr7[] = { "kyle", "kenny", "butters" };
    std::string arr8[] = { "kyle", "cartman", "cartman" };
    std::string arr9[] = { "kyle", "butters", "kenny" };
    std::string arr10[] = { "stan", "kenny", "kenny" };
    assert(includes(arr6, 7, arr7, 3));
    cout<<7<<": "<<counter<<endl;
    counter = 0;
    assert(includes(arr6, 7, arr8, 3));
    cout<<7<<": "<<counter<<endl;
    counter = 0;
    assert(!includes(arr6, 7, arr9, 3));
    cout<<7<<": "<<counter<<endl;
    counter = 0;
    assert(!includes(arr6, 7, arr10, 3));
    cout<<7<<": "<<counter<<endl;
    counter = 0;
    assert(!includes(arr6, 0, arr10, 3)); //n1 = 0
    cout<<0<<": "<<counter<<endl;
    counter = 0;
    assert(includes(arr6, 7, arr10, 0)); //n2 = 0
    cout<<7<<": "<<counter<<endl;
    counter = 0;
    assert(includes(arr6, 0, arr10, 0)); //n1 = n2 = 0, n2 = 0 takes precedence
    cout<<0<<": "<<counter<<endl;
    counter = 0;
    cout<<"Passed all test cases."<<endl;
}
