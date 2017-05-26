#include "stdafx.h"
#include "CMap.h"
#include "Edge.h"
#include <iostream>
//#include <vector>

CMap::CMap(int capacity)
{
	//传入参数的意思是节点的数量
	m_iCapacity = capacity;
	//记录节点的数量
	m_iNodeCount = 0;
	//m_pNodeArray 为*Node
	m_pNodeArray = new Node[m_iCapacity];
	//行列相同
	m_pMatrix = new int[m_iCapacity *m_iCapacity];
	// memset 函数的功能就是内存的设定，不仅要计算数量的大小,
	// 还要计算每一 个所占内存的大小
	// memset(m_pMatrix, 0, m_iCapacity*m_iCapacity*sizeof(int));
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
	{
		m_pMatrix[i] = 0;
	}

	//存最小生成树上的边，最小生成树边的个数为N-1
	m_pEdge = new Edge[m_iCapacity - 1];

}

CMap::~CMap()
{
	delete[] m_pNodeArray;//节点数组
	delete[] m_pMatrix;//邻接矩阵数组
}
/*添加节点*/
bool CMap::addNode(Node *pNode)
{
	if (m_pNodeArray == NULL)
		return false;
	if (pNode == NULL)
		return false;
	// 顶点的索引m_pNodeArray数组的下标
	// 传入节点及索引
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}
//重置所有节点的isVisit置为false
void CMap::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}
// 向有向图中设置值
bool CMap::setValueMatrixForDirectedGraphy(int row, int col, int val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;
	//row为行，col为列的偏移，可以映射到行和列上来
	m_pMatrix[row*m_iCapacity + col] = val;
	return true;
}

// 针对无向图的图
bool CMap::setValueMatrixForUndirectedGraphy(int row, int col, int val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;
	m_pMatrix[row*m_iCapacity + col] = val;
	//对称位置
	m_pMatrix[col*m_iCapacity + row] = val;
	return true;
}

bool CMap::getValueFromMatrix(int row, int col, int &val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;
	//val 此处为引用
	val = m_pMatrix[row*m_iCapacity + col];
	return true;
}

void CMap::printMatrix()
{
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int k = 0; k < m_iCapacity; k++)
		{
			cout << m_pMatrix[i*m_iCapacity + k] << " ";
		}
		cout << endl;
	}
}

//普利姆生成树
void CMap::PrimeTree(int nodeIndex)
{
	int value = 0; //用于取边
	int edgeCount = 0;
	vector<int> nodeVec; //存储边的索引
	vector<Edge> edgeVec; 

	cout << m_pNodeArray[nodeIndex].m_cData << endl;


	nodeVec.push_back(nodeIndex);//压入第一个点
	m_pNodeArray[nodeIndex].m_bIsVisited = true;//将该点置为已访问
	//最终拿到的边数=当前边数-1
	while (edgeCount < m_iCapacity-1)
	{
		//需要一个临时变量
		int temp = nodeVec.back();//取出最尾部的元素
		//寻找与该节点连接的所有边
		for (int i = 0; i < m_iCapacity; i++)
		{
			getValueFromMatrix(temp, i, value);
			if (value != 0) //点与点之间的连线
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else // 如果没有被访问过
				{
					//不会放重复的边
					Edge edge(temp, i, value);
					edgeVec.push_back(edge);
				}
			}

		}
		//从可选边集合中找出最小的边,传入边的集合，返回最小边的索引
		int edgeIndex = getMinEdge(edgeVec);
		//设定该边被选择
		edgeVec[edgeIndex].m_bSelected = true;
		cout << edgeVec[edgeIndex].m_iNodeIndexA << "---" << edgeVec[edgeIndex].m_iNodeIndexB <<"   ";
		cout << edgeVec[edgeIndex].m_iWeightValue << endl;
		// 将当前边放入最小生成树集合中
		m_pEdge[edgeCount] = edgeVec[edgeIndex];
		edgeCount++;

		//找到与当前最小边链接的点
		int nextNodeIndex = edgeVec[edgeIndex].m_iNodeIndexB;
		
		nodeVec.push_back(nextNodeIndex);
		m_pNodeArray[nextNodeIndex].m_bIsVisited = true;

		cout << m_pNodeArray[nextNodeIndex].m_cData << endl;
	}
}

//获取最小边的权值
int CMap::getMinEdge(vector<Edge> edgeVec)
{
	int minWeight = 0;//最小权值
	int edgeIndex = 0;
	int i = 0;
	
	for (; i < edgeVec.size(); i++)
	{
		//先找到第一条没有被选中的边
		if (!edgeVec[i].m_bSelected)//如果没有被选中
		{
			minWeight = edgeVec[i].m_iWeightValue;
			//拿到最小权值边的索引
			edgeIndex = i;
			break;
		}
	}
	if (minWeight == 0)
	{
		return -1;
	}
	for (; i < edgeVec.size();i++)
	{
		if (edgeVec[i].m_bSelected)
		{
			continue;
		}
		else
		{
			if (minWeight > edgeVec[i].m_iWeightValue)
			{
				minWeight = edgeVec[i].m_iWeightValue;
				edgeIndex = i;
			}
		}
	}
	return edgeIndex;
}