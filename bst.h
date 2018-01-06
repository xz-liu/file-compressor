//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_BST_H
#define DATA_STRUCTURE_EXP_BST_H

#include "bin_tree.h"
#include <functional>
/**
 * judge if a and b is equal
 * based on the fact that 
 * if a is not less than b
 * and b is not less than a
 * then they are equal
 */
#define _IS_EQUAL(a, b, comp) (!(comp((a),(b))) && !(comp((b),(a))))
/**
 * binary search tree
 * (does not implement rebalance of the force)
 */
template<class T, class Comp=std::less<T>,class S=void>
struct bst : bin_tree<T, S> {
protected:
	using position = typename bin_tree<T, S>::ptr;
	Comp comp;
	position hot;
#ifndef _MSC_VER
	position &root = bin_tree<T, S>::root;
	int &tree_size = bin_tree<T, S>::tree_size;
#endif
	//implements find operation
	position &search_in(position& rt, const T &val, position &hot) {
		//if the node is found or has reached to the bottom return current value 
		if (!rt || _IS_EQUAL(val, rt->val, comp))return rt;
		hot = rt;//parent of node returned, needed for insertion
		//if found return current node
		//if the value is smaller then search in left child
		//otherwise search in right child
		return search_in(comp(val, rt->val) ? rt->lc : rt->rc, val, hot);
	}
	//remove a node
	position remove_at(position &x, position &hot) {
		position del = x, nxt = nullptr;
		//if x does not have lc then connect rchild to parent
		if (!x->has_lchild())
			nxt = x = x->rc;
		//if x does not have rc then connect lchild to parent
		else if (!x->has_rchild())
			nxt = x = x->lc;
		else {//x has all childs
			//delete x's inorder successor
			del = del->next();
			std::swap(x->val, del->val);
			position u = del->parent;
			nxt = del->rc;
			if (u == x)u->rc = nxt;
			else u->lc = nxt;
		}
		hot = del->parent;
		if (nxt)nxt->parent = hot;
		//return the node that replaces x
		delete del; return nxt;
	}
	// reconnect nodes
	// connect a with T0 and T1, c with T2 and T3, b with a and c
	// returns b, which has become local root
	position reconnect_nodes(position a, position b, position c,
		position T0, position T1, position T2, position T3) {
#define CONNECT(par,ch_type,child)\
	par->ch_type=child;if(child)child->parent=par
		CONNECT(a, lc, T0);
		CONNECT(a, rc, T1); this->update_height(a);
		CONNECT(c, lc, T2);
		CONNECT(c, rc, T3); this->update_height(c);
		CONNECT(b, lc, a);
		CONNECT(b, rc, c); this->update_height(b);
		return b;
#undef CONNECT
	}
	//rotate operation for balanced binary search trees
	//rotate at different position will get different outcome
	//when used, position should be considered carefully
	position rotate_at(position v) throw (std::exception) {
		if (!v)throw std::exception();
		position p = v->parent; position g = p->parent;
		if (p -> is_lchild())//zig
			if (v->is_lchild()) {//zig zig
				p->parent = g->parent;
				return reconnect_nodes(v, p, g, v->lc, v->rc, p->rc, g->rc);
			} else { //zig zag
				v->parent = g->parent; 
				return reconnect_nodes(p, v, g, p->lc, v->lc, v->rc, g->rc);
			} 
		else //zag
			if (v->is_rchild()) { //zag zag
				p->parent = g->parent;
				return reconnect_nodes(g, p, v, g->lc, p->lc, v->lc, v->rc);
			} else { 
				v->parent = g->parent;//zag zig
				return reconnect_nodes(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
	}


public:
    bst() : bin_tree<T,S>(){}
    bst(std::initializer_list<T>&& lst) :bst(){
        for(auto x:lst){insert(x);}
    }
	bst(bst const& rhs):comp(rhs.comp),bin_tree<T,S>(rhs){}
	bst(Comp const& cmp):comp(cmp) {}
	position &find(const T &val) {
        return search_in(root, val, hot = nullptr);
    }
	//insertion
    position& insert(const T &val) {
        position &x = find(val);
        //if x is found return the node found
    	if (x)return x;
        //create a new node and update heights
    	x = new bintree_node<T,S>(val, hot);
        ++this->tree_size;
        this->update_height_above(x);
        return x;
    }
	//removal
    bool erase(const T &val) {
        position &x = find(val);
        //if not found nothing to delete
    	if (!x)return false;
        remove_at(x, hot);
        --this->tree_size;
        this->update_height_above(hot);
        return true;
    }

    void for_each(typename bin_tree<T,S>::visit_func func)
    {this->trav_in_order(func);}
    void for_each(typename bin_tree<T,S>::const_visit_func func)const
    { this->trav_in_order(func);}

};

#endif //DATA_STRUCTURE_EXP_BST_H
