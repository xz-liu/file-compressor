//
// Created by joker on 2017/11/18.
//

#ifndef DATA_STRUCTURE_EXP_EXP_5_H
#define DATA_STRUCTURE_EXP_EXP_5_H

#include <cstdlib>
#include <functional>

/// binary search O(log(n))
template<class T, class RandomIt, class Comp>
RandomIt search(RandomIt begin, RandomIt end,
                const T &value, Comp comp = std::less<T>()) {
    size_t l = 0, r = end - begin;
    while (l < r) {
        size_t mid = (l + r) / 2;
        if (comp(value, *(begin + mid))) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return begin + --l;
}

template<class RandomIt,class Comp>
void qsort(RandomIt head,RandomIt tail,Comp comp) {
    if (head == tail) return;
    RandomIt i = head, j = tail;
    auto pivot = *head;
    while (i != j) {
        while (i != j && comp(pivot, *j))j--;
        *i = *j;
        while (i != j && comp(*i, pivot)) i++;
        *j = *i;
    }
    *i = pivot;
    qsort(head, i - 1, comp);
    qsort(j + 1, tail, comp);
}

template <class Iter>
void qsort(Iter first,Iter last){
    qsort(first,last,std::less<decltype(*first)>());
}



#endif //DATA_STRUCTURE_EXP_EXP_5_H
