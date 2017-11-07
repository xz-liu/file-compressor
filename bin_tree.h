//
// Created by joker on 2017/11/7.
//

#ifndef DATA_STRUCTURE_EXP_BIN_TREE_H
#define DATA_STRUCTURE_EXP_BIN_TREE_H

#include "bintree_node.h"

template <class T,class S = void_status>
class bin_tree {
protected:
    using node=bintree_node<T, S>;
    using ptr=bintree_node<T, S>::bnode_ptr;
    using const_ptr=bintree_node<T, S>::const_bnode_ptr;
    int tree_size;
    ptr root;

    virtual int update_height(ptr x);

    void update_height_above(ptr x);

public:
    using iterator=bintree_iterator<T, S>;
    using const_iterator=const_bintree_iterator<T, S>;

    virtual iterator begin() {

    }

    virtual const_iterator cbegin() const {

    }
};

#endif //DATA_STRUCTURE_EXP_BIN_TREE_H
