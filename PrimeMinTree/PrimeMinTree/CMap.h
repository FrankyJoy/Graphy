#ifndef CMAP_H
#define CMAP_H

#include <vector>
#include "Node.h"
#include "Edge.h"
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

	//普利姆算法  参数为指定的第一个点
	void PrimeTree(int nodeIndex);

private:
	//从矩阵中获取权值
	bool getValueFromMatrix(int row, int col, int & val);
	//广度优先便利实现函数
	void breathFirstTraverseImpl(vector<int> preVec);
	//获取最小边
	int getMinEdge(vector<Edge> edgeVec);

private:
	int m_iCapacity;//图中最多可以容纳的顶点数
	int m_iNodeCount;//已经添加的顶点(节点)个数
	Node * m_pNodeArray;// 用来存放顶点数组
	int *m_pMatrix;		//用来存放邻接矩阵

	Edge * m_pEdge;     //用来存储最小路径
};

#endif