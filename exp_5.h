//
// Created by joker on 2017/11/18.
//

#ifndef DATA_STRUCTURE_EXP_EXP_5_H
#define DATA_STRUCTURE_EXP_EXP_5_H

#include <cstdlib>
#include <functional>

/// binary search O(log(n))
template<class T, class RandomIt, class Comp=std::less<T>>
RandomIt search(RandomIt begin, RandomIt end,
                const T &value, Comp comp = std::less<T>()) {
    size_t l = 0, r = end - begin;
    while (l < r) {
        size_t mid = (l + r) / 2;
        if (comp(value, *(begin + mid))) r = mid;
        else l = mid + 1;
    }
    return begin + --l;
}

template <class Iter,class Comp>
Iter quick_sort_partition(Iter begin,Iter end,Comp comp){
    auto pivot=*begin;
    std::iter_swap(begin,end-1);
    Iter index=begin;
    for(auto i=begin;i<end-1;i++)
        if (comp(*i,pivot)){
            std::iter_swap(i,index);
            index++;
        }
    std::iter_swap(end-1,index);
    return index;
};

template <class Iter,class Comp>
void quicksort(Iter begin, Iter end, Comp comp){
    if(begin<end){
        Iter p=quick_sort_partition(begin,end,comp);
        quicksort(begin, p, comp);
        quicksort(p + 1, end, comp);
    }
}

template <class Iter>
void quicksort(Iter first,Iter last){
    quicksort(first, last,
    std::less<typename std::remove_reference<decltype(*first)>::type>());
}

void run_exp5_tests(){
    using std::cout;
    using std::endl;
    std::cout<<"Exp 5 : find and sort"<<endl;
    vector<int> vec{1,2,43,53,23,4,33,42,432,432,234,23,4,5};
    cout<<"Vector:"<<endl;
    output_list(vec);
    quicksort(vec.begin(),vec.end());
    cout<<"Sorted"<<endl;
    output_list(vec);
    std::sort(vec.begin(),vec.end());
    cout<<"Position of 5 in sorted vector"<<endl;
    cout<<std::distance(vec.begin(),search(vec.begin(),vec.end(),5))<<endl;

}


#endif //DATA_STRUCTURE_EXP_EXP_5_H
