//
//  eval.cpp
//  HW2
//
//  Created by Melody Chen on 4/26/19.
//  Copyright © 2019 Melody Chen. All rights reserved.
//

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
    if(!convert(infix, postfix)) //convert to postfix, if convert returns false, not valid string
        return 1;
    char res = ' ';
    if(!evaluale_postfix(postfix, res)) //evaluate, if eval returns false, not valid string
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
    stack<char> opt_stack;
    stack<char> postfix_s; //stack in postfix notation
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
                //check for what comes before an operand cannot be an operand
                if(k > 0&&(infix[k-1]=='T'||infix[k-1]=='T'))
                    return false;
                postfix_s.push(infix[k]);
                count++;
                break;
            case '(':
                count = 0; //count reset every time (
                opt_stack.push(infix[k]);
                break;
            case ')':
                if(opt_stack.top()=='('&&postfix_s.empty()) //not a valid string if () with nothing valid inside
                    return false;
                while(opt_stack.top()!='(') //pop stack until matching (
                {
                    postfix_s.push(opt_stack.top());
                    opt_stack.pop();
                }
                if(count%2==0) //check for only odd # inside ()
                    return false;
                opt_stack.pop();
                break;
            case '!':
                if(k==infix.size()-1||infix[k+1]=='&'||infix[k+1]=='^'||infix[k+1]==')')
                    //! cannot be at end and cannot come before & ^ )
                    return false;
                opt_stack.push(infix[k]);
                break;
            case '&':
            case '^':
                count++;
                bool one; //check for precedence
                bool two; //check for precedence
                while(!opt_stack.empty()&&opt_stack.top()!='('){
                    one = infix[k]=='&'&&(opt_stack.top()=='&'||opt_stack.top()=='!');
                    two = infix[k]=='^'&&(opt_stack.top()=='&'||opt_stack.top()=='!'||opt_stack.top()=='^');
                    if(!(one||two)){ //if current & ^ does not fulfill one and two
                        break;
                    }
                    postfix_s.push(opt_stack.top());
                    opt_stack.pop();
                }
                opt_stack.push(infix[k]); //push current operator onto stack
                break;
            case ' ': //spaces are okay
                break;
            default: //fails if anything else is put in
                return false;
        }
    }
    //append operator stack to postfix stack
    while (!opt_stack.empty()) {
        postfix_s.push(opt_stack.top());
        opt_stack.pop();
    }
    stack<char> temp; //temp stack to hold values
    //flip the postfix stack with temp stack
    while(!postfix_s.empty()){
        temp.push(postfix_s.top());
        postfix_s.pop();
    }
    //append to postfix string in right order
    while (!temp.empty()) {
        postfix+=temp.top();
        temp.pop();
    }
    return true;
}

bool evaluale_postfix(string postfix, char & result)
{
    stack<char> opd; //initiate operand stack
    //loop through postfix
    for(int k=0; k<postfix.size();k++){
        if(postfix[k]=='T'||postfix[k]=='F'){ //operand case
            opd.push(postfix[k]);
        }else if(postfix[k]=='!'){
            char temp = opd.top();
            opd.pop();
            //apply ! logic
            if(temp=='T')
                opd.push('F');
            else if(temp=='F')
                opd.push('T');
        }else if((postfix[k]=='&'||postfix[k]=='^')&&(opd.size()>=2)){
            //can only apply & ^ when there's two operand to operate on
            char opd2 = opd.top();
            opd.pop();
            char opd1 = opd.top();
            opd.pop();
            //apply logic for & ^
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
        }else{ //all other cases
            return false;
        }
    }
    if(opd.size()!=1) //if whats left is more than one item
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
    test = "T(F)";
    assert(evaluate(test, result, res)==1);
    test = "T(F&T)";
    assert(evaluate(test, result, res)==1);
    test = "&";
    assert(evaluate(test, result, res)==1);
    test = "!() ";
    assert(evaluate(test, result, res)==1);
    test = "T&F!";
    assert(evaluate(test, result, res)==1);
    test = "(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!T)&(!!!!(!!T))";
    assert(evaluate(test, result, res)==0 && res == false);
    test = "((((!!!!(!!(!!T)&!(!!!((!!(!!(F))))))))))";
    assert(evaluate(test, result, res) == 0 && res == false);
    string pf;
    
    //smallbergs test cases
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
    
    cerr<<"Passed all test cases!"<<endl;
}
