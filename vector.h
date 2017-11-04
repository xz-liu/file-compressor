//
// Created by joker on 2017/10/31.
//

#ifndef DATA_STRUCTURE_EXP_VECTOR_H
#define DATA_STRUCTURE_EXP_VECTOR_H
#include <memory>

template<class T, size_t BEGIN = 100>
class vector {
protected:
    T *impl_begin;
    T *impl_end;
    size_t cap;

    void init_cap(size_t size) {
        cap = BEGIN;
        while (cap <= size)cap <<= 1;
        impl_begin = new T[cap];
        impl_end = impl_begin;
    }

    void resize_cap(size_t size, bool reserve = true) {
        size_t pre = cap;
        while (cap <= size)cap <<= 1;
        if (pre < cap) {
            iterator new_place = new T[cap],
                    itpre = begin(), it = new_place;
            if (reserve) {
                while (itpre != end()) {
                    new(it++)T(*itpre++);
                }
                impl_end = it;
            }
            delete[]impl_begin;
            impl_begin = new_place;
            if (!reserve)impl_end = impl_begin;
        } else {
            impl_end = impl_begin + size;
        }
    }

public:
    using iterator=T *;
    using const_iterator=const T *const;

    iterator begin() { return impl_begin; }

    iterator end() { return impl_end; }

    const_iterator begin() const { return impl_begin; }

    const_iterator end() const { return impl_end; }

    const_iterator cbegin() const { return impl_begin; }

    const_iterator cend() const { return impl_end; }

    size_t size() const {
        return impl_end - impl_begin;
    }

    virtual bool empty() { return !size(); }

    vector() {
        init_cap(0);
    }

    vector(std::initializer_list<T> init_list)
            : vector() {
        for (auto x:init_list) {
            push_back(x);
        }
    }

    vector(const vector &rhs) {
        init_cap(rhs.size());
        T *now = impl_begin;
        for (const auto &x:rhs) {
            new(now++)T(x);
        }
        impl_end = impl_begin + rhs.size();
    }

    vector &operator=(const vector &rhs) {
        resize_cap(rhs.size(), false);
        T *now = impl_begin;
        for (const auto &x:rhs) {
            new(now++)T(x);
        }
        impl_end = impl_begin + rhs.size();
    }

    explicit vector(size_t size) {
        init_cap(size);
        impl_end = impl_begin + size;
    }

    vector(size_t size, const T &init_with) :
            vector(size) {
        iterator now = begin();
        while (now != end()) {
            new(now++) T(init_with);
        }
    }

    virtual ~vector() {
        delete[]impl_begin;
    }

    void clear() {
        delete[]impl_begin;
        init_cap(0);
    }

    void push_back(const T &value) {
        if (size() >= cap)resize_cap(size());
        new(impl_end++) T(value);
    }

    void pop_back() {
        if (size()) {
            impl_end--;
        }
    }

    void push_front(const T &value) {
        insert(begin(), value);
    }

    void pop_front() {
        erase(begin());
    }

    void erase(iterator iter) {
        if (size()) {
            iterator it = iter;
            iterator _end = end();
            _end--;
            while (it != _end) {
                new(it)T(*(it + 1));
                it++;
            }
            impl_end = _end;
        }
    }

    void erase(size_t pos) {
        erase(begin() + pos);
    }

    T& back(){
        return impl_end[-1];
    }

    T& front(){
        return *impl_begin;
    }

    void insert(iterator iter, const T &value) {
        resize_cap(size());
        iterator back = end();
        while (back != iter) {
            if (back < begin())
                return;
            back--;
            back[1] = *back;
        }
        impl_end++;
        new(iter) T(value);
    }

    void resize(size_t size) {
        resize_cap(size, false);
    }

    T &operator[](size_t rank) {
        return impl_begin[rank];
    }
};



#endif //DATA_STRUCTURE_EXP_VECTOR_H
