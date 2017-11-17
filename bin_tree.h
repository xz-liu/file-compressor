//
// Created by joker on 2017/11/7.
//

#ifndef DATA_STRUCTURE_EXP_BIN_TREE_H
#define DATA_STRUCTURE_EXP_BIN_TREE_H

#include "bintree_node.h"

#define trav(type_name)\
    void trav_##type_name(visit_func vis){if(root)root->trav_##type_name(vis);}\
    void trav_##type_name(const_visit_func vis)const {if(root)root->trav_##type_name(vis);}

template <class T>
void pre_order_init(std::istream& in,bin_tree<T>& new_tree);

template <class T>
class bin_tree {
protected:
    typedef bintree_node<T> node;
    using ptr=typename bintree_node<T>::bnode_ptr;
    using const_ptr=typename bintree_node<T>::const_bnode_ptr;
    int tree_size;

    /**
 * template <typename T> int BinTree<T>::updateHeight ( BinNodePosi(T) x ) //更新节点x高度
{ return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) ); } //具体规则，因树而异

template <typename T> void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ) //更新高度
{ while ( x ) { updateHeight ( x ); x = x->parent; } } //从x出发，覆盖历代祖先。可优化

 * @param x
 * @return
 */

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

    ptr begin_node()const{
        auto x=root;
        while (x->has_lchild())node::move_to_lc(x);
        return x;
    }
    ptr end_node()const {
        auto x=root;
        while (x->has_rchild())node::move_to_rc(x);
        return x;
    }
    int remove_at(ptr x){
        if(!x)return 0;
        int n=1+remove_at(x->lc)+remove_at(x->rc);
        delete x;return n;
    }
    template <class X>
    friend void pre_order_init(std::istream&,bin_tree<X>& );
public:
    using visit_func=typename node::visit_func;
    using const_visit_func=typename node::const_visit_func;
    using iterator= bintree_iterator<T>;
    using const_iterator= const_bintree_iterator<T>;

    bin_tree():tree_size(0),root(nullptr){}
    virtual ~bin_tree(){clear();}

    virtual void remove_subtree(iterator iter){
        ptr under=iter.node;
        if(under->is_root())root= nullptr;
        else {
            under->set_parent_ref(nullptr);
            update_height_above(under->parent);
            tree_size-=remove_at(under);
        }
    }

    virtual void clear(){remove_subtree(root);}

    trav(level)
    trav(in_order)
    trav(pre_order)
    trav(post_order)

    T& front(){ return *begin(); }
    const T& front()const { return *cbegin();}
    T& back(){
        auto x=root;
        while (x->has_rchild())node::move_to_rc(x);
        return x;
    }
    const T& back()const {
        return (const_cast<bin_tree*>(this))->back();
    }

    iterator get_root(){ return root; }
    const_iterator get_root()const { return root;}
    virtual iterator begin() {
        return iterator(begin_node());
    }

    virtual const_iterator cbegin() const {
        return const_iterator(begin_node());
    }

    virtual const_iterator begin()const { return cbegin();}

    virtual iterator end(){
        return iterator();
    }

    virtual const_iterator cend()const {
        return const_iterator();
    }
    virtual const_iterator end()const{ return cend();}

    ptr root;
};

#endif //DATA_STRUCTURE_EXP_BIN_TREE_H
