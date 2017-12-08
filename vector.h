//
// Created by joker on 2017/10/31.
//

#ifndef DATA_STRUCTURE_EXP_VECTOR_H
#define DATA_STRUCTURE_EXP_VECTOR_H
#include <memory>
#include <iterator>
#include <allocators>
#include <type_traits>

template<class T, class Allocator=std::allocator<T>>
class vector {
public:
	typedef T value_type;
	typedef T& reference;
	typedef	const T& const_reference;
	typedef size_t size_type;
	using iterator = T *;
	using const_iterator = const T *const;
	using reverse_iterator = 
		std::reverse_iterator<iterator>;
	using const_reverse_iterator =
		std::reverse_iterator<const_iterator>;
protected:
	static constexpr size_t MIN_ALLOC = 128;
	T *impl_begin,* impl_end;
	size_t impl_cap;
	Allocator alloc;

	template<class _T>
	std::enable_if_t<std::conjunction_v<std::is_default_constructible<_T>>>
	init_construct(_T* sz){while (sz!=impl_begin)alloc.construct(--sz);}
	
	template<class _T>
	std::enable_if_t<!std::conjunction_v<std::is_default_constructible<_T>>>
	init_construct(_T* sz) { }

	void init_construct(size_t sz){
		init_construct(impl_end = impl_begin + sz);
	}

	void init_cap(size_t size) {
		impl_cap = MIN_ALLOC;
		while (impl_cap <= size)impl_cap <<= 1;
		impl_begin = alloc.allocate(impl_cap);
		impl_end = impl_begin;
	}

	void resize_cap(size_t size, bool reserve = true) {
		size_t pre = impl_cap;
		while (impl_cap <= size)impl_cap <<= 1;
		if (pre < impl_cap) {
			iterator new_place = alloc.allocate(impl_cap);
			iterator itpre = begin(), it = new_place;
			while (itpre != end()) {
				if (reserve)
					alloc.construct(it++, *itpre);
				alloc.destroy(itpre++);
			}
			impl_begin = new_place;
			impl_end = reserve ? it : impl_begin;
		}
	}

	void move_to_iter_right(iterator& iter) {
		auto dis = std::distance(begin(), iter);
		resize_cap(size());
		iter = dis + begin();
		iterator back = end();
		while (back != iter) {
			if (back < begin())
				return;
			--back;
			alloc.construct(back + 1, *back);
			alloc.destroy(back);
		}
		++impl_end;
	}

	void destroy_all(){
		iterator now = impl_begin;
		while (now != impl_end)
			alloc.destroy(now++);
		alloc.deallocate(impl_begin,impl_cap);
	}
public:

	iterator begin() { return impl_begin; }

	iterator end() { return impl_end; }

	const_iterator begin() const { return impl_begin; }

	const_iterator end() const { return impl_end; }

	const_iterator cbegin() const { return impl_begin; }

	const_iterator cend() const { return impl_end; }

	reverse_iterator rbegin() {
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const {
		return (const_reverse_iterator(end()));
	}

	reverse_iterator rend() {
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator rend() const {
		return (const_reverse_iterator(begin()));
	}
	
	size_t size() const {
		return impl_end - impl_begin;
	}

	virtual bool empty() { return !size(); }
	
	template<class Iter>
	void assign(Iter _begin,Iter _end){
		resize_cap(std::distance(begin(), end()), false);
		while (begin != end) alloc.construct(impl_end++, *begin++);
	}
	
	void assign(size_type cnt,const T&& val){
		resize_cap(cnt,false);
		impl_end = impl_begin + cnt;
		for (auto n = begin(); n != end(); ++n)
			alloc.construct(n, val);
	}

	vector() { init_cap(0); }

	template<class Iter>vector(Iter begin,Iter end){
		init_cap(std::distance(begin, end));
		while (begin != end) alloc.construct (impl_end++,*begin++);
	}

	vector(std::initializer_list<T> init_list)
		: vector() {
		for (auto x : init_list) {
			push_back(x);
		}
	}

	vector(const vector &rhs) {
		init_cap(rhs.size());
		for (const auto &x : rhs) {
			alloc.construct(impl_end++,x);
		}
	}

	vector &operator=(const vector &rhs) {
		resize_cap(rhs.size(), false);
		T *now = impl_begin;
		for (const auto &x : rhs) {
			alloc.construct(now++,x);
		}
		impl_end = impl_begin + rhs.size();
		return *this;
	}

	explicit vector(size_t size) {
		init_cap(size);
		init_construct(size);
	}

	vector(size_t size, const T &init_with)  {
		init_cap(size);
		impl_end = impl_begin + size;
		iterator now = begin();
		while (now != impl_end) {
			alloc.construct(now++,init_with);
		}
	}

	virtual ~vector() {
		destroy_all();
	}

	void clear() {
		destroy_all();
		init_cap(0);
	}

	void push_back(const T &value) {
		if (size() >= impl_cap)resize_cap(size());
		alloc.construct(impl_end++,value);
	}

	void pop_back() { if (size()) alloc.destroy(--impl_end); }

	void push_front(const T &value){
		insert(begin(), value);
	}

	void pop_front() { erase(begin()); }

	void erase(iterator iter) {
		if (size()) {
			iterator it = iter;
			iterator _end = end();
			_end--;
			while (it != _end) {
				alloc.destroy(it);
				alloc.construct(it,*(it + 1));
				it++;
			}
			alloc.destroy(impl_end);
			impl_end = _end;
		}
	}

	void erase(size_t pos) { erase(begin() + pos); }

	reference back() { return end()[-1]; }

	reference front() { return begin()[0]; }

	const_reference back() const { return end()[-1]; }

	const_reference front() const { return 0[begin()]; }
	
	void insert(iterator iter, const T &value) {
		move_to_iter_right(iter);
		alloc.construct(iter,value);
	}

	void resize(size_t size) {
		resize_cap(size, false);
		impl_end = impl_begin + size;
	}

	void reserve(size_t new_size){
		if (impl_cap < new_size)resize_cap(new_size, true);
	}

	template <class ...Args>
	void emplace(iterator _where,Args&&... args) {
		move_to_iter_right(_where);
		alloc .construct(_where,std::forward<Args>(args)...);
	}

	template <class ...Args>
	void emplace_back(Args&&... args){
		emplace(end(),std::forward<Args>(args)...);
	}

	template<class ...Args>
	void emplace_front(Args&&... args){
		emplace(begin(), std::forward<Args>(args)...);
	}

	T &operator[](size_t rank) { return impl_begin[rank]; }

	const T &operator[](size_t rank) const { return impl_begin[rank]; }
};


#endif //DATA_STRUCTURE_EXP_VECTOR_H
