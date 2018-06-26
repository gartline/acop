#include "stdafx.h"
#include "Node.h"
#include "Edge.h"

int CNode::m_nTotalNums = 0;

CNode::CNode()
{
	m_nNodeNum = m_nTotalNums;
	m_nTotalNums++;
	InitializeCriticalSection(&m_cs);
}

CNode::~CNode()
{
	DeleteCriticalSection(&m_cs);
}

CEdge* CNode::GetNextStep()
{
	if (m_edges.size() == 0)
		return NULL;

	CEdge* gotoEdge = NULL;

	EnterCriticalSection(&m_cs);

	vector<int> minPheromoneIds;
	unsigned int minPheromone = (*m_edges.begin())->GetPheromone();

	int id = 0;
	for (vector<CEdge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		if ((*it)->GetPheromone() == minPheromone)
		{
			minPheromoneIds.push_back(id);
		}
		else if ((*it)->GetPheromone() < minPheromone)
		{
			minPheromone = (*it)->GetPheromone();
			minPheromoneIds.clear();
			minPheromoneIds.push_back(id);
		}
		id++;
	}

	int p = rand() % minPheromoneIds.size();
	gotoEdge = m_edges[minPheromoneIds[p]];

	LeaveCriticalSection(&m_cs);
	return gotoEdge;
}

void CNode::Lock()
{
	EnterCriticalSection(&m_cs);
}

void CNode::Unlock()
{
	LeaveCriticalSection(&m_cs);
}