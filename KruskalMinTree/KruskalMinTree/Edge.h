#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	int m_iNodeIndexA;//一个点索引
	int m_iNodeIndexB;
	int m_iWeightValue;//边的权重
	bool m_bSelected;//是否被标记
	int edgeCount;
public:
	Edge(int indexA = 0, int indexB = 0, int weight = 0);
};

#endif