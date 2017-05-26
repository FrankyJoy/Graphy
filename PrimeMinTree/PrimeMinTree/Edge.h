#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	Edge(int nodeIndexA = 0,int nodeIndex = 0, int weightValue = 0);
public:
	int  m_iNodeIndexA;//其中一个点的索引
	int  m_iNodeIndexB;
	int  m_iWeightValue;
	bool m_bSelected;//标记是否被选出
};

#endif