//
//  eval.cpp
//  HW2
//
//  Created by Melody Chen on 4/26/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;
bool convert(string infix, string& postfix);
bool evaluale_postfix(string postfix, char & result);
int evaluate(string infix, string& postfix, bool& result)
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
{
    if(!convert(infix, postfix))
        return 1;
    char res = ' ';
    if(!evaluale_postfix(postfix, res))
        return 1;
    if(res=='T') result = true;
    if(res=='F') result = false;
    return 0;
}
bool convert(string infix, string& postfix)
{
    //initialize postfix to empty
    postfix = "";
    //initialize operator stack to empty
    stack<char> postfix_s;
    stack<char> opt_stack;
    //if infix is empty
    if(infix.size()==0)
        return false;
    int count=0; //() only odd number will work
    //loop through all the infix string
    for(int k = 0; k<infix.size(); k++)
    {
        switch(infix[k])
        {
            case 'T':
            case 'F':
                if(k>0&&(infix[k-1]=='T'||infix[k-1]=='T'))
                    return false;
                postfix_s.push(infix[k]);
                count++;
                break;
                //case (
            case '(':
                count = 0;
                opt_stack.push(infix[k]);
                break;
            case ')':
                //pop stack until matching (
                if(opt_stack.top()=='('&&postfix_s.empty())
                    return false;
                while(opt_stack.top()!='(')
                {
                    postfix_s.push(opt_stack.top());
                    opt_stack.pop();
                }
                if(count%2==0)
                    return false;
                opt_stack.pop();
                break;
            case '!':
                if(k==infix.size()-1||infix[k+1]=='&'||infix[k+1]=='^'||infix[k+1]==')')
                    return false;
                opt_stack.push(infix[k]);
                break;
            case '&':
            case '^':
                count++;
                bool one;
                bool two;
                while(!opt_stack.empty()&&opt_stack.top()!='('){
                    one = infix[k]=='&'&&(opt_stack.top()=='&'||opt_stack.top()=='!');
                    two = infix[k]=='^'&&(opt_stack.top()=='&'||opt_stack.top()=='!'||opt_stack.top()=='^');
                    if(!(one||two)){
                        break;
                    }
                    postfix_s.push(opt_stack.top());
                    opt_stack.pop();
                }
                opt_stack.push(infix[k]);
                break;
            case ' ':
                break;
            default:
                return false;
        }
    }
    //append operator to postfix stack
    while (!opt_stack.empty()) {
        postfix_s.push(opt_stack.top());
        opt_stack.pop();
    }
    stack<char> temp;
    //flip the postfix stack
    while(!postfix_s.empty()){
        temp.push(postfix_s.top());
        postfix_s.pop();
    }
    //append to postfix string
    while (!temp.empty()) {
        postfix+=temp.top();
        temp.pop();
    }
    return true;
}
bool evaluale_postfix(string postfix, char & result)
{
    stack<char> opd;
    //loop through postfix
    for(int k=0; k<postfix.size();k++){
        //operand case
        if(postfix[k]=='T'||postfix[k]=='F'){
            opd.push(postfix[k]);
        }else if(postfix[k]=='!'){
            char temp = opd.top();
            opd.pop();
            //apply !
            if(temp=='T')
                opd.push('F');
            else if(temp=='F')
                opd.push('T');
        }else if((postfix[k]=='&'||postfix[k]=='^')&&(opd.size()>=2)){
            char opd2 = opd.top();
            opd.pop();
            char opd1 = opd.top();
            opd.pop();
            if(postfix[k]=='&'){
                if(opd2==opd1)
                    opd.push(opd1);
                else
                    opd.push('F');
            }else if(postfix[k]=='^'){
                if(opd2!=opd1)
                    opd.push('T');
                else
                    opd.push('F');
            }
        }else{
            return false;
        }
    }
    //if opd size!= 1
    if(opd.size()!=1)
        return false;
    result = opd.top();
    return true;
}

int main()
{
    string test = "T&&";
    string result;
    bool res;
    assert(evaluate(test, result, res)==1); //not a valid string
    test = "(T&(  F^F)";
    assert(evaluate(test, result, res)==1);
    test = "(T&   F)";
    assert(evaluate(test, result, res)==0&&result=="TF&"&&res==false);
    //cout<<test<<": "<<result<<endl;
    test = "!(T&F)";
    assert(evaluate(test, result, res)==0&&result=="TF&!"&&res==true);
    test = "(T&!F)";
    assert(evaluate(test, result, res)==0&&result=="TF!&"&&res==true);
    test = "(!T&!F)";
    assert(evaluate(test, result, res)==0&&result=="T!F!&"&&res==false);
    test = "!(!T&!F)";
    assert(evaluate(test, result, res)==0&&result=="T!F!&!"&&res==true);
    test = "(F^T&T^F)";
    assert(evaluate(test, result, res)==0&&result=="FTT&^F^"&&res==true);
    test = "T&!(F^T&  T  ^ F)^ !!!(F&T&F)";
    assert(evaluate(test, result, res)==0&&result=="TFTT&^F^!&FT&F&!!!^"&&res==true);
    test = "T^";
    assert(evaluate(test, result, res)==1);
    test = "TT";
    assert(evaluate(test, result, res)==1);
    test = "";
    assert(evaluate(test, result, res)==1);
    test = "((T))";
    assert(evaluate(test, result, res)==0&&result=="T"&&res==true);
    test = "(TT&)";
    assert(evaluate(test, result, res)==1);
    test = "(TF&^)";
    assert(evaluate(test, result, res)==1);
    test = "(T^&F)";
    assert(evaluate(test, result, res)==1);
    test = "((T^F))&";
    assert(evaluate(test, result, res)==1);
    test = "&T^F";
    assert(evaluate(test, result, res)==1);
    test = "(T&F&^)";
    assert(evaluate(test, result, res)==1);
    test = "(T&F&)";
    assert(evaluate(test, result, res)==1);
    test = "(!T)";
    assert(evaluate(test, result, res)==0 && res == false);
    test = "T&T!";
    assert(evaluate(test, result, res)==1);
    test = "T!&T";
    assert(evaluate(test, result, res)==1);
    test = "(T&T)!";
    assert(evaluate(test, result, res)==1);
    test = "(!(!T&F)!)";
    assert(evaluate(test, result, res)==1);
    test = "!(!(!(T&F)))";
    assert(evaluate(test, result, res)==0&&res==true);
    test = "!T";
    assert(evaluate(test, result, res)==0&&res==false);
    string pf;
    bool answer;
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cerr<<"Passed all test case"<<endl;
}
