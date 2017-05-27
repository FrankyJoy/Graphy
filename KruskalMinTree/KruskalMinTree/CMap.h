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

	//向图中添加顶点
	bool addNode(Node *pNode);
	void resetNode();

	bool setValueMatrixForUndirectedGraphy(int row, int col, int weight);

	void printMatrix();
	void KruskalTree();

private:
	//	从邻接矩阵中获取值
	bool getValueFromMatrix(int row, int col, int &val);
	int getMinEdge(vector<Edge> edgeVec);
	// 判断顶点是否在点集合中
	bool isInSet(vector<int> nodeSet, int target);
	// 合并两个顶点的集合
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