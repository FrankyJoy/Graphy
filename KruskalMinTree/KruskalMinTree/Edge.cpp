#include "stdafx.h"
#include "Edge.h"

Edge::Edge(int a, int b, int w)
{
	m_iNodeIndexA = a;
	m_iNodeIndexB = b;
	m_iWeightValue = w;
	m_bSelected = false;
	//edgeCount = 0;
}

