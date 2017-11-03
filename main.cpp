#include <functional>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <iomanip>
#include "list.h"
#include "vector.h"


using std::cout;
using std::cin;
using std::endl;
template <class Seq>
void output_list(const Seq& list){
    cout<<"Size:"<<list.size()<<" Pos:"<<(&list)<<endl;
    for(const auto& x:list){
        cout<<x<<" ";
    }
    cout<<endl;
}
template<class T, class Comp>
bool in_range(const T &target,  T mink,
               T maxk, Comp comp) {
    return comp(mink, target) && comp(target, maxk);
};

template<class T, class Comp>
void delete_range(list<T> &lst,
           T mink, T maxk,
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
template <class T>
void delete_range(list<T> &lst,T mink,T maxk){
    delete_range(lst,mink,maxk,std::less<T>());
}

template<class BidirIt>
void reverse(BidirIt first, BidirIt last) {
    while ((first != last) && (first != --last)) {
        std::swap(*first, *last);first++;
    }
}

template <class T,class Comp>
void merge_list(const list<T> &first, const list<T> &second,list<T>& result,Comp comp){
    auto iter1=first.begin(),iter2=second.begin();
    result.clear();
    while (iter1!=first.end()&&iter2!=second.end()){
        if (comp(*iter1,*iter2)){
            result.push_back(*iter1);
            iter1++;
        } else{
            result.push_back(*iter2);
            iter2++;
        }
    }
    while (iter1!=first.end()){
        result.push_back(*iter1);
        iter1++;
    }
    while (iter2!=second.end()){
        result.push_back(*iter2);
        iter2++;
    }
};

template <class T>
void merge_list(const list<T>& first,const list<T> &second
                   ,list<T>& result) {
    merge_list(first, second,result, std::less<T>());
}


int main() {
    cout<<"Test list"<<endl;
    list<int> listInt{1,2,3,4,5,6,7,8,9,10};
    listInt.erase(listInt.find(5));
    output_list(listInt);
    listInt.insert(listInt.find(4),5);
    output_list(listInt);
    listInt.push_back(11);
    output_list(listInt);
    listInt.push_front(0);
    output_list(listInt);
    reverse(listInt.begin(),listInt.end());
    output_list(listInt);
    delete_range(listInt,3,10);
    output_list(listInt);
    reverse(listInt.begin(),listInt.end());
    output_list(listInt);
    list<int> toMerge{5,6,7}, mergeResult;
    output_list(mergeResult);
    output_list(toMerge);
    merge_list(listInt,toMerge,mergeResult);
    output_list(mergeResult);
    cout<<"Test vector"<<endl;
    vector<int> vec{1,2,3,4,5};
    output_list(vec);
    vec.push_back(6);
    vec.push_back(7);
    output_list(vec);
    vec.pop_back();
    cout<<"vec[0] is "<<vec[0]<<endl;
    output_list(vec);
    return 0;
}