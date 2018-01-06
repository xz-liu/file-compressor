#pragma once
#ifndef DATA_STRUCTURE_EXP_MAP_H
#define DATA_STRUCTURE_EXP_MAP_H
#include <iterator>
#include "rb_tree.h"
#include "rb_container_base.h"
/**
 * Comparer 
 * used to compare the first element of std::pair 
 */
template <class Comp> struct comp_first {
	Comp comp;
	comp_first( Comp const& comp=Comp()):comp(comp){}
	comp_first(comp_first const& another):comp(another.comp){}
	comp_first() = default;
	template<class _Ty1,class _Ty2> 
	constexpr auto operator() (_Ty1&& _Left, _Ty2&& _Right) const {
		return comp(static_cast<_Ty1&&>(_Left).first, static_cast<_Ty2&&>(_Right).first);
	}
};

/**
* Map
* A container imitating std::map
* implemented using red black tree
*/
template<class Key, class Value, class Comp = std::less<>>
struct map :rb_container_base< std::pair< Key, Value>, comp_first<Comp>,
	univ_bst_iter<std::pair< Key, Value>>,
	univ_bst_iter<std::pair< Key, Value>, std::pair< Key, Value> const>> {

	using _Base = rb_container_base < std::pair< Key, Value>, comp_first<Comp>,
		univ_bst_iter<std::pair< Key, Value>>,
		univ_bst_iter<std::pair< Key, Value>, std::pair< Key, Value> const>>;

	USING_TYPE_FROM_BASE(iterator);
	USING_TYPE_FROM_BASE(const_iterator);
	USING_TYPE_FROM_BASE(reverse_iterator);
	USING_TYPE_FROM_BASE(const_reverse_iterator);
	USING_TYPE_FROM_BASE(size_type);
	
	using key_type = Key;
	using mapped_type = Value;
	using value_type = std::pair<Key, Value>;
	using key_compare = Comp;
	using difference_type = std::ptrdiff_t;
	using reference = mapped_type&;
	using const_reference = const mapped_type&;
	
private:
	key_compare key_comp;

	template<bool _FillZero=false>
	value_type make_search(key_type const& key) {
		value_type x;x.first = key;
		if constexpr(_FillZero&&std::is_trivial_v<mapped_type>)
			memset(&x.second, 0, sizeof(mapped_type));
		return x;
	}
public:
	
	explicit map(key_compare const& cmp=Comp()) 
	: _Base(comp_first<Comp>(cmp)), key_comp(cmp){}

	map(std::initializer_list<value_type>&& init_list,key_compare const& cmp = Comp())
		:_Base(std::forward<std::initializer_list<value_type>>(init_list), cmp), key_comp(cmp){}

	template<class Iter>
	map(Iter first, Iter second, Comp const& cmp = Comp())
		: _Base(first, second, cmp), key_comp(cmp) {}
	
	map(map const& rhs) :_Base(rhs),key_comp(rhs.key_comp){}
	
	map& operator=(map const& rhs) {
		_Base::_BinTree::operator=(rhs);
		key_comp = rhs.key_comp;
		return *this;
	}

	void swap(map const& rhs) {
		std::swap(key_comp, rhs.key_comp);
		_Base::swap(rhs);
	}

	iterator find(const key_type& key) {
		return _Base::find(make_search(key));
	}

	bool erase(const key_type& key) {
		return _Base::erase(make_search(key));
	}

#define SEARCH_BY_KEY(return_type,name,if_const,when_fail)\
	return_type name(key_type key) if_const{\
		iterator x = find(key);\
		if (x == this->end())when_fail;\
		return x->second;\
	}

	SEARCH_BY_KEY(reference, operator[], ,
		x = _Base::insert(make_search<true>(key)));
	SEARCH_BY_KEY(const_reference, operator[], 
		const,x = _Base::insert(make_search<true>(key)));
	SEARCH_BY_KEY(reference, at, ,
		throw std::out_of_range("key not found"));
	SEARCH_BY_KEY(const_reference, at, const,
		throw std::out_of_range("key not found"));

#undef SEARCH_BY_KEY

};
#endif