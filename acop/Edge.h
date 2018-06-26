#pragma once

class CNode;

class CEdge
{
private:
	unsigned int m_nPheromone;

public:
	CEdge();

	CNode* m_pStartNode;
	CNode* m_pEndNode;

	float m_fValue;
	unsigned int GetPheromone();
	void IncPheromone();
	void ResetPheromone();
};