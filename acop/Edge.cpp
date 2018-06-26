#include "stdafx.h"

#include "Edge.h"
#include "Node.h"

CEdge::CEdge()
{
	m_nPheromone = 0;
	m_fValue = 0;
}

unsigned int CEdge::GetPheromone()
{
	return m_nPheromone;
}

void CEdge::IncPheromone()
{
	m_pStartNode->Lock();
	m_nPheromone++;
	m_pStartNode->Unlock();
}

void CEdge::ResetPheromone()
{
	m_pStartNode->Lock();
	m_nPheromone = 0;
	m_pStartNode->Unlock();
}