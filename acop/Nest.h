#pragma once

#include <list>
#include <vector>
#include <Windows.h>
using namespace std;

class CPath;
class CAnt;
class CNode;
class CEdge;

class CNest
{
private:
	CNest();
	static CNest* m_inst;
	CRITICAL_SECTION m_cs;
	CPath* m_pBestPath;
	list<CAnt*> m_ants;
	int m_nStartTickCount;
	int m_nBestPathTickCount;

public:
	static CNest& Inst();
	~CNest();
	void Clear();

	CNode* m_pStartNode;
	CNode* m_pDestinationNode;

	float GetBestPathValue();
	void Run();
	bool NewPath(CPath* pPath);
	int AntsAlive();
	void PrintResult();
	CEdge* GetRandomEdgeFromBestPath();
};