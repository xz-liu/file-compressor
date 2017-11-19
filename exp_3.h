//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_EXP_3_H
#define DATA_STRUCTURE_EXP_EXP_3_H

#include <iostream>
#include <functional>
#include <bitset>
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
void pre_order_init(std::istream& in,bin_tree<T>& new_tree, const T& sepreator){
    pre_order_init(in,new_tree.get_root(),sepreator);
    in.clear();
}
using namespace std;

void run_exp3_tests(){

    {
        auto res = huffman<char>("aaaaabbccccdefg");
        for (auto x:res.counts()) {
            cout << x.first << ":" << x.second << endl;
        }
        cout << endl;
        for (auto x:res.encoding()) {
            cout << x.first << ":" <<bitset<8> (x.second) << endl;
        }
    }
    bin_tree<char> int_tree;
    pre_order_init(cin,int_tree,'#');
    auto visit=[](char x){
        cout<<x<<" ";
    };
    cout<<"pre order :"<<endl;
    int_tree.trav_pre_order(visit);
    cout<<endl;
    cout<<"in order  :"<<endl;
    int_tree.trav_in_order(visit);
    cout<<endl;
    cout<<"post order :"<<endl;
    int_tree.trav_post_order(visit);
    cout<<endl;
    cout<<"level      :"<<endl;
    int_tree.trav_level(visit);
};



#endif //DATA_STRUCTURE_EXP_EXP_3_H
