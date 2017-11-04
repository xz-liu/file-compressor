//
// Created by joker on 2017/11/5.
//

#ifndef DATA_STRUCTURE_EXP_EXP_2_H
#define DATA_STRUCTURE_EXP_EXP_2_H

#include "vector.h"
#include "stack.h"

#include <iostream>
#include <string>

using uint=unsigned int;

#define until(x) while(!(x))

void convert(const vector<uint> &input, uint input_base,
             vector<uint> &output, uint output_base) {
    output.clear();
    using ull=unsigned long long;
    ull val = 0ULL;
    for (uint n:input) {
        val = val * input_base + n;
    }
    stack<uint> mid;
    while (val){
        mid.push(val%output_base);
        val/=output_base;
    }
    until(mid.empty()){
        output.push_back(mid.top());
        mid.pop();
    }
}


bool check_expression(const std::string& exp) {
    stack<char> brackets;
    for (char c:exp) {
        if (std::string("{<([").find(c)
                 != std::string::npos) {
            brackets.push(c);
        }
        else if (c == [&]() ->char {
                 switch (brackets.top()) {
                     case '(':return ')';
                     case '[':return ']';
                     case '{':return '}';
                     case '<':return '>';
                     default:return brackets.top();
                 }}()) {
            brackets.pop();
        } else {
            return false;
        }
    }
    return brackets.empty();
}

double get_result(std::string str);

void run_exp2_tests(){
    using std::cout;
    using std::endl;

    cout<<"test converting"<<endl;
    vector<uint> dec_nums[]= {
            {4,2,9,4,9,6,7,2,9,6},
            {1,6,0,2},
            {2,1,4,7,4,8,3,6,4,7}
    },result;
    for(auto& dec:dec_nums){
        convert(dec, 10, result, 16);
        cout<<"dec:"<<endl;
        for(auto x:dec)cout<<x;
        cout<<endl;
        cout<<"hex:"<<endl;
        for(auto x:result){
            cout<<"0123456789ABCDEF"[x];
        }
        cout<<endl;
        convert(dec, 10, result, 8);
        cout<<"oct:"<<endl;
        for(auto x:result)cout<<x;
        cout<<endl;
        convert(dec, 10, result, 2);
        cout<<"bin:"<<endl;
        for(auto x:result)cout<<x;
        cout<<endl;
    }

    cout<<"test expression checking"<<endl;
    std::string test_exp[]={
            "([]){<[]()>}",//true
            "{()",//false
            "[{]}"//false
    };
    for(auto& s:test_exp){
        cout<<s<<" is "<<(check_expression(s)?"":"not ")<<"a valid expression" <<endl;
    }

    cout<<"test evaluating expressions"<<endl;
    std::string expressions[]{
            "sin(5)/4+3",
            "log(3)-(2*PI+e^(1/2))",
            "4!+8/asin(PI/4)"
    };
    for(auto& f:expressions){
        cout<<f<<" equals "<<get_result(f)<<endl;
    }
}

#endif //DATA_STRUCTURE_EXP_EXP_2_H
