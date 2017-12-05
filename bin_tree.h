//
// Created by joker on 2017/11/7.
//

#ifndef DATA_STRUCTURE_EXP_BIN_TREE_H
#define DATA_STRUCTURE_EXP_BIN_TREE_H

#include "bintree_node.h"

template <class T>
class bin_tree {
protected:
    typedef bintree_node<T> node;
    using ptr=typename bintree_node<T>::bnode_ptr;
    using const_ptr=typename bintree_node<T>::const_bnode_ptr;
    int tree_size;
    ptr root;
    virtual int update_height(ptr x){
        return x->node_height=
          1+std::max(node::stature(x->lc),node::stature(x->rc));
    }

    void update_height_above(ptr x){
        while (x){
            update_height(x);
            node::move_to_parent(x);
        }
    }

    ptr& begin_node()const{
        auto x=root;
        while (x->has_lchild())node::move_to_lc(x);
        return x;
    }
    ptr& end_node()const {
        auto x=root;
        while (x->has_rchild())node::move_to_rc(x);
        return x;
    }
    int remove_at(ptr x){
        if(!x)return 0;
        int n=1+remove_at(x->lc)+remove_at(x->rc);
        delete x;return n;
    }

    template <class CharT>
    void pre_order_init(std::basic_istream<CharT> &in,
                        typename bintree_node<T>::bnode_ptr &now,
                        typename bintree_node<T>::bnode_ptr parent,
                        int& size,const T &sepreator) {
        T x;if (!(in >> x)) return;
        if (x == sepreator)
        { now = nullptr;return; }
        size++;now = (new bintree_node<T>(x,parent));
        pre_order_init(in, now->lc,now,size, sepreator);
        pre_order_init(in, now->rc,now,size,sepreator);

    }

public:
    using visit_func=typename node::visit_func;
    using const_visit_func=typename node::const_visit_func;
    using position= bintree_node<T>*;
    using const_position= const bintree_node<T>*;

    bin_tree():tree_size(0),root(nullptr){}
    virtual ~bin_tree(){clear();}

    template <class CharT=char>
    void pre_order_init(std::basic_istream<CharT> &in,const T &sepreator){
        this->clear();
        pre_order_init(in,root, nullptr,tree_size,sepreator);
        in.clear();
    }


    static void remove_subtree(bin_tree* tree,position iter){
        if (!iter)return;
        if(iter->is_root())tree->root= nullptr;
        else iter->set_parent_ref(nullptr);
        tree->update_height_above(iter->parent);
        tree->tree_size-=tree->remove_at(iter);
    }

    virtual void clear(){remove_subtree(this,root);}

#define BINTREE_TRAV(type_name)\
void trav_##type_name(visit_func vis)\
{if(root)root->trav_##type_name(vis);}\
void trav_##type_name(const_visit_func vis)const\
{if(root)root->trav_##type_name(vis);}

    BINTREE_TRAV(level)
    BINTREE_TRAV(in_order)
    BINTREE_TRAV(pre_order)
    BINTREE_TRAV(post_order)

#undef BINTREE_TRAV

    T& front(){ return **begin_node(); }
    const T& front()const { return **end_node();}
    T& back(){
        auto x=root;
        while (x->has_rchild())node::move_to_rc(x);
        return x;
    }
    const T& back()const {
        return (const_cast<bin_tree*>(this))->back();
    }

    position& get_root(){ return root; }
    const_position get_root()const { return root;}
};

#endif //DATA_STRUCTURE_EXP_BIN_TREE_H
