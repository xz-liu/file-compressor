//
// Created by joker on 2017/11/5.
//

#ifndef DATA_STRUCTURE_EXP_QUEUE_H
#define DATA_STRUCTURE_EXP_QUEUE_H

#include "list.h"
#include <cstdlib>

template <class T>
class deque: public list<T>{};

template <class T>
class queue:private list<T>{
public:
    void push(const T& val){
        list<T>::push_back(val);
    }
    void pop(){
        list<T>::pop_back();
    }
    size_t size(){
        return list<T>::size();
    }
    bool empty(){
        return list<T>::empty();
    }
    T& front(){
        return list<T>::front();
    }
};

#endif //DATA_STRUCTURE_EXP_QUEUE_H
