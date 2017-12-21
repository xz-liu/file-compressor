#pragma once
#ifndef DATA_STRUCTURE_EXP_SET_BASE_H
#define DATA_STRUCTURE_EXP_SET_BASE_H

#include "rb_tree.h"

#define ITER_OPTR(type,op,fun)\
type operator op (int)\
	{var tmp=*this;item=item->fun();return tmp;}\
type& operator op ()\
	{item = item->fun(); return *this; }

/**
 *  a universal iterator used in bin_tree based types which use 
 *  bintree_node, a class which next() and prev() implemented, 
 *  as nodes. when IndType is T const it becomes const iterator 
 */
template<class T, class IndType = T>
struct univ_bst_iter {
	using node = bintree_node<T, rb_color>;
	using ptr = node*;
	using const_ptr = const node*;
	ptr item;
	template<class Ind>
	univ_bst_iter(const univ_bst_iter<T, Ind>& rhs) :item(rhs.item) {}
	univ_bst_iter(ptr p = nullptr) :item(p) {}
	univ_bst_iter(const_ptr p) :item(const_cast<ptr>(p)) {}
	ITER_OPTR(univ_bst_iter, ++, next);
	ITER_OPTR(univ_bst_iter, --, prev);
	bool operator!=(const univ_bst_iter& rhs) { return item != rhs.item; }
	bool operator==(const univ_bst_iter& rhs) { return item == rhs.item; }
	IndType& operator*() const {
		return (item->val);
	}
	IndType* operator->() const {
		return (&item->val);
	}
};

#undef ITER_OPTR

#define USING_TYPE_FROM_BASE(type) \
	typedef typename _Base::type type
/**
 * base for map and set
 * implements functions about iterator
 * and insert, erase and so on...
 */
template<class T, class Comp,
	class _Iter, class _CIter, class _Base = rb_tree<T, Comp>>
struct rb_container_base : _Base {
	using iterator = _Iter;
	using const_iterator = _CIter;
	using reverse_iterator = std::reverse_iterator<_Iter>;
	using const_reverse_iterator = std::reverse_iterator<_CIter>;
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = T const&;
	using position = typename _Base::position;

protected:
	using _BST = bst<T, Comp, rb_color>;
	using _BinTree = bin_tree<T, rb_color>;
	using _Node = bintree_node<T, rb_color>;

	rb_container_base(std::initializer_list<T> const& init_list,Comp const& comp)
		:_Base(comp) {
		insert(init_list.begin(),init_list.end());
	}

	rb_container_base(rb_container_base const& rhs):_Base(rhs){}
		
	template<class Iter>
	rb_container_base(Iter begin,Iter end,Comp const& cmp)
		:_Base(cmp) {
		insert(begin, end);
	}

	rb_container_base(Comp const& cmp) :_Base(cmp) {}

public:

	template<class Iter>
	void assign(Iter begin, Iter end) {
		this->clear();
		insert(begin, end);
	}

	void assign(rb_container_base const& another) {
		assign(another.begin(), another.end());
	}

	void swap(rb_container_base const& rhs) {
		std::swap(this->root, rhs.root);
		std::swap(this->comp, rhs.comp);
		std::swap(this->tree_size, rhs.tree_size);
	}


	iterator begin() noexcept {
		return iterator(this->begin_node());
	}
	iterator end() noexcept {
		return iterator();
	}
	const_iterator cbegin() const noexcept {
		return const_iterator(this->begin_node());
	}
	const_iterator cend() const noexcept {
		return const_iterator();
	}
	const_iterator begin() const noexcept {
		return cbegin();
	}
	const_iterator end() const noexcept {
		return cend();
	}
	reverse_iterator rbegin() noexcept {
		return reverse_iterator(this->end_node());
	}
	reverse_iterator rend() noexcept {
		return reverse_iterator();
	}
	const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator(this->end_node());
	}
	const_reverse_iterator crend() const noexcept {
		return const_reverse_iterator();
	}
	const_reverse_iterator rbegin() const noexcept {
		return crbegin();
	}
	const_reverse_iterator rend() const noexcept {
		return crend();
	}

	bool operator==(rb_container_base const& rhs) const{
		if (this->size() != rhs.size())return false;
		iterator left = begin(), right = rhs.begin();
		while (left!=end()) {
			if (!_IS_EQUAL(*left++, *right++, this->comp))return false;
		}
		return true;
	}

	template<class Iter>
	void insert(Iter first, Iter last) {
		while (first != last)_Base::insert(*first++);
	}

	iterator insert(const_reference val) {
		return _Base::insert(val);
	}

	iterator find(const_reference val) {
		position x = _Base::find(val);
		if (x&& _IS_EQUAL(x->val, val, _Base::comp))
			return x;
		return end();
	}

	const_iterator find(const_reference val) const {
		return (const_cast
			<rb_container_base<T, Comp, _Iter, _CIter, _Base>*>
			(this))->find(val);
	}

	bool empty() { return !this->size(); }

};

#endif
