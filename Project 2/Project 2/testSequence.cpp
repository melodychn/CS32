//
//  testnewSequence.cpp
//  HW1
//
//  Created by Melody Chen on 4/11/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//


#include <iostream>
#include "Sequence.h"
#include <cassert>
using namespace std;
void joshtestcase()
{
        // Test empty sequence
        Sequence emptyOne;
        assert(emptyOne.size() == 0); // test size
        assert(emptyOne.empty() == 1); // test empty
        assert(emptyOne.erase(0) == 0); // test erase == 0
        assert(emptyOne.remove(0) == 0); // test remove == 0
        
        // Test insert and erase functions
        Sequence a;
        // test insert(position, value_to_be_inserted)
        assert(a.insert(0, 4) == 0); // insert at beginning
        assert(a.insert(1, 10) == 1);
        assert(a.insert(1, 9) == 1);
        assert(a.insert(1, 8) == 1);
        assert(a.insert(1, 7) == 1);
        assert(a.insert(1, 6) == 1);
        assert(a.insert(1, 5) == 1);
        assert(a.insert(7, 100) == 7); // insert at end
        // 4 5 6 7 8 9 10 100
        assert(a.erase(2) == 1); // test erase from position 2
        // 4 5 7 8 9 10 100
        // test insert(value_to_be_inserted)
        assert(a.insert(6) == 2);
        assert(a.insert(0) == 0); // insert at front
        assert(a.insert(10) == 7);
        // 0 4 5 6 7 8 9 10 10 100
        assert(a.insert(100) == 9); // insert at back
        
        // test insert and remove functions
        Sequence c;
        // insert values
        assert(c.insert(0, 1) == 0);
        assert(c.insert(1, 3) == 1);
        assert(c.insert(2, 5) == 2);
        // 1 3 5
        assert(c.insert(6) == 3);
        assert(c.insert(6) == 3);
        assert(c.insert(7) == 5);
        // 1 3 5 6 6 7
        assert(c.remove(6) == 2); // remove more than 1 value
        assert(c.insert(7) == 3);
        assert(c.remove(7) == 2); // remove from back
        assert(c.remove(1) == 1); // remove from front
        assert(c.insert(0, 1) == 0);
        // 1 3 5
        ItemType get; // used to get values to test get function
        assert(c.get(1, get) == 1 && get == 3); // test get
        assert(c.get(0, get) == 1 && get == 1); // test get from front
        assert(c.get(2, get) == 1 && get == 5); // test get from back
        assert(c.get(-1, get) == 0); // test invalid position
        assert(c.get(3, get) == 0); // test invalid position
        
        // test remove same values in a sequence of 1 value
        Sequence allSame;
        assert(allSame.insert(5) == 0);
        assert(allSame.insert(5) == 0);
        assert(allSame.insert(5) == 0);
        assert(allSame.insert(5) == 0);
        assert(allSame.insert(5) == 0);
        assert(allSame.remove(5) == 5); // remove all 5's
        ItemType x_allSame = 2; // test get function on empty Sequence
        assert(allSame.get(0, x_allSame) == 0 && x_allSame == 2); // ensure value of ItemType variable does not change
        
        // test set nd find functions
        Sequence set;
        // insert values
        assert(set.insert(5) == 0);
        assert(set.insert(4) == 0);
        assert(set.insert(3) == 0);
        assert(set.insert(2) == 0);
        assert(set.insert(1) == 0);
        // set values for all Nodes
        assert(set.set(0, 99) == 1);
        assert(set.set(1, 98) == 1);
        assert(set.set(2, 97) == 1);
        assert(set.set(3, 96) == 1);
        assert(set.set(4, 95) == 1);
        assert(set.set(-1, 7) == 0); // test for invalid position
        assert(set.set(5, 7) == 0); // test for invalid position
        // 99 98 97 96 95
        assert(set.find(50) == -1); // test for no values in Sequence
        assert(set.find(99) == 0);
        assert(set.find(98) == 1);
        assert(set.find(97) == 2);
        assert(set.find(96) == 3);
        assert(set.find(95) == 4);
        
        // test swap
        Sequence one; // has 4 values
        assert(one.insert(30) == 0);
        assert(one.insert(20) == 0);
        assert(one.insert(10) == 0);
        assert(one.insert(5) == 0);
        Sequence two; // has 3 values
        assert(two.insert(300) == 0);
        assert(two.insert(200) == 0);
        assert(two.insert(100) == 0);
        one.swap(two); // swap
        assert(one.size() == 3); // test sizes after swap
        assert(two.size() == 4); // test sizes after swap
        // test individual sequences
        assert(one.insert(55) == 0); // make sure insert works if it has correct size
        assert(two.insert(55) == 4); // make sure insert works if it has correct size
        
        // test copy constructor
        Sequence original; // insert values
        assert(original.insert(36) == 0);
        assert(original.insert(31) == 0);
        assert(original.insert(19) == 0);
        Sequence copy(original);
        assert(copy.find(36) == 2); // check to see correct value
        assert(copy.find(31) == 1); // check to see correct value
        assert(copy.find(19) == 0); // check to see correct value
        assert(copy.size() == 3); // check size
        
        // test assignment operator
        Sequence equal1; // insert values
        assert(equal1.insert(87) == 0);
        assert(equal1.insert(86) == 0);
        assert(equal1.insert(85) == 0);
        Sequence equal2; // insert values
        assert(equal2.insert(123) == 0);
        assert(equal2.insert(122) == 0);
        assert(equal2.insert(121) == 0);
        equal2 = equal1; // use assignment operator, equal2 Sequence should be deleted
        assert(equal2.find(87) == 2); // test value
        assert(equal2.find(86) == 1); // test value
        assert(equal2.find(85) == 0); // test value
        assert(equal2.size() == 3); // test size
        
        std::cerr << "Sequence Class tests passed" << std::endl;
        
        // test subsequence function
        Sequence testingSS1; // insert values
        testingSS1.insert(0, 13);
        testingSS1.insert(1, 11);
        testingSS1.insert(2, 12);
        testingSS1.insert(3, 13);
        testingSS1.insert(4, 12);
        testingSS1.insert(5, 11);
        testingSS1.insert(6, 12);
        testingSS1.insert(7, 11);
        testingSS1.insert(8, 14);
        testingSS1.insert(9, 67);
        Sequence testingSS2; // insert values, pattern to be found in testingSS1
        testingSS2.insert(0, 11);
        testingSS2.insert(1, 12);
        testingSS2.insert(2, 11);
        assert(subsequence(testingSS1, testingSS2) == 5); // test functionality
        assert(subsequence(testingSS1, testingSS1) == 0); // make sure same string works
        assert(subsequence(testingSS2, testingSS1) == -1); // first sequence smaller than second
        
        // test interleave
        Sequence il1; // first sequence
        il1.insert(0, 1);
        il1.insert(1, 3);
        il1.insert(2, 5);
        il1.insert(3, 7);
        il1.insert(4, 8);
        Sequence il2; // second sequence
        il2.insert(0, 2);
        il2.insert(1, 4);
        il2.insert(2, 6);
        Sequence ilResult; // result
        ilResult.insert(0, 76); // put values in result
        ilResult.insert(0, 24); // should not appear in result after function
        interleave(il1, il2, ilResult);
        // check values
        assert(ilResult.find(1) == 0);
        assert(ilResult.find(2) == 1);
        assert(ilResult.find(3) == 2);
        assert(ilResult.find(4) == 3);
        assert(ilResult.find(5) == 4);
        assert(ilResult.find(6) == 5);
        assert(ilResult.find(7) == 6);
        assert(ilResult.find(8) == 7);
        assert(ilResult.size() == 8);
        // test interleave with seq1 as result
        interleave(il1, il2, il1);
        assert(il1.find(1) == 0);
        assert(il1.find(2) == 1);
        assert(il1.find(3) == 2);
        assert(il1.find(4) == 3);
        assert(il1.find(5) == 4);
        assert(il1.find(6) == 5);
        assert(il1.find(7) == 6);
        assert(il1.find(8) == 7);
        assert(il1.size() == 8);
        
        // test interleave with seq2 empty
        Sequence aaa;
        aaa.insert(10);
        aaa.insert(8);
        aaa.insert(6);
        aaa.insert(4);
        Sequence bbb; // empty sequence
        Sequence res1;
        interleave(aaa, bbb, res1);
        assert(res1.find(4) == 0);
        assert(res1.find(6) == 1);
        assert(res1.find(8) == 2);
        assert(res1.find(10) == 3);
        // test interleave with seq1 empty
        interleave(bbb, aaa, res1);
        assert(res1.find(4) == 0);
        assert(res1.find(6) == 1);
        assert(res1.find(8) == 2);
        assert(res1.find(10) == 3);
        // test interleave with all empty
        Sequence emptyinterleave;
        interleave(emptyinterleave, emptyinterleave, emptyinterleave);
        assert(emptyinterleave.size() == 0);
        assert(emptyinterleave.empty() == 1);
        
        std::cerr << "Functions tests passed" << std::endl;
    
    
    //#include <string>
    //#include <cassert>
    //#include "Sequence.h"
    //#include <iostream>
    //int main()
    //{
    //    Sequence ss;  // ItemType is std::string
    //    ss.insert(0, "aaa");
    //    ss.insert(1, "bbb");
    //    ss.insert(2, "ccc");
    //    ItemType x = "xxx";
    //    assert(!ss.get(3, x) && x == "xxx");  // x is unchanged
    //    assert(ss.get(1, x) && x == "bbb");
    //    std::cerr << "All tests passed" << std::endl;
    //
    //}
    
    //#include "Sequence.h"
    //#include <type_traits>
    //
    //int subsequence(const Sequence& seq1, const Sequence& seq2);
    //void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
    //
    //#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }
    //
    //static_assert(std::is_default_constructible<Sequence>::value,
    //    "Sequence must be default-constructible.");
    //static_assert(std::is_copy_constructible<Sequence>::value,
    //    "Sequence must be copy-constructible.");
    //static_assert(std::is_copy_assignable<Sequence>::value,
    //    "Sequence must be assignable.");
    //
    //void thisFunctionWillNeverBeCalled()
    //{
    //    CHECKTYPE(&Sequence::empty, bool (Sequence::*)() const);
    //    CHECKTYPE(&Sequence::size, int  (Sequence::*)() const);
    //    CHECKTYPE(&Sequence::insert, int (Sequence::*)(int, const ItemType&));
    //    CHECKTYPE(&Sequence::insert, int (Sequence::*)(const ItemType&));
    //    CHECKTYPE(&Sequence::erase, bool (Sequence::*)(int));
    //    CHECKTYPE(&Sequence::remove, int  (Sequence::*)(const ItemType&));
    //    CHECKTYPE(&Sequence::get, bool (Sequence::*)(int, ItemType&) const);
    //    CHECKTYPE(&Sequence::set, bool (Sequence::*)(int, const ItemType&));
    //    CHECKTYPE(&Sequence::find, int  (Sequence::*)(const ItemType&) const);
    //    CHECKTYPE(&Sequence::swap, void (Sequence::*)(Sequence&));
    //    CHECKTYPE(subsequence, int(*)(const Sequence&, const Sequence&));
    //    CHECKTYPE(interleave, void(*)(const Sequence&, const Sequence&, Sequence&));
    //}
    //
    //int main()
    //{}
}
int main() {
    joshtestcase();
    Sequence a;
    assert(a.insert(0,1)==0);
    assert(a.insert(0,0)==0);
    assert(a.insert(2,3)==2);
    assert(a.insert(2,2)==2);
    assert(a.insert(4,4)==4);
    assert(a.size()==5);
    unsigned long test;
    assert(a.get(0, test)==true);
    assert(test==0);
    assert(a.get(5, test)==false);
    assert(a.get(4, test)==true);
    assert(test==4);
    assert(a.get(-1, test)==false);
    assert(a.insert(6, 9)==-1);
    assert(a.insert(0)==0);
    assert(a.insert(5)==6);
    assert(a.insert(100)==7);
    assert(a.insert(1)==2);
    assert(a.erase(0)==true);
    assert(a.erase(0)==true);
    assert(a.erase(6)==true);
    assert(a.erase(6)==false);
    assert(a.remove(1)==2);
    assert(a.find(2)==0);
    assert(a.find(6)==-1);
    assert(a.find(5)==3);
    
    Sequence b;
    //testing for empty list
    assert(b.remove(0)==0);
    assert(b.find(0)==-1);
    assert(b.erase(0)==false);
    assert(b.set(5, 10)==false);
    assert(b.get(0,test)==false);
    assert(b.insert(0)==0);
    assert(b.erase(0)==true);
    //testing for all same values
    for(int k=0; k<4; k++)
        b.insert(1);
    assert(b.find(1)==0);
    assert(b.size()==4);
    assert(b.remove(1)==4);
    assert(b.size()==0);
    //regular testing
    assert(b.insert(0)==0);
    assert(b.insert(1)==1);
    assert(b.insert(2)==2);
    assert(b.set(0, 1)==true);
    assert(b.get(0, test)==true);
    assert(test==1);
    assert(b.set(2,3)==true);
    assert(b.get(2, test)==true);
    assert(test==3);
    assert(b.set(3,3)==false);
    //testing swap
    Sequence d;
    Sequence e;
    ItemType v = 0;

    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(d.insert(v) != -1);

    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    assert(d.size()==5);
    assert(e.size()==0);
    assert(d.find(v)==0);
    assert(e.find(v)==-1);
    e.swap(d);
    assert(e.size()==5); //check if their sizes are swapped
    assert(d.size()==0); //check if sizes are swapped
    assert(d.find(v)==-1);
    assert(e.find(v)==0);
    assert(d.insert(v) != -1); //check if you're able to insert stuff into b now
    assert(d.find(v)==0); //check if the first instance of v is at 0
    
    //testing copy constructor
    Sequence f(a);
    assert(f.size()==a.size());
    assert(f.get(0, test)==true);
    assert(test==2);
    assert(f.get(1,test)==true);
    assert(test==3);
    assert(f.get(2,test)==true);
    assert(test==4);
    assert(f.get(3,test)==true);
    assert(test==5);
    assert(f.insert(0)==0);
    assert(f.find(5)==4);
    //testing assignment operator
    f = b;
    assert(f.size()==3);
    f.get(0, test);
    assert(test==1);
    f.get(1, test);
    assert(test==1);
    f.get(2, test);
    assert(test==3);
    assert(f.remove(1)==2);
    assert(f.size()==1);
    
    //test subsequence
    Sequence g;
    Sequence i;
    Sequence z;
    assert(subsequence(g, i)==-1);
    g.insert(2);
    g.insert(5);
    g.insert(7);
    g.insert(9);
    g.insert(12);
    g.insert(17);
    i.insert(7);
    i.insert(9);
    i.insert(12);
    z.insert(4);
    z.insert(8);
    z.insert(9);
    z.insert(9);
    assert(subsequence(g, g)==0); //test for aliasing
    assert(subsequence(g, i)==2);
    assert(subsequence(i, g)==-1);
    assert(subsequence(g, z)==-1);
    //test interleave
    Sequence k(a);
    i.insert(15);
    i.insert(22);
    i.insert(25);
    interleave(i, z, k);
    k.get(0, test);
    assert(test==7);
    k.get(1, test);
    assert(test==4);
    interleave(i, z, i);
    i.get(0, test);
    assert(test==7);
    i.get(1, test);
    assert(test==4);
    i.get(2, test);
    assert(test==9);
    i.get(3, test);
    assert(test==8);
    i.get(8, test);
    assert(test==22);
    i.get(9, test);
    assert(test==25);
    cerr<<"passed all test cases"<<endl;
    return 0;

}

