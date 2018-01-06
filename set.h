#pragma once

#ifndef DATA_STRUCTURE_EXP_SET_H
#define DATA_STRUCTURE_EXP_SET_H
#include <functional>
#include "rb_container_base.h"

template <class T, class Comp = std::less<>,
	class _Base=rb_container_base<T,Comp,
	univ_bst_iter<T,T>,
	univ_bst_iter<T,T const>>>
struct set:_Base {

	USING_TYPE_FROM_BASE(iterator);
	USING_TYPE_FROM_BASE(const_iterator);
	USING_TYPE_FROM_BASE(reverse_iterator);
	USING_TYPE_FROM_BASE(const_reverse_iterator);
	USING_TYPE_FROM_BASE(size_type);

	using key_type = T;
	using value_type = T;
	using key_compare = Comp;
	using reference = value_type&;
	using const_reference = const value_type&;

	explicit set(key_compare const& cmp = Comp())
		: _Base(comp_first<Comp>(cmp)){}

	set(std::initializer_list<_KeyPair>const& init_list,
		key_compare const& cmp = Comp())
		:_Base(init_list, cmp) {}

	template<class Iter>
	set(Iter first, Iter second, Comp const& cmp = Comp())
		: _Base(first, second, cmp) {}

	set(set const& rhs) :_Base(rhs) {}

	set& operator=(set const& rhs) {
		_Base::_BinTree::operator=(rhs);
		return *this;
	}
};

#endif
