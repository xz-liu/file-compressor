//
// Created by joker on 2017/10/31.
//

#ifndef DATA_STRUCTURE_EXP_LIST_NODE_H
#define DATA_STRUCTURE_EXP_LIST_NODE_H

template<class T>
class list;

template<class T>
class list_iterator;

template<class T>
class const_list_iterator;

template<class T>
class list_node {
    friend class list_iterator<T>;

    friend class const_list_iterator<T>;

    T value;
public:
    list_node *next;
    list_node *prev;//optional
    //O(1)
    static void erase(list_node *node) {
        if (node) {
            if (node->prev)node->prev->next = node->next;
            if (node->next)node->next->prev = node->prev;
            delete node;
        }
    }

    //O(1)
    static void erase(list_node *prev, list_node *node) {
        if (prev) {
            prev->next = node->next;
            if (prev->next)prev->next->prev = prev;
        }
        erase(node);
    }

    static void insert_before(list_node *nxt, list_node *ins) {
        if (nxt) {
            if (nxt->prev)ins->prev = nxt->prev->prev;
            nxt->prev = ins;
        }
        if (ins->prev)ins->prev->next = ins;
        ins->next = nxt;

    }

    static void insert(list_node *prev, list_node *ins) {
        if (prev) {
            if (prev->next)ins->next = prev->next;
            prev->next = ins;
        }
        if (ins->next)ins->next->prev = ins;
        ins->prev = prev;
    }

    static void insert(list_node *prev, const T &val) {
        insert(prev, new list_node(val));
    }

    void insert_before(const T &val) {
        insert_before(this, new list_node(val));
    }

    void insert(const T &val) {
        insert(this, val);
    }

    void erase() {
        erase(this);
    }

    explicit list_node(const T &value,
                       list_node *next = nullptr,
                       list_node *prev = nullptr) :
            value(value), next(next), prev(prev) {}

    T &operator*() {
        return value;
    }
};

template<class T>
class list_iterator {
protected:
    list_node<T> *node;
    list_node<T> *end_prev;

    friend class list<T>;

public:
    explicit list_iterator(list_node<T> *pointer = nullptr,
                           list_node<T> *end_prev = nullptr)
            : node(pointer), end_prev(end_prev) {}

    T *operator->() {
        return &node->value;
    };

    T &operator*() {
        return node->value;
    }

    list_iterator &operator++() {
        node = node->next;
        return *this;
    }

    list_iterator &operator--() {
        node = node ? node->prev : end_prev;
        return *this;
    }

    list_iterator operator++(int) {
        auto ret=*this;
        ++(*this);
        return ret;
    }

    list_iterator operator--(int) {
        auto ret=*this;
        --(*this);
        return ret;
    }

    bool operator==(const list_iterator<T> &iterator) const {
        return node == iterator.node;
    }

    bool operator!=(const list_iterator<T> &iterator) const {
        return node != iterator.node;
    }

    list_iterator &operator=(const list_iterator &rhs)= default;

    list_iterator(const list_iterator &rhs) = default;
};

template<class T>
class const_list_iterator : public list_iterator<T> {
public:
    explicit const_list_iterator(list_node<T> *pointer = nullptr,
                                 list_node<T> *end_prev = nullptr)
            : list_iterator<T>(pointer, end_prev) {}

    const_list_iterator &operator=(const const_list_iterator &rhs)= default;

    const_list_iterator(const const_list_iterator &rhs) = default;

    const T *const operator->() const {
        return &list_iterator<T>::node->value;
    };

    const T &operator*() const {
        return list_iterator<T>::node->value;
    }
};

#endif //DATA_STRUCTURE_EXP_LIST_NODE_H
