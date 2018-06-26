#pragma once

#include <vector>
using namespace std;

class CEdge;

class CPath
{
public:
	float m_fPathValue;
	vector<CEdge*> m_path;

	CPath();
	void Clear();
	bool Add(CEdge* pEdge);
	void Print();
	CEdge* GetRandomEdge();
};