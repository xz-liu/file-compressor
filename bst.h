//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_BST_H
#define DATA_STRUCTURE_EXP_BST_H

#include "bin_tree.h"
#include <functional>
#define _IS_EQUAL(a,b,comp) (!comp(a,b) && !comp(b,a))
template <class T,class Comp=std::less<T>>
struct bst:bin_tree<T>{
protected:
    Comp comp;
    ptr hot;
    size_t tree_size;
    ptr& search_in(ptr rt,const T& val,ptr& hot){
        if (!rt||_IS_EQUAL(val,rt->val,comp))return rt;
        hot=rt;
        return search_in(comp(val,rt->val)?rt->lc:rt->rc,val,hot);
    }
    ptr& search(const T& val){
        return search_in(root,val,hot= nullptr);
    }
    ptr remove_at(ptr& x,ptr& hot) {
        ptr del = x, nxt = nullptr;
        if (!x->has_lchild())nxt = x->rc;
        else if (!x->has_rchild())nxt = x->lc;
        else {
            del = del->next();
            std::swap(x->val, del->val);
            ptr unc = del->parent;
            nxt = del->rc;
            if (unc == x)unc->rc = nxt;
            else unc->lc = nxt;
        }
        hot = del->parent;
        if (nxt)nxt->parent = hot;
        delete del; return nxt;
    }
public:
    bst():bin_tree<T>(),tree_size(0){}
    iterator find(const T& val){ return search(val);}
    iterator insert(const T& val){
        ptr & x=search(val);if(x)return x;
        x=new bintree_node<T>(val,hot);
        tree_size++;update_height_above(x);
        return x;
    }
    bool erase(const T& val){
        ptr &x=search(val);
        if (!x)return false;
        remove_at(x,hot);tree_size--;
        update_height_above(hot);
        return true;
    }

};

#endif //DATA_STRUCTURE_EXP_BST_H
