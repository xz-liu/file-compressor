//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_EXP_3_H
#define DATA_STRUCTURE_EXP_EXP_3_H

#include <iostream>
#include <functional>
#include <bitset>
#include <sstream>
#include "huffman.h"
#include "bin_tree.h"

template <class T>
void pre_order_init(std::istream& in,bintree_node<T>*& root, const T& sepreator){
    T x;if(!(in>>x)) return;
    if(x==sepreator) {
        root= nullptr;
        return;
    }
    root=(new bintree_node<T>(x));
    pre_order_init(in,root->lc,sepreator);
    pre_order_init(in,root->rc,sepreator);
}

template <class T>
void pre_order_init(std::basic_istream<T>& in,bin_tree<T>& new_tree, const T& sepreator){
    pre_order_init(in,new_tree.get_root(),sepreator);
    in.clear();
}

void run_exp3_tests(){
    using std::cout;
    using std::endl;
    using std::bitset;

    cout<<endl<<"Exp 3 :binary trees"<<endl<<endl;
    cout<<"Test huffman tree"<<endl;

        auto res = huffman<char>("aaaaabbccccdefg");
    cout<<"Original string: "<<res.str()<<endl;
    cout<<"Char counts"<<endl;
    for (auto x:res.counts()) {
        cout << x.first << ":" << x.second << endl;
    }
    cout<<"Encoding"<< endl;
    for (auto x:res.encoding()) {
        cout << x.first << ":" <<bitset<8> (x.second) << endl;
    }

    bin_tree<char> char_tree;
    std::stringstream ss("abc##de#g##f###");
    cout<<"Test traverse"<<endl;
    cout<<"Input: "<<ss.str()<<endl;
    pre_order_init<char>(ss,char_tree,'#');
    auto visit=[](char x){
        cout<<x<<" ";
    };
    cout<<"Pre order :"<<endl;
    char_tree.trav_pre_order(visit);
    cout<<endl;
    cout<<"In order  :"<<endl;
    char_tree.trav_in_order(visit);
    cout<<endl;
    cout<<"Post order :"<<endl;
    char_tree.trav_post_order(visit);
    cout<<endl;
    cout<<"Level      :"<<endl;
    char_tree.trav_level(visit);
};



#endif //DATA_STRUCTURE_EXP_EXP_3_H
