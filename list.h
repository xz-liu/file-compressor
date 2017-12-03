//
// Created by joker on 2017/10/31.
//

#ifndef DATA_STRUCTURE_EXP_LIST_H
#define DATA_STRUCTURE_EXP_LIST_H

#include "list_node.h"
#include <initializer_list>

template<class T>
class list {
protected:
    list_node<T> *head;
    list_node<T> *tail;
    size_t list_size;

    void next_node(list_node<T> *&node) {
        node = node->next;
    }

    void prev_node(list_node<T> *&node) {
        node = node->prev;
    }

public:
    using iterator=list_iterator<T>;
    using const_iterator=const_list_iterator<T>;

    size_t size() const {
        return list_size;
    }

    bool empty() const {
        return !list_size;
    }

    list() : head(nullptr), tail(nullptr), list_size(0) {}

    list(const list &rhs) : list() {
        for (const auto &x:rhs) {
            push_back(x);
        }
    }

    list(std::initializer_list<T> init_list) : list() {
        for (auto x:init_list) {
            push_back(x);
        }
    }

    list &operator=(const list &rhs) {
        clear();
        for (const auto &x:rhs) {
            push_back(x);
        }
        return *this;
    }

    virtual ~list() {
        clear();
    }

    void clear() {
        while (head && head != tail && list_size--) {
            auto tmp = head;
            next_node(head);
            list_node<T>::erase(tmp);
        }
    }

    void push_back(const T &value) {
        if (tail) {
            list_node<T>::insert(tail,
                 new list_node<T>(value, nullptr, tail));
            next_node(tail);
        } else {
            if (head) {
                list_node<T>::insert(head,
                 tail = new list_node<T>(value, nullptr, head));
            } else {
                head = new list_node<T>(value);
            }
        }
        list_size++;
    }

    template <class ...Args>
    void emplace(Args&& ... args) {
        if (tail) {
            list_node<T>::insert(tail, new list_node<T>(args..., nullptr, tail));
            next_node(tail);
        } else if (head)
            list_node<T>::insert(head, tail = new list_node<T>(args..., nullptr, head));
        else head = new list_node<T>(args...);
        list_size++;
    }

    void push_front(const T &value) {
        if (head) {
            list_node<T>::insert_before(head,
                new list_node<T>(value, head));
            prev_node(head);
        } else {
            head = new list_node<T>(value);
        }
        list_size++;
    }

    void pop_back() {
        if (tail) {
            list_node<T> *tmp = tail;
            prev_node(tail);
            list_node<T>::erase(tail, tmp);
            list_size--;
        } else if (head) {
            list_node<T>::erase(head);
            head = tail = nullptr;
            list_size--;
        }
    }

    void pop_front() {
        if (head) {
            if(tail==head)tail= nullptr;
            list_node<T> *tmp = head;
            next_node(head);
            list_node<T>::erase(tmp);
            list_size--;
        }
    }

    T& back(){
        return **tail;
    }

    T& front(){
        return **head;
    }

    iterator begin() {
        return iterator(head, tail);
    }

    iterator end() {
        return iterator(nullptr, tail);
    }

    const_iterator begin() const {
        return const_iterator(head, tail);
    }

    const_iterator end() const {
        return const_iterator(nullptr, tail);
    }

    const_iterator cbegin() const {
        return const_iterator(head, tail);
    }

    const_iterator cend() const {
        return const_iterator(nullptr, tail);
    }

    void insert(iterator pos, const T &val) {
        list_node<T>::insert(pos.node, val);
        list_size++;
    }

    void erase(iterator pos) {
        list_node<T>::erase(pos.node->prev, pos.node);
        list_size--;
    }

    iterator find(const T &val) {
        for (iterator iter = begin(); iter != end(); iter++) {
            if (*iter == val)return iter;
        }
        return end();
    }

    T &operator[](size_t pos) {
        auto b = begin();
        for (; pos--; b++);
        return *b;
    }
};

#endif //DATA_STRUCTURE_EXP_LIST_H
