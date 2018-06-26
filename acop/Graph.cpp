#include "stdafx.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Nest.h"
#include <fstream>
#include <iostream>
#include <windows.h>

CGraph::CGraph(char* path)
{
	Clear();
	Read2(path);
}

CGraph::~CGraph()
{
	Clear();
}

int CGraph::TopsCount()
{
	return (int)m_nodes.size();
}

void CGraph::Clear()
{
	//clear signs
	for (vector<CEdge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		delete *it;
	}

	m_edges.clear();

	//clear tops
	for (vector<CNode*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		delete *it;
	}

	m_nodes.clear();
	CNode::m_nTotalNums = 0;
}

void CGraph::ClearPheromone()
{
	for (vector<CEdge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		(*it)->ResetPheromone();
	}
	srand(GetTickCount());
}

void CGraph::Read(char* path)
{
	ifstream file(path);
	if (!file.is_open())
		return;

	int count = 0;
	file >> count;

	for (int i = 0; i < count; i++)
	{
		CNode* newTop = new CNode();
		m_nodes.push_back(newTop);
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			float v;
			file >> v;
			if (v != 0)
			{
				CEdge* ns = new CEdge();
				ns->m_pStartNode = m_nodes[i];
				ns->m_pEndNode = m_nodes[j];
				ns->m_fValue = v;

				m_edges.push_back(ns);
				m_nodes[i]->m_edges.push_back(ns);
			}
		}
	}

}

void CGraph::Read2(char* path)
{
	cout << "Reading file: ";

	ifstream file(path);
	if (!file.is_open())
		return;

	int count = 0;
	file >> count;

	PopulateNodes(count);

	int edges = 0;
	file >> edges;
	for (int i = 0; i < edges; i++)
	{
		int s;
		int e;
		file >> s;
		file >> e;
		if (s >= m_nodes.size() || e >= m_nodes.size())
			continue;
		
		AddEdge(s, e);
		AddEdge(e, s);

		if (100 * i % edges == 0)
		{
			cout << '\r';
			cout << "Reading file: " << 100 * i / edges << "%";
			//cout << ".";
		}
	}
	cout << '\r';
	cout << "Reading file: 100%" << endl;
}

void CGraph::Save(char* path)
{
	ofstream file(path);

	file << m_nodes.size() << endl;
	file << m_edges.size() << endl;

	for (vector<CEdge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		file << (*it)->m_pStartNode->m_nNodeNum << " " << (*it)->m_pEndNode->m_nNodeNum << endl;
	}

	file.close();
}

void CGraph::PrintInfo()
{
	cout << endl << "...!GRAPH INFO!..." << endl;
	cout << ".Nodes Count: " << m_nodes.size() << endl;
	cout << ".Edges Count: " << m_edges.size() << endl;
	cout << ".................." << endl;
}

CEdge* RemoveEdgeFromList(vector<CEdge*>& list, int s, int e)
{
	for (vector<CEdge*>::iterator it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->m_pStartNode->m_nNodeNum == s && (*it)->m_pEndNode->m_nNodeNum == e)
		{
			CEdge* pToRemove = *it;
			list.erase(it);

			return pToRemove;
		}
	}
	return NULL;
}

bool FindEdgeInList(vector<CEdge*>& list, int s, int e)
{
	bool bFound = false;
	for (vector<CEdge*>::iterator it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->m_pStartNode->m_nNodeNum == s && (*it)->m_pEndNode->m_nNodeNum == e)
		{
			bFound = true;
		}
	}

	return bFound;
}

void CGraph::PopulateNodes(int count)
{
	for (int i = 0; i < count; i++)
	{
		CNode* newTop = new CNode();
		m_nodes.push_back(newTop);
	}
}

void CGraph::AddEdge(int from, int to, float value)
{
	if (!FindEdgeInList(m_edges, from, to) && !FindEdgeInList(m_nodes[from]->m_edges, from, to))
	{
		CEdge* newEdge = new CEdge();
		newEdge->m_pStartNode = m_nodes[from];
		newEdge->m_pEndNode = m_nodes[to];
		newEdge->m_fValue = value;

		m_edges.push_back(newEdge);
		m_nodes[from]->m_edges.push_back(newEdge);
	}
}

void CGraph::RemoveEdge(int s, int e)
{
	CEdge* pToRemove = RemoveEdgeFromList(m_edges, s, e);

	RemoveEdgeFromList(m_nodes[s]->m_edges, s, e);
	RemoveEdgeFromList(m_nodes[e]->m_edges, e, s);

	delete pToRemove;
}

void CGraph::FindPath(int from, int to)
{
	CNest::Inst().m_pStartNode = m_nodes[from];
	CNest::Inst().m_pDestinationNode = m_nodes[to];

	CNest::Inst().Run();
	while (true)
	{
		if (CNest::Inst().AntsAlive() == 0)
			break;

		Sleep(100);
	}

	CNest::Inst().PrintResult();
}