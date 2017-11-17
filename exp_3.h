//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_EXP_3_H
#define DATA_STRUCTURE_EXP_EXP_3_H

#include <iostream>
#include "bin_tree.h"

template <class T>
void pre_order_init(std::istream& in,bintree_node<T>::bnode_ptr & root){
    T x;if(!in>>x) return;
    root=(new bintree_node<T>(x));
    pre_order_init(in,root->lc);
    pre_order_init(in,root->rc);
}

template <class T>
void pre_order_init(std::istream& in,bin_tree<T>& new_tree){
    pre_order_init(in,new_tree.root);
}

#endif //DATA_STRUCTURE_EXP_EXP_3_H
