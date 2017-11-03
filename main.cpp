#include <functional>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include "list.h"
#include "vector.h"
using std::cout;
using std::cin;
using std::endl;


template<class T, class Comp>
bool in_range(const T &target, const T &mink,
              const T &maxk, Comp comp = std::less<T>()) {
    return comp(mink, target) && comp(target, maxk);
};

template<class T, class Comp>
void delete_range(list<T> &lst,
          const T &mink, const T &maxk,
          Comp comp = std::less<T>()) {
    auto _begin=lst.begin();
    while (_begin!=lst.end()) {
        if(in_range(*_begin,mink,maxk,comp)){
            auto tmp=_begin;
            _begin++;
            lst.erase(tmp);
        } else{
            _begin++;
        }
    }
}

template<class BidirIt>
void reverse(BidirIt first, BidirIt last) {
    while ((first != last) && (first != --last)) {
        std::swap(*first++, *last);
    }
}

template <class T,class Comp>
list<T> merge_list(list<T> first,list<T> second,Comp comp= std::less<T>()){
    auto iter1=first.begin(),iter2=second.begin();
    list<T> result;
    while (iter1!=first.end()&&iter2!=second.end()){
        if (comp(*iter1,*iter2)){
            result.push_back(*iter1++);
        } else{
            result.push_back(*iter2++);
        }
    }
    while (iter1!=first.end())result.push_back(*iter1++);
    while (iter2!=second.end())result.push_back(*iter2++);
    return result;
};

#include <bits/stdc++.h>
using namespace std;
int main() {

    return 0;
}