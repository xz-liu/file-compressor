//
// Created by joker on 2017/10/31.
//

#ifndef DATA_STRUCTURE_EXP_LIST_H
#define DATA_STRUCTURE_EXP_LIST_H

#include "list_node.h"

template <class T>
class list{
protected:
    list_node<T> *head;
    list_node<T> *tail;
    size_t list_size;
    void next_node(list_node<T>*& node){
        node=node->next;
    }
    void prev_node(list_node<T>*& node){
        node=node->prev;
    }
public:
    using iterator=list_iterator<T>;
    using const_iterator=const_list_iterator<T>;

    size_t size(){
        return list_size;
    }
    bool empty(){
        return !list_size;
    }
    list():head(nullptr),tail(nullptr),list_size(0){}
    list(const list& rhs){(*this)=rhs;}
    list&operator=(const list& rhs){
        clear();
        for(auto &x:rhs){
            push_back(x);
        }
        return *this;
    }
    virtual ~list(){
        clear();
    }
    void clear(){
        list_size=0;
        while (head&&head!=tail){
            auto tmp=head;
            next_node(head);
            list_node<T>::erase(tmp);
        }
    }
    void push_back(const T& value){
        if(tail){
            list_node<T>::insert(tail,
                         new list_node<T>(value, nullptr,tail));
            next_node(tail);
        } else {
            if (head) {
                list_node<T>::insert(head,
                     tail= new list_node<T>(value, nullptr,head));
            } else {
                head = new list_node<T>(value);
            }
        }
        list_size++;
    }
    void push_front(const T& value){
        if(head){
            list_node<T>::insert_before(head,
                                 new list_node<T>(value,head));
            prev_node(head);
        } else {
            head = new list_node<T>(value);
        }
        list_size++;
    }
    void pop_back(){
        if(tail){
            list_node<T> * tmp=tail;
            prev_node(tail);
            list_node<T>::erase(tail,tmp);
            list_size--;
        } else if(head){
            list_node<T>::erase(head);
            head=tail= nullptr;
            list_size--;
        }
    }

    void pop_front(){
        if (head){
            list_node<T> * tmp=head;
            next_node(head);
            list_node<T>::erase(tmp);
            list_size--;
        }
    }

    iterator begin(){
        return iterator(head);
    }
    iterator end(){
        return iterator(nullptr);
    }

    const_iterator begin()const {
        return const_iterator(head);
    }
    const_iterator end()const{
        return const_iterator(nullptr);
    }
    const_iterator cbegin()const {
        return const_iterator(head);
    }
    const_iterator cend()const{
        return const_iterator(nullptr);
    }

    void insert(list_iterator<T> pos, const T& val){
        list_node<T>::insert(pos.node,val);
    }
    void erase(list_iterator<T> pos){
        list_node<T>::erase(pos.node->prev,pos.node);
    }
    list_iterator<T> find(const T& val){
        if (empty())return end();
        for(list_iterator<T> iter=begin();iter!=end();iter++){
            if (*iter==val)return iter;
        }
        return end();
    }
    T&operator[](size_t pos){
        auto b=begin();
        for(;pos--;b++);
        return *b;
    }
};

#endif //DATA_STRUCTURE_EXP_LIST_H
