#include "stdafx.h"
#include "Path.h"
#include "Edge.h"
#include "Node.h"
#include <iostream>
#include <Windows.h>

CPath::CPath()
{
	Clear();
}

void CPath::Clear()
{
	m_fPathValue = 0;
	m_path.clear();
}

void CPath::Print()
{
	for (vector<CEdge*>::iterator it = m_path.begin(); it != m_path.end(); it++)
	{
		cout << "[" << (*it)->m_pStartNode->m_nNodeNum << "]->";
	}
	cout << "[" << (m_path.back())->m_pEndNode->m_nNodeNum << "]" << endl;
	cout << "Distance: " << m_fPathValue << endl;
}

bool CPath::Add(CEdge* pEdge)
{
	if (m_path.size() && (m_path.back())->m_pEndNode->m_nNodeNum != pEdge->m_pStartNode->m_nNodeNum)
		return false;

	pEdge->IncPheromone();
	float newPath = 0;
	bool bOpt = false;
	for (vector<CEdge*>::iterator it = m_path.begin(); it != m_path.end(); it++)
	{
		if ((*it)->m_pStartNode == pEdge->m_pEndNode)
		{
			m_path.erase(it, m_path.end());
			bOpt = true;
			break;
		}
		else
		{
			newPath += (*it)->m_fValue;
		}
	}
	if (!bOpt)
	{
		m_path.push_back(pEdge);
		m_fPathValue += pEdge->m_fValue;
	}
	else
	{
		m_fPathValue = newPath;
	}

	return true;
}

CEdge* CPath::GetRandomEdge()
{
	int p = rand() % m_path.size();
	return m_path[p];
}