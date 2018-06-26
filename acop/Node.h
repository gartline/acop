#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class CEdge;

class CNode
{
private:
	CRITICAL_SECTION m_cs;
public:
	int m_nNodeNum;
	static int m_nTotalNums;

	CNode();
	~CNode();

	vector<CEdge*> m_edges;

	CEdge* GetNextStep();

	void Lock();
	void Unlock();
};
