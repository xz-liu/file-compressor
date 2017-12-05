//
// Created by joker on 2017/11/18.
//

#ifndef DATA_STRUCTURE_EXP_EXP_5_H
#define DATA_STRUCTURE_EXP_EXP_5_H

#include <cstdlib>
#include <functional>
#include "queue.h"
#include <iostream>
#include "basic.h"

/// binary search O(log(n))
template<class T, class RandomIt, class Comp=std::less<>>
RandomIt search(RandomIt begin, RandomIt end,
        const T &value, Comp comp = std::less<>()) {
    size_t l = 0, r = end - begin;
    while (l < r) {
        size_t mid = (l + r) / 2;
        if (comp(value, *(begin + mid))) r = mid;
        else l = mid + 1;
    }
    return begin + --l;
}

template <class Iter,class Comp>
Iter quick_sort_partition(Iter begin,Iter end,Comp comp) {
    auto pivot = *begin;auto &&right=end-1;
    std::iter_swap(begin, right);
    Iter index = begin;
    for (auto i = begin; i != right; i++)
        if (comp(*i, pivot))std::iter_swap(i, index++);
    std::iter_swap(right, index);
    return index;
}

template <class Iter,class Comp=std::less<>>
void quick_sort(Iter begin, Iter end, Comp comp=std::less<>()){
    if(begin<end){
        Iter p=quick_sort_partition(begin,end,comp);
        quick_sort(begin, p, comp);
        quick_sort(p + 1, end, comp);
    }
}


inline void run_exp5_tests(){
    using std::cout;
    using std::endl;
    cout<<"Exp 5 : find and sort"<<endl<<endl;
    cout<<"Test sort(quick-sort)"<<endl;
    vector<int> vec{1,2,43,53,23,4,33,42,432,432,234,23,4,5};
    cout<<"Vector:"<<endl;
    output_list(vec);
    quick_sort(vec.begin(), vec.end());
    cout<<"Sorted"<<endl;
    output_list(vec);
    cout<<"Test binary search"<<endl;
    cout<<"Position of 5 in sorted vector: ";
    cout<<(std::distance(vec.begin(),search(vec.begin(),vec.end(),5))+1)<<endl;
}


#endif //DATA_STRUCTURE_EXP_EXP_5_H
