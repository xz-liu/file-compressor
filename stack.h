//
// Created by joker on 2017/11/5.
//

#ifndef DATA_STRUCTURE_EXP_STACK_H
#define DATA_STRUCTURE_EXP_STACK_H

#include "vector.h"

template <class T>
class stack:private vector<T>{
public:
    stack():vector<T>(){}
    void push(const T& val){
        vector<T>::push_back(val);
    }
    void pop(){
        vector<T>::pop_back();
    }
    size_t size(){
        return vector<T>::size();
    }
    bool empty(){
        return vector<T>::empty();
    }
    T& top(){
        return vector<T>::back();
    }
};


#endif //DATA_STRUCTURE_EXP_STACK_H
