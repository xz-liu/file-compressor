//
// Created by joker on 2017/11/5.
//

#ifndef DATA_STRUCTURE_EXP_EXP_1_H
#define DATA_STRUCTURE_EXP_EXP_1_H

#include <functional>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <typeinfo>
#include <iomanip>
#include "list.h"
#include "vector.h"


template<class Seq>
void output_list(const Seq &list) {
    std::cout << "Size:" << list.size() << " Pos:" << (&list) << std::endl;
    for (const auto &x:list) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

template<class T, class Comp=std::less<>>
void merge_list(const list<T> &first, const list<T> &second,
                list<T> &result, Comp comp = std::less<>()) {
    auto iter1 = first.begin(), iter2 = second.begin();
    result.clear();
    while (iter1 != first.end() && iter2 != second.end())
        if (comp(*iter1, *iter2))result.push_back(*iter1++);
        else result.push_back(*iter2++);
    while (iter1 != first.end())result.push_back(*iter1++);
    while (iter2 != second.end())result.push_back(*iter2++);
};


template<class T, class Comp=std::less<>>
void insert_sorted(list<T> &lst, const T &val, Comp comp = std::less<>()) {
    auto iter = lst.begin();
    while (iter != lst.end()) {
        if (comp(val, *iter)) break;
        iter++;
    }
    iter--;
    lst.insert(iter, val);
}

template<class T, class Comp>
bool in_range(const T &target, T mink,
              T maxk, Comp comp) {
    return comp(mink, target) && comp(target, maxk);
};

template<class T, class Comp=std::less<>>
void delete_range(list<T> &lst, T mink, T maxk,
                  Comp comp = std::less<>()) {
    auto _begin = lst.begin();
    while (_begin != lst.end()) {
        if (in_range(*_begin, mink, maxk, comp)) {
            auto tmp = _begin;
            _begin++;
            lst.erase(tmp);
        } else _begin++;
    }
}

template<class BidirIt>
void reverse(BidirIt first, BidirIt last) {
    while ((first != last) && (first != --last))
        std::iter_swap(first++, last);
}

template <class T>
auto reverse_linked_list(list_node<T>* head){
    decltype(head) prev= nullptr,curr=head;
    while (curr){
        auto nxt=curr->next;
        curr->next=prev;
        prev=curr;
        curr=nxt;
    }
    return prev;
}

void run_exp1_tests() {
    using std::cout;
    using std::endl;
    cout << "Exp 1 :vector and list" << endl << endl;
    cout << "Test list" << endl;
    list<int> listInt{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    output_list(listInt);
    cout << "Erase 5" << endl;
    listInt.erase(listInt.find(5));
    output_list(listInt);
    cout << "Insert 5 after 4" << endl;
    listInt.insert(listInt.find(4), 5);
    output_list(listInt);
    cout << "Push back 11" << endl;
    listInt.push_back(11);
    output_list(listInt);
    cout << "Push front 0" << endl;
    listInt.push_front(0);
    output_list(listInt);
    cout << "Reverse list" << endl;
    reverse(listInt.begin(), listInt.end());
    output_list(listInt);
    cout << "Delete range(3,10)" << endl;
    delete_range(listInt, 3, 10);
    output_list(listInt);
    cout << "Reverse list" << endl;
    reverse(listInt.begin(), listInt.end());
    output_list(listInt);
    list<int> toMerge{5, 6, 7}, mergeResult;
    cout << "Merge with ";
    output_list(toMerge);
    merge_list(listInt, toMerge, mergeResult);
    output_list(mergeResult);
    cout << "Insert 5 in sorted list" << endl;
    insert_sorted(mergeResult, 5);
    output_list(mergeResult);
    cout << "Test vector" << endl;
    vector<int> vec{1, 2, 3, 4, 5};
    output_list(vec);
    cout << "Push back 6" << endl;
    vec.push_back(6);
    cout << "Push back 7" << endl;
    vec.push_back(7);
    output_list(vec);
    cout << "Pop back" << endl;
    vec.pop_back();
    cout << "vec[0] is " << vec[0] << endl;
    output_list(vec);
}

#endif //DATA_STRUCTURE_EXP_EXP_1_H
