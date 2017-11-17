//
// Created by joker on 2017/11/7.
//

#ifndef DATA_STRUCTURE_EXP_BINTREE_NODE_H
#define DATA_STRUCTURE_EXP_BINTREE_NODE_H

#include <functional>
#include <cstdlib>
#include <queue>
#include "queue.h"

template <class T>
class bin_tree;

template <class T>
struct bintree_node {
    using bnode_ptr=bintree_node *;
    using const_bnode_ptr=const bintree_node *;
    using visit_func=std::function<void(T &)> ;
    using const_visit_func=std::function<void(const T &)> ;
    T val;
    bintree_node *parent, *lc, *rc;
    int node_height;
    int npl;
    static int stature(bnode_ptr ptr) {
        return ptr ? ptr->node_height : -1;
    }

    bintree_node()
            : parent(nullptr), lc(nullptr), rc(nullptr),
              node_height(0), npl(1){}

    explicit bintree_node(const T &val, bnode_ptr parent = nullptr,
                 bnode_ptr lchild = nullptr, bnode_ptr rchild = nullptr,
                 int height = 0, int null_path_length = 1)
            : val(val), parent(parent), lc(lchild), rc(rchild), node_height(height),
              npl(null_path_length) {}

    static void move_to_lc(bnode_ptr &ptr) {
        ptr = ptr->lc;
    }

    static void move_to_rc(bnode_ptr &ptr) {
        ptr = ptr->rc;
    }

    static void move_to_parent(bnode_ptr &ptr) {
        ptr = ptr->parent;
    }

    bool has_parent() const {
        return (bool) parent;
    }

    bool is_root()const {
        return !has_parent();
    }

    bool is_lchild() const{
        return !is_root() && (this == parent->lc);
    }

    bool is_rchild() const{
        return !is_root() && (this == parent->rc);
    }

    bool has_lchild() const{
        return (bool) lc;
    }

    bool has_rchild() const{
        return (bool) rc;
    }

    bool has_child() const{
        return has_lchild() || has_rchild();
    }

    bool has_all_children() const{
        return has_rchild() && has_rchild();
    }

    bool is_leaf() const{
        return !has_child();
    }

    bnode_ptr sibling() {
        return is_lchild() ? parent->rc : parent->lc;
    }

    bnode_ptr uncle() {
        return parent->is_lchild() ?
               parent->parent->rc :
               parent->parent->lc;
    }

    void set_parent_ref(bnode_ptr ptr){
        if (is_root())return;
        if(is_lchild())parent->lc=ptr;
        else parent->rc=ptr;
    }

    int size() {
        int size_now = 1;
        if (lc)size_now += lc->size();
        if (rc)size_now += rc->size();
        return size_now;
    }

    bnode_ptr next() {
        bnode_ptr s = this;
        if (rc) {
            s = rc;
            while (s->has_lchild())move_to_lc(s);
        } else {
            while (s->is_rchild())move_to_parent(s);
            move_to_parent(s);
        }
        return s;
    }
    const_bnode_ptr next()const{
        return (const_cast<bnode_ptr >(this))->next();
    }

    bnode_ptr insert_as_lchild(T const &val) {
        return lc = new bintree_node(val, this);
    }

    bnode_ptr insert_as_rchild(T const &val) {
        return rc = new bintree_node(val, this);
    }

    void trav_in_order(visit_func visit) {
        if (!this)return;
        lc->trav_in_order(visit);
        visit(val);
        rc->trav_in_order(visit);
    }

    void trav_in_order(const_visit_func visit) const {
        if (!this)return;
        lc->trav_in_order(visit);
        visit(val);
        rc->trav_in_order(visit);
    }

    void trav_pre_order(visit_func visit) {
        if (!this)return;
        visit(val);
        lc->trav_pre_order(visit);
        rc->trav_pre_order(visit);
    }

    void trav_pre_order(const_visit_func visit) const {
        if (!this)return;
        visit(val);
        lc->trav_pre_order(visit);
        rc->trav_pre_order(visit);
    }

    void trav_post_order(visit_func visit) {
        if (!this)return;
        lc->trav_post_order(visit);
        rc->trav_post_order(visit);
        visit(val);
    }

    void trav_post_order(const_visit_func visit) const {
        if (!this)return;
        lc->trav_post_order(visit);
        rc->trav_post_order(visit);
        visit(val);
    }

    void trav_level(visit_func visit){
        std::queue<bnode_ptr> Q;
        using namespace std;
        Q.push(this);
        while (!Q.empty()){
            bnode_ptr x=Q.front();
            Q.pop();visit(x->val);
            if(x->has_lchild()){
                Q.push(x->lc);
            }
            if(x->has_rchild()){
                Q.push(x->rc);
            }
        }
    }

    void trav_level(const_visit_func visit)const{
        queue<const_bnode_ptr> Q;
        Q.push(this);
        while (!Q.empty()){
            const_bnode_ptr x=Q.front();
            Q.pop();visit(x->val);
            if(x->has_lchild())Q.push(x->lc);
            if(x->has_rchild())Q.push(x->rc);
        }
    }

    bool operator<(bintree_node const &bn) const {
        return val < bn.val;
    }

    bool operator==(bintree_node const &bn) const {
        return val == bn.val;
    }
};

template <class T>
class bintree_iterator{
protected:
    using bnode_ptr= typename
    bintree_node<T>::bnode_ptr;
    bnode_ptr node;
    friend class bin_tree<T>;
public:
    bintree_iterator(bnode_ptr node= nullptr){
        this->node= node;
    }

     bintree_iterator&operator++(){
        node=node->next();
        return *this;
    }

     bintree_iterator operator++(int){
        auto ret=*this;
        (*this)++;
        return ret;
    }

    T &operator*(){
        return node->val;
    }
    T*operator->(){
        return &node->val;
    }

    bintree_iterator lchild(){
        return (node->lc);
    }
    bintree_iterator rchild(){
        return (node->rc);
    }
    bintree_iterator parent(){
        return (node->parent);
    }
    bintree_iterator create_lc(const T& v){
        if(node->has_lchild())return nullptr;
        return node->insert_as_lchild(v);
    }
    bintree_iterator create_rc(const T& v){
        if(node->has_rchild())return nullptr;
        return node->insert_as_rchild(v);
    }
    bool operator==(bintree_iterator it)const {
        return node==it.node;
    }
    bool  operator!=(bintree_iterator it)const {
        return node!=it.node;
    }
};

template <class T>
class const_bintree_iterator {
    using const_bnode_ptr= typename
    bintree_node<T>::const_bnode_ptr;
    const_bnode_ptr node;
    friend class bin_tree<T>;
public:
    const_bintree_iterator(const_bnode_ptr node= nullptr){
        this->node= node;
    }

    const_bintree_iterator &operator++() {
        node = node->next();
        return *this;
    }

    const_bintree_iterator operator++(int) {
        auto ret = *this;
        (*this)++;
        return ret;
    }

    const T& operator*  () const{
        return node->val;
    }

    T const * operator->() const{
        return &node->val;
    }
    const_bintree_iterator lchild()const {
        return (node->lc);
    }
    const_bintree_iterator rchild()const {
        return (node->rc);
    }
    const_bintree_iterator parent()const{
        return (node->parent);
    }
    bool operator==(const_bintree_iterator it)const {
        return node==it.node;
    }
    bool  operator!=(const_bintree_iterator it)const {
        return node!=it.node;
    }
};

#endif //DATA_STRUCTURE_EXP_BINTREE_NODE_H
