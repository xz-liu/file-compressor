//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_GRAPH_H
#define DATA_STRUCTURE_EXP_GRAPH_H

#include "list.h"
#include "vector.h"
#include <numeric>

template <class T>
struct graph_mat:public vector<vector<T>>{
    explicit graph_mat(int N)
    :vector<vector<T>>(N,vector<T>(N,0)){}
    int in_degree(size_t pos)const {
        return std::accumulate(begin(),end(),0,[&pos](auto a, auto b){
            return a[pos]+b[pos] ;
        });
    }
    int out_degree(size_t pos)const {
        return std::accumulate((*this)[pos].begin(),(*this)[pos].end(),0);
    }
    int degree(size_t pos)const {
        return in_degree(pos)+out_degree(pos);
    }
};

template <class T>
struct list_edge{
    size_t from;
    size_t to;
    T val;
};

struct graph_node{
    size_t pos_ref;
    size_t edge_ref;
};

template <class Node,class Edge>
struct graph_list{
    vector<list_edge<Edge>> edges;
    vector<vector<graph_node>> out,in;
    vector<Node> node_vals;
    explicit graph_list(size_t N,const Node& x=Node())
            :out(N),in(N),node_vals(N,x){}

    void add_edge(size_t u,size_t v,const Edge& e){
        edges.push_back({u,v,e});
        in[v].push_back({u,edges.size()-1});
        out[u].push_back({v,edges.size()-1});
    }

    void add_node(const Node& v){
        in.push_back(vector<graph_node>());
        out.push_back(vector<graph_node>());
        node_vals.push_back(v);
    }

    vector<graph_node>& out_at(size_t i){
        return out[i];
    }

    vector<graph_node>& in_at(size_t i){
        return in[i];
    }

    Node&operator[](size_t i){
        return node_vals[i];
    }

    int in_degree(size_t pos)const {
        return out[pos].size();
    }
    int out_degree(size_t pos)const {
        return in[pos].size();
    }
    int degree(size_t pos)const {
        return in_degree(pos)+out_degree(pos);
    }

    list_edge<Edge> query_edge(size_t u,size_t v){
        return edges[out[u][v].edge_ref];
    }

};


#endif //DATA_STRUCTURE_EXP_GRAPH_H
