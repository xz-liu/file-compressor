//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_GRAPH_H
#define DATA_STRUCTURE_EXP_GRAPH_H

#include "list.h"
#include "vector.h"
#include "queue.h"
#include <numeric>
#include <any>
#include <functional>
template <class T>
struct graph_mat: public vector<vector<T>>{
    explicit graph_mat(int N)
    :vector<vector<T>>(N,vector<T>(N,0)){}
    graph_mat(const std::initializer_list<::vector<T>>& list)
            :vector<vector<T>>(list){}
    using mat=vector<vector<T>>;
    using iterator = typename mat::iterator;
    using const_iterator =typename mat::const_iterator;

    T in_degree(size_t pos)const {
        T val(0);
        for(auto x=this->begin();x!=this->end();x++){
            val+=x->operator[](pos);
        }
        return val;
    }
    T out_degree(size_t pos)const {
        return std::accumulate((*this)[pos].begin(),(*this)[pos].end(),T(0));
    }
    T degree(size_t pos)const {
        return in_degree(pos)+out_degree(pos);
    }
};

template <class T>
struct graph_edge{
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
    vector<graph_edge<Edge>> edges;
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
    const Node&operator[](size_t i)const {
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

    graph_edge<Edge> query_edge(size_t u,size_t v){
        return edges[out[u][v].edge_ref];
    }

    void dfs(size_t u,std::function<void(Node&)> visit,
             bool first=true){
        static ::vector<bool> vis;
        if(first){
            vis.resize(node_vals.size());
            for(auto& x:vis)x= false;
        }
        visit(node_vals[u]);vis[u]=true;
        for(auto x:out[u])if (!vis[x.pos_ref])
                dfs(x.pos_ref,visit, false);
    }

    void bfs(size_t u,std::function<void(Node&)> visit) {
        ::vector<bool> vis(node_vals.size(), false);
        queue<size_t> Q;Q.push(u);
        while (!Q.empty()) {
            size_t front = Q.front();
            Q.pop();
            if (!vis[front]) {
                vis[front] = true;
                visit(node_vals[front]);
                for (auto x:out[front])
                    Q.push(x.pos_ref);
            }
        }
    }
};

const int inf=0x3f3f3f3f;
void dijkstra(const graph_mat<int> &G,size_t v,vector<int> &res) {
    size_t n;
    res.resize(n = G.size());
    ::vector<bool> vis(n, false);
    for (int i = 0; i < n; ++i) res[i] = (i ? inf : 0);
    for (int i = 0; i < n; ++i) {
        int x, m = inf;
        for (int y = 0; y < n; ++y)
            if (!vis[y] && res[y] <= m)m = res[x = y];
        vis[x] = true;
        for (int y = 0; y < n; ++y)
            res[y] = std::min(res[y], res[x] + G[x][y]);
    }
}



#endif //DATA_STRUCTURE_EXP_GRAPH_H
