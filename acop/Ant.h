#pragma once

#include <list>
using namespace std;

class CNode;
class CPath;

class CAnt
{
public:
	CAnt();
	~CAnt();

	bool m_bAlive;

	CNode* m_pCurrentNode;

	void Run();
	void Step();
	void StartOver();

	int m_nSteps;
	CPath* m_pPath;
};