//
//  main.cpp
//  Project 4
//
//  Created by Melody Chen on 6/4/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "storage.h"
using namespace std;


//version 1
int getLength(hashTable& hash, string fold, string fnew, string current, int old_start, int new_start){
    int org_size = current.size();
    string concat_old = fold.substr(old_start+org_size);
    string concat_new = fnew.substr(new_start+org_size);
    int length=0;
    for(int k = 0; k<concat_new.size(); k++){
        if(concat_old[k]!=concat_new[k])
            break;
        else
            length++;
    }
    return length;
}

//version 2
int getLength2(hashTable& hash, string fold, string fnew, string current, int old_start, int new_start){
    int org_size = current.size();
    string concat_old = fold.substr(old_start+org_size);
    string concat_new = fnew.substr(new_start+org_size);
    //Hash the next 6, at old_start + 6
    int length=0;
    if(concat_new.size()>=6){
        string lookfor = concat_new.substr(0,6);
        int olddex = old_start+6, newdex = 0;
        while(hash.find(lookfor, olddex)){ //if you can hash it, keep hashings
            if(olddex+6>concat_old.size()||newdex+6>concat_new.size())
                break;
            olddex+=6;
            newdex+=6;
            length+=6;
            lookfor = concat_new.substr(newdex, 6);
        }
        //loop to do the rest
        for(int k = newdex; k<concat_new.size()&&k<concat_old.size(); k++){
            if(concat_old[k]!=concat_new[k])
                break;
            else
                length++;
        }
    }else{
        //if you can't hash it, compare it
        for(int k = 0; k<concat_new.size()&&k<concat_old.size(); k++){
            if(concat_old[k]!=concat_new[k])
                break;
            else
                length++;
        }
    }
    return length;
}

//reads file to string
string readFileToString(istream& file)
{
    if(!file){
        cerr << "Error with file inputted in readFileToString function!"<<endl;
        return "";
    }
    string output;
    string temp;
    while(getline(file, temp)){
        output+=temp;
        output+="\n";
    }
    if(temp!="")
        output = output.substr(0,output.size()-1);
    return output;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    //need to read in fold and fnew into string
    if(!fdiff)
        cerr<<"Cannot open fdiff file in createDiff."<<endl;
    string sold = readFileToString(fold), snew = readFileToString(fnew);
    //store sold in hashtable by N chunks
    hashTable oldtable(sold.size()/4);
    for(int k=0; k<sold.size(); k++)
        oldtable.insert(sold.substr(k,(k>sold.size()-6)?sold.size()-k:6), k);
    //comparing N chunk in snew to sold
    int add_in=-999;
    string oldsub;
    for(int j=0; j<snew.size();j++){
        int end = (j>snew.size()-6)?snew.size():j+6;
        string current = snew.substr(j,end-j);
        int offset;
        oldtable.search(current, offset);
        if(offset!=-999){ //if you found a match
            //add the new stuff
            if(add_in!=-999){
                fdiff<<"A"<<j-add_in<<":"<<snew.substr(add_in,j-add_in);
                add_in=-999;
            }
            int new_end, new_start = offset;
            int L = current.size();
            int length = getLength2(oldtable, sold, snew, current, offset, j);
            int temp_offset = offset, count=0;
            while(oldtable.nextOffset(current, temp_offset)!=-999){
                temp_offset = oldtable.nextOffset(current, temp_offset);
                int newlength=getLength2(oldtable, sold, snew, current, temp_offset, j);
                if(newlength>length){
                    length = newlength;
                    new_start = temp_offset;
                }
                count++;
            }
            L+=length;
            fdiff<<"C"<<L<<","<<new_start;
            j=j+L-1; //ERROR
            
        }else{
            //fdiff<<"A"<<1<<":"<<snew[j];
            if(add_in==-999)
                add_in = j;
        }
        oldsub = current;
    }
    if(add_in!=-999)
        fdiff<<"A"<<snew.size()-add_in<<":"<<snew.substr(add_in,snew.size()-add_in);
}

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
        case '\r':
        case '\n':
            return true;
    }
    return false;
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    if(!fold||!fdiff||!fnew){
        cerr<<"Cannot open file in applyDiff"<<endl;
        return false;
    }
    string fileold = readFileToString(fold);
    char cmd = 'A';
    int length=0, offset=0;
    while(cmd!='x'){
        if(getCommand(fdiff, cmd, length, offset)){
            if(length<0||offset<0||length>fileold.size()) //error
                return false;
            if(cmd=='A'){
                for(int k=0; k<length;k++){
                    char c;
                    fdiff.get(c);
                    fnew<<c;
                }
            }else if(cmd=='C'){
                for(int k=0; k<length;k++)
                    fnew<<fileold[offset+k];
            }else if(cmd=='\r'||cmd=='\n')
                return true;
        }else{
            return false;
        }
    }
    return true;
}

//int main() {
//    cout<<"Enter file name: ";
//    string filename;
//    cin>>filename;
//    ifstream infile("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/"+filename+"1.txt");
//    ifstream compfile("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/"+filename+"2.txt");
//    ofstream difffile_o("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/results.txt");
//    createDiff(infile, compfile, difffile_o);
//    difffile_o.close();
//    ifstream infile2("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/"+filename+"1.txt");
//    ofstream newfile("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/newfile2.txt");
//    ifstream difffile_i("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/results.txt");
//    if(!applyDiff(infile2, difffile_i, newfile))
//        cerr<<"Faulty apply diff file."<<endl;
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;

bool runtest(string oldName, string newName, string diffName, string newName2)
{
    if (diffName == oldName  ||  diffName == newName  ||
        newName2 == oldName  ||  newName2 == diffName  ||
        newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream diffFile(diffName, ios::binary);
    if (!diffFile)
    {
        cerr << "Cannot create " << diffName << endl;
        return false;
    }
    createDiff(oldFile, newFile, diffFile);
    diffFile.close();
    
    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream diffFile2(diffName, ios::binary);
    if (!diffFile2)
    {
        cerr << "Cannot read the " << diffName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(applyDiff(oldFile, diffFile2, newFile2));
    newFile2.close();
    
    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {
        
        cerr << newName2 << " is not identical to " << newName
        << "; test FAILED" << endl;
        return false;
    }
    return true;
}

int main()
{
    assert(runtest("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/strange1.txt", "/Users/melodychen/Documents/School/CS32/Project 4/Project 4/strange2.txt", "/Users/melodychen/Documents/School/CS32/Project 4/Project 4/results.txt", "/Users/melodychen/Documents/School/CS32/Project 4/Project 4/newfile2.txt"));
    cerr << "Test PASSED" << endl;
}

//bool findNextString(hashTable& oldtable, string newfile, string oldfile, int start_new, int end_new, int start_old, int end_old, int& off_start, int& off_end, int offset_o){
//    //want to hash the next substring
//    off_end=-999;
//    int count = 0;
//    string org_string = newfile.substr(start_new,end_new); //THE STRING YOU ARE LOOKING FOR
//    while(start_new!=end_new){
//        int init_end = end_old; //TO BE CONFIRMED END NEW OR OLD
//        end_new = (end_new>=newfile.size())?newfile.size():end_new+1;
//        start_new++;
//        string current = newfile.substr(start_new, end_new-start_new<=0?end_new:end_new-start_new); //STRING TO LOOK FOR
//        if(current=="Sam, I")
//            cout<<"goat"<<endl;
//        if(end_new==newfile.size()){ //iffy part
//            off_end = end_old;
//            return true;
//        }
//        int offset;
//        if(!oldtable.search(current, offset)){
//            if(off_end==-999)
//                return false;
//            off_end = init_end; //the one that hasnt been updated this turn
//            return true;
//        }else if(offset!=offset_o){
//            cout<<offset<<", "<<offset_o<<endl;
//            //find the next of org_string and check the distance from new offset
//            int temp = offset_o;
//            while(oldtable.nextOffset(org_string, temp)!=-999){ //see if you found the org_string again in another offset
//                if(oldtable.nextOffset(org_string, temp)==offset-count-1){ //check to see if u found at right place
//                    cout<<"I'm inside"<<endl;
//                    offset_o = offset;
//                    start_old = oldtable.nextOffset(org_string, temp); //change where your copy command will copy from
//                    off_start = offset-count-1; //official start should be updated as well
//                    end_old = offset+6>oldfile.size()?oldfile.size():offset+6;
//                    cout<<newfile.size()<<endl;
//                    //end_new = ((start_new+6)>newfile.size())?newfile.size():start_new+6;
//                    break;
//                }
//                temp =oldtable.nextOffset(org_string, temp); //try looking for another offset
//            }
//            end_old=end_old+1>oldfile.size()?oldfile.size():end_old+1;
//        }else{
//        //end_old = offset+6>oldfile.size()?oldfile.size():offset+6; //FAULTY
//            end_old=end_old+1>oldfile.size()?oldfile.size():end_old+1;
//        }
//        offset_o++;
//        off_end = init_end;
//        count++;
//
//    }
//    off_end = oldfile.size();
//    return true;
//}
