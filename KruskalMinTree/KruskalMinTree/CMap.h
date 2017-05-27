#ifndef CMAP_H
#define CMAP_H

#include "Node.h"
#include "Edge.h"
#include <vector>

using namespace std;

class CMap
{
private:
public:
	CMap(int Capacity);
	~CMap();

	//��ͼ����Ӷ���
	bool addNode(Node *pNode);
	void resetNode();

	bool setValueMatrixForUndirectedGraphy(int row, int col, int weight);

	void printMatrix();
	void KruskalTree();

private:
	//	���ڽӾ����л�ȡֵ
	bool getValueFromMatrix(int row, int col, int &val);
	int getMinEdge(vector<Edge> edgeVec);
	// �ж϶����Ƿ��ڵ㼯����
	bool isInSet(vector<int> nodeSet, int target);
	// �ϲ���������ļ���
	void mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB);

private:
	int m_iCapacity;
	int m_iNodeCount;
	//int edgeCount;
	Node * m_pNodeArray;
	int * m_pMatrix;

	Edge * m_pEdge;
};


#endif