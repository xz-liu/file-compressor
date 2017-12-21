//
// Created by joker on 2017/11/5.
//

#ifndef DATA_STRUCTURE_EXP_STACK_H
#define DATA_STRUCTURE_EXP_STACK_H

#include "vector.h"
#include "list.h"

template <class T>
class stack: vector<T>{
public:
    stack():vector<T>(){}
    void push(const T& val){
        vector<T>::push_back(val);
    }
    void pop(){
        vector<T>::pop_back();
    }
    size_t size() const{
        return vector<T>::size();
    }
    bool empty() override{
        return vector<T>::empty();
    }
    T& top(){
        return vector<T>::back();
    }
};

template<class T>
class stack_by_list :public list<T>{
public:
	stack_by_list() :list<T>() {}
	void push(const T& val) {
		list<T>::push_back(val);
	}
	void pop() {
		list<T>::pop_back();
	}
	size_t size() const {
		return list<T>::size();
	}
	bool empty() const {
		return !size();
	}
	T& top() {
		return list<T>::back();
	}
};

#endif //DATA_STRUCTURE_EXP_STACK_H
