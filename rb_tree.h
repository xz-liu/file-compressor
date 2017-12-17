#pragma once

#ifndef DATA_STRUCTURE_EXP_RB_TREE_H
#define DATA_STRUCTURE_EXP_RB_TREE_H
#include <functional>
#include "bst.h"

enum class rb_color {
	red, black
};

template<class T, class Comp = std::less<>>
class rb_tree :public bst<T, Comp, rb_color> {
public:
	using position = typename bst<T, Comp, rb_color>::position;
protected:
	static bool is_black(position p) {
		return (!(p) || (rb_color::black == color(p)));
	}
	static bool is_red(position p) { return !is_black(p); }
	static rb_color& color(position p) { return p->status.val(); }
	static rb_color set_color(position p, rb_color c) {
		p->status.assign(c);
		return c;
	}
	static int stature(position x) { return bintree_node<T, rb_color>::stature(x); }
	static bool black_height_updated(position x) {
		return (stature(x->lc) == stature(x->rc))
			&& (x->height == (is_red(x) ?
				stature(x->lc) : stature(x->lc) + 1));
	}

	template<class ...Args>
	static position new_rbnode(Args&&...args) {
		position x = new bintree_node<T, rb_color>
			(std::forward<Args>(args)...);
		set_color(x, rb_color::red);
		return x;
	}

#define GET_PARENT_REF(x)	((x) == this->root ? this->root : ((x)->is_lchild() ? (x)->parent->lc : (x)->parent->rc))

	void black_black(position now) {
		position p = now ? now->parent : this->hot;
		if (!p)return;
		position s = (now == p->lc) ? p->rc : p->lc;
		if (is_black(s)) {
			position t = nullptr;
			if (is_red(s->rc))t = s->rc;
			if (is_red(s->lc))t = s->lc;
			if (t) {
				rb_color old = color(p);
				position b = GET_PARENT_REF(p) = this->rotate_at(t);
				if (b->has_lchild()) {
					set_color(b->lc, rb_color::black);
					update_height(b->lc);
				}
				if (b->has_rchild()) {
					set_color(b->rc, rb_color::black);
					update_height(b->rc);
				}
				set_color(b, old); update_height(b);
			} else {
				set_color(s, rb_color::red);
				--s->height;
				if (is_red(p))set_color(p, rb_color::black);
				else {
					p->height;
					black_black(p);
				}
			}
		} else {
			set_color(s, rb_color::black);
			set_color(p, rb_color::red);
			position t = s->is_child() ? s->lc : s->rc;
			this->hot = p; GET_PARENT_REF(p) = this->rotate_at(t);
			black_black(now);
		}
	}

	void red_red(position x) {
		if (x->is_root()) {
			set_color(this->root, rb_color::black);
			++this->root->height;
		} else {
			position p = x->parent; if (is_black(p))return;
			position grand = p->parent; position u = x->uncle();
			if (is_black(u)) {
				if (x->is_lchild() == p->is_lchild())
					set_color(p, rb_color::black);
				else { set_color(x, rb_color::black); }
				set_color(grand, rb_color::red);
				position gg = grand->parent;
				position r = GET_PARENT_REF(grand) = (this->rotate_at(x));
				r->parent = gg;
			} else {
				set_color(p, rb_color::black);
				++p->height;
				set_color(u, rb_color::black);
				++u->height;
				if (!grand->is_root())set_color(grand, rb_color::red);
				red_red(grand);
			}
		}
	}
	int update_height(position x) override{
		x->height = std::max(stature(x->lc), stature(x->rc));
		return is_black(x) ? x->height++ : x->height;
	}

public:
	position& insert(T const& val)override {
		position& x = this->find(val); if (x)return x;
		++this->tree_size;
		x = new_rbnode(val, this->hot, nullptr, nullptr, -1);
		red_red(x); return x ? x : this->hot->parent;
	}
	bool erase(T const& val)override {
		position&x = this->find(val);
		if (!x)return false;
		position r = this->remove_at(x, this->hot);
		if (!(--this->tree_size))return true;
		if (!this->hot) {
			set_color(this->root, rb_color::black);
			update_height(this->root);
		} else if (black_height_updated(this->hot))
			return true;
		else if (is_red(r)) {
			set_color(r, rb_color::black);
			++r->height;
		} else black_black(r);
		return true;
	}

	void clear() override{
		bin_tree<T, rb_color>::clear();
		this->tree_size = 0;
	}

	size_t size() { return this->tree_size; }

	template<class Out>
	static Out& output_pos_info(Out& out, position p,position found=nullptr) {
		out << R"({"Type":)";
		if (!p) return out << R"("N","Value":null},)";
		out <<'"'<< ((found==p)?"rb":"RB")
		[std::underlying_type_t<rb_color>(color(p))]<<R"(","Value":")"
			<< p->val;
		return out << R"("},)";
	}
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
		return output_tree(out, tree.root);
	}
};

#endif

