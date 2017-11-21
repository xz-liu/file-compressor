//
// Created by joker on 2017/11/21.
//

#ifndef DATA_STRUCTURE_EXP_EXP_4_H
#define DATA_STRUCTURE_EXP_EXP_4_H

#include "graph.h"

void run_exp4_tests(){
    using std::cout;
    using std::endl;
    cout<<"Exp 4 : graph"<<endl;
    graph_mat<int > graph{
            {1,1,0,1,1},
            {1,1,0,0,0},
            {0,1,1,1,1},
            {0,0,0,0,1},
            {1,0,1,0,1}
    };
    cout<<"Graph in matrix"<<endl;
    for(auto x:graph){
        for(auto y:x){cout<<y;}
        cout<<endl;
    }
    cout<<"in degree of each nodes:"<<endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout<<"in["<<i<<"] = "<<graph.in_degree(i)<<endl;
    }

    cout<<"out degree of each nodes:"<<endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout<<"out["<<i<<"] = "<<graph.out_degree(i)<<endl;
    }
    vector<int> res;
    dijkstra(graph,0,res);
    for (int u = 0; u < res.size(); ++u) {
        cout<<"the shortest path from point 0 to point "<<u<<" is " ;
        if(res[u]==inf)cout<<"inf";
        else cout<<res[u];
        cout<<endl;
    }
    cout<<"Graph in list"<<endl;
    graph_list<int,int> graphList(10);
    cout<<"Adding edges"<<endl;
    vector<vector<int>> add={
            {0,9,9},
            {0,1,1},
            {1,2,1},
            {1,3,1},
            {1,4,1},
            {2,5,2},
            {2,6,6},
            {2,7,1},
            {3,4,4},
            {7,8,9},
            {8,9,1}
    };
    for (int i = 0; i < 10; ++i) {
        graphList[i]=i;
    }
    for(auto x:add){
        cout<<"add edge u="<<x[0]<<" v="<<x[1]<<" w="<<x[2]<<endl;
        graphList.add_edge(x[0],x[1],x[2]);
    }
    cout<<"BFS"<<endl;
    graphList.bfs(0,[&](auto a){cout<<a<<" ";});
    cout<<endl<<"DFS"<<endl;
    graphList.dfs(0,[&](auto a){cout<<a<<" ";});
    cout<<endl;

}
#endif //DATA_STRUCTURE_EXP_EXP_4_H
