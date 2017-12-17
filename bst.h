//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_BST_H
#define DATA_STRUCTURE_EXP_BST_H

#include "bin_tree.h"
#include <functional>


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
			nxt = x = x->rc;
		else if (!x->has_rchild())
			nxt = x = x->lc;
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

	position connect34(position a, position b, position c,
		position T0, position T1, position T2, position T3) {
#define CONNECT(par,ch_type,child)\
	par->ch_type=child;if(child)child->parent=par
		CONNECT(a, lc, T0);
		CONNECT(a, rc, T1); update_height(a);
		CONNECT(c, lc, T2);
		CONNECT(c, rc, T3); update_height(c);
		CONNECT(b, lc, a);
		CONNECT(b, rc, c); update_height(b);
		return b;
#undef CONNECT
	}

	position rotate_at(position v) throw (std::exception) {
		if (!v)throw std::exception();
		position p = v->parent; position g = p->parent;
		if (p -> is_lchild())
			if (v->is_lchild()) { 
				p->parent = g->parent;
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			} else { 
				v->parent = g->parent; 
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			} 
		else 
			if (v->is_rchild()) { 
				p->parent = g->parent;
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			} else { 
				v->parent = g->parent;
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
	}


public:
    bst() : bin_tree<T,S>(){}
    bst(std::initializer_list<T>&& lst) :bst(){
        for(auto x:lst){insert(x);}
    }
	virtual position &find(const T &val) {
        return search_in(root, val, hot = nullptr);
    }

    virtual position& insert(const T &val) {
        position &x = find(val);
        if (x)return x;
        x = new bintree_node<T,S>(val, hot);
        ++tree_size;
        this->update_height_above(x);
        return x;
    }

    virtual bool erase(const T &val) {
        position &x = find(val);
        if (!x)return false;
        remove_at(x, hot);
        --tree_size;
        this->update_height_above(hot);
        return true;
    }

    void for_each(typename bin_tree<T,S>::visit_func func)
    {this->trav_in_order(func);}
    void for_each(typename bin_tree<T,S>::const_visit_func func)const
    { this->trav_in_order(func);}

};

#endif //DATA_STRUCTURE_EXP_BST_H
