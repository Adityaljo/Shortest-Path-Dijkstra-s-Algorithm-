#pragma once
#include<vector>
using namespace std;
class Graph
{
private:
	int size_;
	vector <vector<pair<int, double>>> graph_;
public:
	Graph(int size) :graph_(vector<vector<pair<int, double>>>(size, vector<pair<int, double>>())),size_(size){};
	vector<pair<int, double>> getVector(int index)
	{
		return graph_[index];
	}
	void add(int u, int v, double val) {
		graph_[u].push_back({ v,val });
	}
	int getSize() { return size_; }
};

