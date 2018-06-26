#pragma once

#include <vector>
using namespace std;

class CNode;
class CEdge;

class CGraph
{
public: 
	CGraph(char* path);
	~CGraph();

	int TopsCount();
 
	void Clear();
	void ClearPheromone();
	void Read(char* path);
	void Read2(char* path);
	void Save(char* path);
	void PrintInfo();
	void PopulateNodes(int count);
	void AddEdge(int from, int to, float value = 1);
	void RemoveEdge(int s, int e);
	void FindPath(int from, int to);
	vector<CNode*> m_nodes;
	vector<CEdge*> m_edges;
};