#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	Edge(int nodeIndexA = 0,int nodeIndex = 0, int weightValue = 0);
public:
	int  m_iNodeIndexA;//����һ���������
	int  m_iNodeIndexB;
	int  m_iWeightValue;
	bool m_bSelected;//����Ƿ�ѡ��
};

#endif