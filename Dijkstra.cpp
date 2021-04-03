// Dijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Graph.h"
#include<vector>
#include<algorithm>
using namespace std;

class PQ {
private:
    vector<pair<double, int>> pq_;
    vector<double>distance_;
    int size_;
public:
    PQ(int size) :size_(size), distance_(vector<double>(size, 999999999)) {};
    void add(double val, int node) {
        auto indx = find_if(begin(pq_), end(pq_), [&](auto ele) {return ele.second == node; });
        if (indx!=end(pq_)){
            indx->first = val;
            make_heap(begin(pq_), end(pq_), [](auto element1, auto element2) {return(element1.first > element2.first); });
        }
        else{
        pq_.push_back({ val,node });
        push_heap(begin(pq_), end(pq_), [](auto element1, auto element2) {return(element1.first > element2.first); });
        }
        distance_[node] = val;
    }
    void delete_min(){
        pop_heap(begin(pq_), end(pq_), [](auto element1, auto element2) {return(element1.first > element2.first); });
        pq_.pop_back();
    }
    double getDist(int node) { return distance_[node]; }
    int getMinID() { return pq_.front().second; }
    int getMinDist() { return pq_.front().first; }
};


int main()
{
    int num = 5;
    Graph G(num);
    G.add(0, 1, 10.0);
    G.add(0, 2, 5.0);
    G.add(1, 3, 1.0);
    G.add(1, 2, 2.0);
    G.add(2, 1, 3.0);
    G.add(2, 4, 2.0);
    G.add(4, 0, 7.0);
    G.add(2, 3, 9.0);
    G.add(3, 4, 4.0);
    G.add(4, 3, 6.0);

    int u = 0, v = 3;

    /*
    1. S=empty;=>used(n,false) distance=0
    2. preced(n,-1)
    3. S={u}=> actual node=u used[u]=true;
    4. loop
    5. relax edges
    6. extract min and add to set, preced[v]=u; delete from priority queue    
    */

    double distance = 0.0;
    vector<int> preced(num, -1);
    vector<bool>used(num, false);
    PQ pq(num);
    int actualNode = u;
    used[actualNode] = true;
    for (int i = 0; i < num; i++){
        G.getVector(actualNode);
        auto vec = G.getVector(actualNode);
        for (int j = 0; j < vec.size(); j++) {
            if (!used[vec[j].first]) {
                if ((distance + vec[j].second) < pq.getDist(vec[j].first)){
                    pq.add((distance + vec[j].second), vec[j].first);
                    preced[vec[j].first] = actualNode;
                }
            }
        }
        actualNode = pq.getMinID();
        distance = pq.getMinDist();
        if(actualNode==v)
        {
            cout << "Min distance from u= " << u << "to v =" << v <<"is "<< distance<< endl;
            break;
        }
        pq.delete_min();
        used[actualNode] = true;
    }
    vector<int>path;
    int node = v;
    while (node != u) {
        path.push_back(node);
        node = preced[node];
    }
    reverse(begin(path), end(path));
    
    for_each(begin(path), end(path), [](int node) {cout << node << endl; });


}

