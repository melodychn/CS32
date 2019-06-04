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
#include "hashtable.h"
using namespace std;

const int consec_chars = 8;

//version 1 of getLength which does not take advantage of hashTable, will compare character by character after you find a match
int getLength(hashTable& hash, string fold, string fnew, string current, int old_start, int new_start){
    size_t org_size = current.size(); //size of current string that we have found as match in fold and fnew
    string concat_old = fold.substr(old_start+org_size); //cut off everything we already examined
    string concat_new = fnew.substr(new_start+org_size); //cut off everything we already examined
    int length=0;
    for(int k = 0; k<concat_new.size(); k++){ //see how long the match continues by matching char to char
        if(concat_old[k]!=concat_new[k]) //if no longer matching, then stop length++
            break;
        else
            length++;
    }
    return length;
}

//version 2 of getLength which takes advantage of the hashTable, will try to find the next consec_char number of chars i.e. next string to look at in the hashtable at specified index to see if the next consec_char number of chars match, should be faster than version 1
int getLength2(hashTable& hash, string fold, string fnew, string current, int old_start, int new_start){
    size_t org_size = current.size(); //size of current string that we have found as match
    string concat_old = fold.substr(old_start+org_size); //cut off everything we already examined
    string concat_new = fnew.substr(new_start+org_size); //cut off everything we already examined
    //Hash the next consec_chars, at old_start + consec_chars
    int length = 0;
    if(concat_new.size()>=consec_chars){ //check if what is left after the cutoff is long enough to be hashed
        string lookfor = concat_new.substr(0,consec_chars); //the string we're trying to match of fnew
        int olddex = old_start+consec_chars, newdex = 0;
        while(hash.find(lookfor, olddex)){ //if you can find match at specified index, keep hashings for the next consec_char nums
            if(olddex+consec_chars>concat_old.size()||newdex+consec_chars>concat_new.size())
                break; //stop looking for match if your index + consec_chars exceed size of string
            olddex+=consec_chars; //increment these val by consec_char since you have found another match
            newdex+=consec_chars;
            length+=consec_chars;
            lookfor = concat_new.substr(newdex, consec_chars);
        }
        //compare char by char for the what the above loop cannot examine i.e. if you can't find a match of consec_char length in the hashtable, try looking for a shorter match
        for(int k = newdex; k<concat_new.size()&&k<concat_old.size(); k++){
            if(concat_old[k]!=concat_new[k])
                break;
            else
                length++;
        }
    }else{ //compare char by char if the string you're looking for has length < consec_char
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
    if(temp!="") //checks for whether the there is a new line at end of file
        output = output.substr(0,output.size()-1);
    return output;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    if(!fdiff || !fnew || !fold) //check for valid files
        cerr<<"Cannot open file in createDiff."<<endl;
    string sold = readFileToString(fold), snew = readFileToString(fnew);
    //store sold in hashtable by consec_char number of chunks
    hashTable oldtable(sold.size()/7);
    for(int k=0; k<sold.size(); k++) //insert strings into hashtable
        oldtable.insert(sold.substr(k,(k>sold.size()-consec_chars)?sold.size()-k:consec_chars), k);
    int add_in=-999; //index later used for Add command
    for(int j=0; j<snew.size();j++){ //loop through the new file
        size_t end = (j>snew.size()-consec_chars)?snew.size():j+consec_chars; //used for edge cases for strings at end of file
        string current = snew.substr(j,end-j); //the current string we're examing
        int offset;
        oldtable.search(current, offset); //look for current in hashtable
        if(offset!=-999){ //if you found a match
            if(add_in!=-999){ //if you found a match AND there are chars to be added with A command then add all prev strings that weren't a match
                fdiff<<"A"<<j-add_in<<":"<<snew.substr(add_in,j-add_in);
                add_in=-999; //reset to state of NO chars to be added
            }
            int new_start = offset;
            size_t L = current.size(); //the initial length of our match
            int length = getLength(oldtable, sold, snew, current, offset, j); //whether we can find longer match
            int temp_offset = offset; //used for when we want to see if our current length is the longest possible length i.e. if there are better matched
            while(oldtable.nextOffset(current, temp_offset)!=-999){ //if there is a next offset with the string we're looking at
                temp_offset = oldtable.nextOffset(current, temp_offset);
                int newlength=getLength(oldtable, sold, snew, current, temp_offset, j);
                if(newlength>length){ //if the newlength is longer, then temp_offset is a better offset
                    length = newlength;
                    new_start = temp_offset;
                }
            }
            L+=length; //add length to intial length of our match
            fdiff<<"C"<<L<<","<<new_start; //output COPY command
            j=j+L-1; //don't need to examine the next L characters
            
        }else{
            if(add_in==-999) //if no match, we need to begin our add indexing
                add_in = j;
        }
    }
    if(add_in!=-999) //if you reach end of newfile and there are chars you haven't added, add them
        fdiff<<"A"<<snew.size()-add_in<<":"<<snew.substr(add_in,snew.size()-add_in);
}

//helper function for getting command
bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

//helper function for getting command
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

//applies the difference file to old file to create a new file
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    if(!fold||!fdiff||!fnew){
        cerr<<"Cannot open file in applyDiff"<<endl;
        return false;
    }
    string fileold = readFileToString(fold);
    char cmd = 'A'; //ensures that we will go in loop at least once
    int length = 0, offset = 0;
    while(cmd!='x'){
        if(getCommand(fdiff, cmd, length, offset)){ //can obtain a valid command
            if(length<0||offset<0||length>fileold.size()||offset>=fileold.size()) //bad values
                return false;
            if(cmd=='A'){
                for(int k=0; k<length;k++){ //add length chars into new file
                    char c;
                    fdiff.get(c);
                    fnew<<c;
                }
            }else if(cmd=='C'){
                for(int k=0; k<length;k++) //copy length chars at offset from old file to new file
                    fnew<<fileold[offset+k];
            }else if(cmd=='\r'||cmd=='\n') //ignore
                ;
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

//Below is smallberg's test functions

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
    cout<<"Enter file name: ";
    string filename;
    cin>>filename;
//    assert(runtest("/Users/melodychen/Documents/School/CS32/Project 4/Project 4/strange1.txt", "/Users/melodychen/Documents/School/CS32/Project 4/Project 4/strange2.txt", "/Users/melodychen/Documents/School/CS32/Project 4/Project 4/results.txt", "/Users/melodychen/Documents/School/CS32/Project 4/Project 4/newfile2.txt"));
    assert(runtest(filename+"1.txt", filename+"2.txt", "results.txt", "newfile2.txt"));
    cerr << "Test PASSED" << endl;
}
