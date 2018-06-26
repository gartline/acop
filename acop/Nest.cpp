#include "stdafx.h"
#include "Nest.h"
#include "Ant.h"
#include "Path.h"
#include "config.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>

CNest* CNest::m_inst = NULL;

CNest::CNest()
{
	m_pBestPath = NULL;
	InitializeCriticalSection(&m_cs);
}

CNest::~CNest()
{
	Clear();
	DeleteCriticalSection(&m_cs);
}

CNest& CNest::Inst()
{
	if (m_inst == NULL)
	{
		m_inst = new CNest();
	}

	return *m_inst;
}

void CNest::Clear()
{
	if (m_pBestPath)
		delete m_pBestPath;

	m_pBestPath = NULL;

	for (list<CAnt*>::iterator it = m_ants.begin(); it != m_ants.end(); it++)
	{
		delete (*it);
	}
	m_ants.clear();
}

void CNest::Run()
{
	Clear();

	for (int i = 0; i < ANTS_IN_NEST; i++)
	{
		CAnt* ant = new CAnt();
		ant->m_pCurrentNode = m_pStartNode;
		m_ants.push_back(ant);
	}

	m_nStartTickCount = GetTickCount();
	for (list<CAnt*>::iterator it = m_ants.begin(); it != m_ants.end(); it++)
	{
		(*it)->Run();
	}
}

bool CNest::NewPath(CPath* pPath)
{
	EnterCriticalSection(&m_cs);

	if (m_pBestPath == NULL)
	{
		m_pBestPath = pPath;
		m_nBestPathTickCount = GetTickCount(); 
		LeaveCriticalSection(&m_cs);
		return true;
	}

	if (pPath->m_fPathValue < m_pBestPath->m_fPathValue)
	{
		delete m_pBestPath;
		m_pBestPath = pPath;
		m_nBestPathTickCount = GetTickCount();
		LeaveCriticalSection(&m_cs);
		return true;
	}
	LeaveCriticalSection(&m_cs);
	return false;
}

float CNest::GetBestPathValue()
{
	float res = -1;

	EnterCriticalSection(&m_cs);
	if (m_pBestPath)
		res = m_pBestPath->m_fPathValue;
	LeaveCriticalSection(&m_cs);

	return res;
}

int CNest::AntsAlive()
{
	int count = 0;
	for (list<CAnt*>::iterator it = m_ants.begin(); it != m_ants.end(); it++)
	{
		if ((*it)->m_bAlive)
			count++;
	}

	return count;
}

void CNest::PrintResult()
{
	int resTC = GetTickCount();

	cout << endl << "===<<< RESULT FOR [" << m_pStartNode->m_nNodeNum << "]->[" << m_pDestinationNode->m_nNodeNum << "] >>>===" << endl;
	if (m_pBestPath == NULL)
	{
		cout << "No Path Found." << endl;
		cout << "Time: " << resTC - m_nStartTickCount << endl;
	}
	else
	{
		m_pBestPath->Print();
		cout << "Time: " << m_nBestPathTickCount - m_nStartTickCount << " of " << resTC - m_nStartTickCount << endl;
	}
	cout << "====================================" << endl;
}

CEdge* CNest::GetRandomEdgeFromBestPath()
{
	if(m_pBestPath)
		return m_pBestPath->GetRandomEdge();

	return NULL;
}