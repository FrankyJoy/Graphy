#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	int m_iNodeIndexA;//һ��������
	int m_iNodeIndexB;
	int m_iWeightValue;//�ߵ�Ȩ��
	bool m_bSelected;//�Ƿ񱻱��
	int edgeCount;
public:
	Edge(int indexA = 0, int indexB = 0, int weight = 0);
};

#endif