#pragma once
#ifndef DATA_STRUCTURE_EXP_SET_H
#define DATA_STRUCTURE_EXP_SET_H

#include "rb_tree.h"

template<class T>
struct set_iterator {
	using node = bintree_node<T, rb_color>;
	using ptr = node*;
	ptr item;
	set_iterator(ptr p) :item(p) {}
	set_iterator operator++(int) {
		auto tmp = *this;
		item = item->next();
		return tmp;
	}
	set_iterator& operator++() {
		item = item->next();
		return *this;
	}
	T& operator*() {
		return item->val();
	}
};
template<class T>
struct const_set_iterator {
	using node = bintree_node<T, rb_color>;
	using ptr = node*;
	ptr item;
	const_set_iterator(ptr p) :item(p) {}
	const_set_iterator operator++(int) {
		auto tmp = *this;
		item = item->next();
		return tmp;
	}
	const_set_iterator& operator++() {
		item = item->next();
		return *this;
	}
	T const& operator*() {
		return item->val();
	}
};

template<class T,class Comp=std::less<>,class _Iter,class _CIter>
struct set_base: rb_tree<T,Comp> {
	using iterator = _Iter;
	using const_iterator = _CIter;

};

#endif
