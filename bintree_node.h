//
// Created by joker on 2017/11/7.
//

#ifndef DATA_STRUCTURE_EXP_BINTREE_NODE_H
#define DATA_STRUCTURE_EXP_BINTREE_NODE_H

#include <functional>
#include <optional>
#include <cstdlib>
#include "queue.h"

template <class T,class S=void>
struct bintree_node {
    using bnode_ptr=bintree_node *;
    using const_bnode_ptr=const bintree_node *;
    using visit_func=std::function<void(T &)> ;
	using const_visit_func=std::function<void(const T &)> ;
    T val;
	struct Status{
		S * _val;
		Status(){
			if constexpr(!std::is_same_v<S, void>)
				_val = new S;
		}
		~Status(){
			if constexpr(!std::is_same_v<S, void>)
				delete _val;
		}
		template <class _T>
		void assign(const _T& v){*_val = v;}
		template<class _T=S>std::enable_if_t<!std::is_same_v<_T,void>,_T>&
			val() { return *_val; }
		template<class _T>	void val() { }
	}status;
	bintree_node *parent, *lc, *rc;
    int height;
    static int stature(bnode_ptr ptr) {
        return ptr ? ptr->height : -1;
    }

    bintree_node()
    : parent(nullptr), lc(nullptr), rc(nullptr), height(0){}

    explicit bintree_node(const T &val, bnode_ptr parent = nullptr,
                bnode_ptr lchild = nullptr, bnode_ptr rchild = nullptr,
                int height = 0, int null_path_length = 1)
    : val(val), parent(parent), lc(lchild), rc(rchild), height(height){}

    static void move_to_lc(bnode_ptr &ptr) { ptr = ptr->lc; }

    static void move_to_rc(bnode_ptr &ptr) { ptr = ptr->rc; }

    static void move_to_parent(bnode_ptr &ptr) { ptr = ptr->parent; }

    bool has_parent() const { if(!this)return true;return  parent; }

    bool is_root()const { return !has_parent(); }

	bool is_child() const { return !this || is_child() || is_rchild(); }

    bool is_lchild() const{ return !is_root() && (this == parent->lc); }

    bool is_rchild() const{ return !is_root() && (this == parent->rc); }

    bool has_lchild() const{ return lc; }

    bool has_rchild() const{ return rc; }

    bool has_child() const{ return has_lchild() || has_rchild(); }

    bool has_all_children() const{ return has_rchild() && has_rchild(); }

    bool is_leaf() const{ return !(this&&has_child()); }

    bnode_ptr& sibling() { return is_lchild() ? parent->rc : parent->lc; }

    bnode_ptr& uncle() {return parent->is_lchild() ? parent->parent->rc : parent->parent->lc; }
	
	bnode_ptr set_parent_ref(bnode_ptr ptr) {
		if (!this)return nullptr;
		if (is_root())return this;
		if (is_lchild())return parent->lc = ptr;
		return parent->rc = ptr;
	}  

    int size() {
        int size_now = 1;
        if (lc)size_now += lc->size();
        if (rc)size_now += rc->size();
        return size_now;
    }

    bnode_ptr next() {
        bnode_ptr s = this;
        if (rc) {
            s = rc;
            while (s->has_lchild())move_to_lc(s);
        } else {
            while (s->is_rchild())move_to_parent(s);
            move_to_parent(s);
        }
        return s;
    }

    const_bnode_ptr& next()const{ return (const_cast<bnode_ptr >(this))->next(); }

    bnode_ptr& insert_as_lchild(T const &val) { return lc = new bintree_node(val, this); }

    bnode_ptr& insert_as_rchild(T const &val) { return rc = new bintree_node(val, this); }

    bool operator<(bintree_node const &bn) const { return val < bn.val; }

    bool operator==(bintree_node const &bn) const { return val == bn.val; }

#define _BASE if (!this)return;
#define _VIS visit(val);
#define _NEXT_CHILD(child_type,trav_type) \
    child_type->trav_##trav_type##_order(visit);

#define _BINTREE_NODE_TRAV(trav_type,body)\
    void trav_##trav_type##_order(visit_func visit) {_BASE body } \
    void trav_##trav_type##_order(const_visit_func visit) const {_BASE body}

    _BINTREE_NODE_TRAV(in, _NEXT_CHILD(lc,in) _VIS _NEXT_CHILD(rc,in))
    _BINTREE_NODE_TRAV(pre, _VIS _NEXT_CHILD(lc,pre)_NEXT_CHILD(rc,pre))
    _BINTREE_NODE_TRAV(post, _NEXT_CHILD(lc,post)_NEXT_CHILD(rc,post)_VIS)

#undef _BINTREE_NODE_TRAV
#define _BINTREE_NODE_TRAV_LEVEL(prefix,attr)\
    void trav_level(prefix##visit_func visit) attr{\
        queue<prefix##bnode_ptr> Q;Q.push(this);\
        while (!Q.empty()){\
            prefix##bnode_ptr x=Q.front();\
            Q.pop();visit(x->val);\
            if(x->has_lchild()){ Q.push(x->lc); }\
            if(x->has_rchild()){ Q.push(x->rc); }\
        }\
    }

    _BINTREE_NODE_TRAV_LEVEL(,)
    _BINTREE_NODE_TRAV_LEVEL(const_, const)

#undef _BINTREE_NODE_TRAV_LEVEL
#undef _NEXT_CHILD
#undef _VIS
#undef _BASE
};

#endif //DATA_STRUCTURE_EXP_BINTREE_NODE_H
