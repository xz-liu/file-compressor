//
// Created by joker on 2017/11/5.
//

#ifndef DATA_STRUCTURE_EXP_QUEUE_H
#define DATA_STRUCTURE_EXP_QUEUE_H

#include "list.h"
#include "bin_tree.h"
#include "vector.h"
#include <cstdlib>

template<class T>
class deque : public list<T> {};

template<class T>
class queue : private list<T> {
public:
    void push(const T &val) {
        list<T>::push_back(val);
    }

    void pop() {
        list<T>::pop_front();
    }

    size_t size() {
        return list<T>::size();
    }

    bool empty() {
        return list<T>::empty();
    }

    const T &front() {
        return list<T>::front();
    }

};

template<class T, class Seq=vector<T>, class Comp=std::less<>>
class priority_queue{
public:
    using container_type=Seq;
    using value_compare=Comp;
    using value_type=typename Seq::value_type;
    using size_type=typename Seq::size_type;
    using reference=typename Seq::reference;
    using const_reference=typename Seq::const_reference;
protected:
    Seq container;
    Comp comp;
    bool exists(size_type rank)
    { return rank < container.size(); }

    bool rank_comp(size_type ra, size_type rb)
    { return comp(container[ra], container[rb]); }

    void rank_swap(size_type a, size_type b) {
        std::iter_swap(container.begin() + a, container.begin() + b);
    }

    void heap_up(size_type rank) {
        while (rank && rank_comp((rank - 1) / 2, rank)) {
            rank_swap((rank - 1) / 2, rank);
            rank = (rank - 1) / 2;
        }
    }

    void heap_down(size_type rank) {
        while (true) {
            size_type lc = rank * 2 + 1, rc = rank * 2 + 2, mx;
            if (exists(lc)) {
                mx = lc;
                if (exists(rc) && rank_comp(mx, rc))mx = rc;
            } else break;
            if (rank_comp(rank, mx)) {
                rank_swap(rank, mx);
                rank = mx;
            } else break;
        }
    }

    void erase(size_type index) {
        if (container.empty())return;
        rank_swap(index, container.size() - 1);
        container.pop_back();
        heap_down(index);
    }
public:
    explicit
    priority_queue(Comp const& comp=Comp(),Seq const& seq=Seq())
    : comp(comp),container(seq){}

    size_type size() { return container.size(); }

    bool empty() { return container.empty(); }

    void push(const_reference val) {
        container.push_back(val);
        heap_up(container.size() - 1);
    }

    void pop() { erase(0); }

    const_reference top() { return container.front(); }

    template<class ...Args>
    void emplace(Args &&... args) {
        container.emplace_back(args...);
        heap_up(container.size() - 1);
    }
};


#endif //DATA_STRUCTURE_EXP_QUEUE_H
