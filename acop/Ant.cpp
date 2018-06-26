#include "stdafx.h"
#include <iostream>
#include "Ant.h"
#include "Path.h"
#include "Node.h"
#include "Edge.h"
#include "config.h"
#include "Nest.h"

CAnt::CAnt()
{
	m_pPath = new CPath();
	m_bAlive = true;
}

CAnt::~CAnt()
{
	if(m_pPath)
		delete m_pPath;
}

void CAnt::Step()
{
	CEdge* gotoEdge = m_pCurrentNode->GetNextStep();

	if (gotoEdge == NULL)
	{
		//No path from Node
		StartOver();
	}
	else
	{
		m_pPath->Add(gotoEdge);
		m_nSteps++;
		m_pCurrentNode = gotoEdge->m_pEndNode;
	}

	if (m_nSteps > ANT_LIFE_STEPS)
		m_bAlive = false;
}

void CAnt::StartOver()
{
	m_pPath->Clear();
	m_pCurrentNode = CNest::Inst().m_pStartNode;
}

DWORD WINAPI AntThread(LPVOID lpParam)
{
	CAnt* pAnt = (CAnt*)lpParam;

	while (true)
	{
		while (pAnt->m_pCurrentNode != CNest::Inst().m_pDestinationNode)
		{
			pAnt->Step();

			if (!pAnt->m_bAlive)
				return 0;

			float fBestPathValue = CNest::Inst().GetBestPathValue();
			if (fBestPathValue != -1 && pAnt->m_pPath->m_fPathValue > fBestPathValue)
			{
				pAnt->StartOver();
			}
		}

		bool bAccepted = CNest::Inst().NewPath(pAnt->m_pPath);

		if (bAccepted)
			pAnt->m_pPath = new CPath();

		pAnt->StartOver();
	}
	return 0;
}

void CAnt::Run()
{
	HANDLE ThreadHandle = 0;

	ThreadHandle = CreateThread(NULL, 0, AntThread, this, 0, NULL);
}

