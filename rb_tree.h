#pragma once

#ifndef DATA_STRUCTURE_EXP_RB_TREE_H
#define DATA_STRUCTURE_EXP_RB_TREE_H
#include <functional>
#include "bst.h"
/**
 * red black tree color type
 */
enum class rb_color {
	red, black
};

/**
 * red black tree class template
 * extends class bst<T, Comp, rb_color>
 * implements insertion, removal of red black tree
 * and rebalance after modified
 * height in this tree is defined as black height
 */
template<class T, class Comp = std::less<>, class _Base= bst<T, Comp, rb_color>>
class rb_tree :public _Base {
public:
	using position = typename bst<T, Comp, rb_color>::position;
protected:
	static bool is_black(position p) {//nullptr is colored black
		return (!(p) || (rb_color::black == color(p)));
	}
	static bool is_red(position p) { return !is_black(p); }
	//get current color
	static rb_color& color(position p) { return p->status.val(); }
	//set current color
	static rb_color set_color(position p, rb_color c) {
		p->status.assign(c);return c;
	}
	static int stature(position x) { return bintree_node<T, rb_color>::stature(x); }
	//check if black height is correct
	static bool black_height_updated(position x) {
		return (stature(x->lc) == stature(x->rc))//height of childs should be the same
			&& (x->height == (is_red(x) ?
				//if this is black the height need to be 1 + height of child
				//otherwise the height need to be the same with height of child
				stature(x->lc) : stature(x->lc) + 1));
	}
	//create a new red black tree node
	template<class ...Args>
	static position new_rbnode(Args&&...args) {
		position x = 
			new bintree_node<T, rb_color>(std::forward<Args>(args)...);
		//set new node color to red
		set_color(x, rb_color::red);
		return x;
	}
// parent' s reference of this node
#define GET_PARENT_REF(x)	((x) == this->root ? this->root : ((x)->is_lchild() ? (x)->parent->lc : (x)->parent->rc))
	//rebalance after removal
	void after_removal(position r) {
		//tree becomes empty
		if (!(--this->tree_size))return;
		//if root deleted set new root to black
		// and update height
		if (!this->hot) {
			set_color(this->root, rb_color::black);
			update_height(this->root);
		} //if is still balanced then no need to rebalance
		else if (black_height_updated(this->hot));
		//if r is red then set it's color to black
		else if (is_red(r)) {
			set_color(r, rb_color::black);
			++r->height;
		}//r is black, rebalance the tree 
		else double_black(r);
	}
	//fix double black
	void double_black(position r) {
		//x's parent(also r's parent since r replaces x)
		position p = r ? r->parent : this->hot;
		if (!p)return;//s is root
		//r's sibling (cannot use r->sibling() since r may be nullptr)
		position s = (r == p->lc) ? p->rc : p->lc;
		if (is_black(s)) {
			position t = nullptr;
			if (is_red(s->rc))t = s->rc;
			if (is_red(s->lc))t = s->lc;
			if (t) {//case BB-1 : sibling is black and has at least one red child
				//let s's color be p's color and rotate
				rb_color old = color(p);
				position b = GET_PARENT_REF(p) = this->rotate_at(t);
				//set new local root's children to black
				if (b->has_lchild()) {
					set_color(b->lc, rb_color::black);
					update_height(b->lc);
				}
				if (b->has_rchild()) {
					set_color(b->rc, rb_color::black);
					update_height(b->rc);
				}
				set_color(b, old); update_height(b);
			} else {//case BB-2 : s does not have a red child
				//combine s with p
				set_color(s, rb_color::red);
				--s->height;
				if (is_red(p))//case BB-2R : p is red, change it to black
					set_color(p, rb_color::black);
				else {//case BB-2B : need to rebalance above
					--p->height; double_black(p);
				}
			}
		} else {//case BB-3 : sibling is red
			//swap colors of s and p and rotate at s's same side child
			//to make r's sibling become black
			set_color(s, rb_color::black);
			set_color(p, rb_color::red);
			position t = s->is_lchild() ? s->lc : s->rc;
			this->hot = p; GET_PARENT_REF(p) = this->rotate_at(t);
			//because p now is red
			//it will take at most once more to rebalance
			double_black(r);
		}
	}
	//rebalance after insertion
	void after_insertion(position x) {
		if (x->is_root()) {//if is root set color to black
			set_color(this->root, rb_color::black);
			++this->root->height;
		} else {
			//if parent is black then no need to rebalance
			position parent = x->parent; if (is_black(parent))return;
			//otherwise grandparent must exist and must be black
			position grand = parent->parent; position uncle = x->uncle();
			if (is_black(uncle)) {//case 1 :uncle is black
				//check if x is in the same side of x->parent
				if (x->is_lchild() == parent->is_lchild())
					//swap parent's color with grandparent's color
					set_color(parent, rb_color::black);		
				else//swap x's color with grandparent's color
				{ set_color(x, rb_color::black); }
				set_color(grand, rb_color::red);
				//rotate at x, then reconnect with the tree
				position grand_grand_parent = grand->parent;
				position r = GET_PARENT_REF(grand) = (this->rotate_at(x));
				r->parent = grand_grand_parent;
			} else {//case 2 :uncle is red
				//set parent and uncle to black
				//and set grandparent to red
				set_color(parent, rb_color::black);
				++parent->height;
				set_color(uncle, rb_color::black);
				++uncle->height;
				if (!grand->is_root())set_color(grand, rb_color::red);
				//it may cause unbalance above 
				//can be fixed recursively
				after_insertion(grand);
			}
		}
	}
	//override update height
	int update_height(position x) override{
		//height increases only when x is black
		x->height = std::max(stature(x->lc), stature(x->rc));
		return is_black(x) ? x->height++ : x->height;
	}

public:
	rb_tree(Comp const& cmp=Comp()):_Base(cmp){}
	rb_tree(rb_tree const& rhs):_Base(rhs){}
	//insertion
	position& insert(T const& val) {
		position& x = this->find(val); if (x)return x;
		++this->tree_size;//create a new node
		x = new_rbnode(val, this->hot, nullptr, nullptr, -1);
		after_insertion(x); //rebalance
		return x ? x : this->hot->parent;//return value always contains val
	}
	//removal
	bool erase(T const& val) {
		return erase(this->find(val));
	}

	bool erase(position& pos) {
		if (!pos)return false;//cannot erase nullptr
		//remove node and rebalance
		after_removal(this->remove_at(pos, this->hot));
		return true;
	}

	size_t size() { return this->tree_size; }

	// user interface part
	// output a node's info
	template<class Out>
	static Out& output_pos_info(Out& out, position p,position found=nullptr) {
		out << R"({"C":)";
		if (!p) return out << R"("N","V":null},)";
		out <<'"'<< ((found==p)?"rb":"RB")
		[std::underlying_type_t<rb_color>(color(p))]<<R"(","V":")"
			<< p->val;
		return out << R"(","H":")"<< p->height << R"("},)";
	}
	// pre-order traverse the tree and output info as json text
	template <class Out>
	static void output_pos(Out& out, position p,position found=nullptr) {
		output_pos_info(out, p,found);
		if (p) {
			output_pos(out, p->lc,found);
			output_pos(out, p->rc,found);
		}
	}
	template<class Out>
	Out& output_tree(Out& out, position found = nullptr) {
		out << size() << std::endl;
		out << "[";
		output_pos(out, this->root,found);
		return  out<< "]" << std::endl;
	}
	template<class Out>
	friend Out& operator<<(Out& out, rb_tree& tree) {
		return tree.output_tree(out, tree.root);
	}
};

#endif

