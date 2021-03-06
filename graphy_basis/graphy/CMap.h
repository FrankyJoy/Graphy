#ifndef CMAP_H
#define CMAP_H

#include <vector>
#include "Node.h"
using namespace std;

class CMap
{
public:
	CMap(int capacity);
	~CMap();

	bool addNode(Node * pNode);//向图中加入顶点（节点）
	void resetNode();			//重置顶点
	//为有向图设置邻接矩阵
	bool setValueMatrixForDirectedGraphy(int row, int col, int val = 1);
	//为无向图设置邻接矩阵
	bool setValueMatrixForUndirectedGraphy(int row, int col, int val = 1);


	//打印邻接矩阵
	void printMatrix();

	//深度优先遍历
	void depthFirstTraverse(int nodeIndex);
	//广度优先遍历
	void breadthFirstTraverse(int nodeIndex);

private:
	//从矩阵中获取权值
	bool getValueFromMatrix(int row, int col, int & val);
	//广度优先便利实现函数
	void breathFirstTraverseImpl(vector<int> preVec);

private:
	int m_iCapacity;//图中最多可以容纳的顶点数
	int m_iNodeCount;//已经添加的顶点(节点)个数
	Node * m_pNodeArray;// 用来存放顶点数组
	int *m_pMatrix;		//用来存放邻接矩阵
};

#endif