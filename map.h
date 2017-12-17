#pragma once
#ifndef DATA_STRUCTURE_EXP_MAP_H
#define DATA_STRUCTURE_EXP_MAP_H
#include <iterator>
#include "rb_tree.h"
#include "set_base.h"
template<class Key,class Value,class Comp=std::less<>>
struct key_value_pair {
	Key key;
	Value val;
	bool operator<(const key_value_pair& rhs)const {
		return Comp(key, rhs.key);
	}
	std::pair<Key&,Value&> get_pair() {
		return std::pair<Key&, Value&>(key, val);
	}
	std::pair<Key,Value> get_const_pair()const {
		return std::pair<Key, Value>(key, val);
	}
};

template<class Key, class Value> struct map_iterator
	:set_iterator<key_value_pair<Key, Value>> {
	using base = set_iterator<key_value_pair<Key, Value>>;
	using node = typename base::node;
	using ptr = typename base::ptr;
	map_iterator(ptr p) :base(p) {}
	map_iterator operator++(int) {
		auto tmp = *this;
		this->item = this->item->next();
		return tmp;
	}
	map_iterator& operator++() {
		this->item = this->item->next();
		return *this;
	}
	std::pair<Key&, Value&> operator*() {
		return (base::operator*()).get_pair();
	}
};

template<class Key, class Value> struct const_map_iterator
	:set_iterator<key_value_pair<Key, Value>> {
	using base = set_iterator<key_value_pair<Key, Value>>;
	using node = typename base::node;
	using ptr = typename base::ptr;
	const_map_iterator(ptr p) :base(p) {}
	const_map_iterator operator++(int) {
		auto tmp = *this;
		this->item = this->item->next();
		return tmp;
	}
	const_map_iterator& operator++() {
		this->item = this->item->next();
		return *this;
	}
	std::pair<Key, Value> operator*() {
		return (base::operator*()).get_const_pair();
	}
};


template<class Key,class Value, class Comp = std::less<>>
struct map : set_base<key_value_pair<Key, Value>, Comp, 
map_iterator<Key, Value>,const_map_iterator<Key,Value>> {
	using base = set_base<key_value_pair<Key, Value>, Comp,
		map_iterator<Key, Value>, const_map_iterator<Key, Value>>;
	using iterator = map_iterator<Key, Value>;
	using const_iterator = const_map_iterator<Key, Value>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

};

#endif
#pragma once
