//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_BST_H
#define DATA_STRUCTURE_EXP_BST_H

#include "bin_tree.h"
#include <functional>


template<class T, class Comp=std::less<T>>
struct bst : bin_tree<T> {
protected:
    using position =typename bin_tree<T>::ptr;
    Comp comp;
    position hot,&root=bin_tree<T>::root;
    int &tree_size=bin_tree<T>::tree_size;

    position &search_in(position& rt, const T &val, position &hot) {
#define _IS_EQUAL(a, b, comp) (!comp(a,b) && !comp(b,a))
        if (!rt || _IS_EQUAL(val, rt->val, comp))return rt;
#undef _IS_EQUAL
        hot = rt;
        return search_in(comp(val, rt->val) ? rt->lc : rt->rc, val, hot);
    }

    position remove_at(position &x, position &hot) {
        position del = x, nxt = nullptr;
        if (!x->has_lchild())
            nxt = x= x->rc;
        else if (!x->has_rchild())
            nxt = x=x->lc;
        else {
            del = del->next();
            std::swap(x->val, del->val);
            position u = del->parent;
            nxt = del->rc;
            if (u == x)u->rc = nxt;
            else u->lc = nxt;
        }
        hot = del->parent;
        if (nxt)nxt->parent = hot;
        delete del; return nxt;
    }

public:
    bst() : bin_tree<T>(){}
    bst(std::initializer_list<T>&& lst)
            :bst(){
        for(auto x:lst){insert(x);}
    }
    position &find(const T &val) {
        return search_in(root, val, hot = nullptr);
    }

    position insert(const T &val) {
//        position update;
        position &x = find(val);
        if (x)return x;
        x = new bintree_node<T>(val, hot);
        tree_size++;
        this->update_height_above(x);
        return x;
    }

    bool erase(const T &val) {
        position &x = find(val);
        if (!x)return false;
        remove_at(x, hot);
        tree_size--;
        this->update_height_above(hot);
        return true;
    }

};

#endif //DATA_STRUCTURE_EXP_BST_H
