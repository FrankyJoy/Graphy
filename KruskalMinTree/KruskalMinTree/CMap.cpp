#include "stdafx.h"
#include "CMap.h"
#include <iostream>

using namespace std;

CMap::CMap(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	//edgeCount = 0;
	//Node * m_pNodeArray = new Node[m_iCapacity*m_iCapacity];
	m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity * m_iCapacity];
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
		m_pMatrix[i] = 0;

	m_pEdge = new Edge[m_iCapacity-1];//存储的边数为容量-1
}
CMap::~CMap()
{
	delete[] m_pEdge;
	delete[] m_pNodeArray;
	delete[] m_pMatrix;
}

//	添加节点
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

//	查找对应行列的值
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
	for (; i < edgeVec.size(); i++)
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

void CMap::KruskalTree()
{
	int value = 0;
	int edgeCount = 0;
	vector<vector<int>> nodeSets;//点集合

	vector<Edge> edgeVec;  //	存放边的数组
	//查找所有的边
	for (int i = 0; i < m_iCapacity; i++)
	{	//	查找下三角矩阵，找出相交点并取值
		for (int j = i+1; j < m_iCapacity; j++)
		{
			getValueFromMatrix(i, j, value);
			if (value != 0)
			{
				Edge edge(i, j, value);
				edgeVec.push_back(edge);
			}
		}
	}

	//第一步找到循环终止的条件,边数=顶点数-1
	while (edgeCount < m_iCapacity-1)
	{
		//	2.从边的集合中找到最小边
		int minEdgeIndex = getMinEdge(edgeVec);
		edgeVec[minEdgeIndex].m_bSelected = true;

		//	3.找出最小边连接的点
		int nodeAIndex = edgeVec[minEdgeIndex].m_iNodeIndexA;
		int nodeBIndex = edgeVec[minEdgeIndex].m_iNodeIndexB;

		//	4.找出点所在的点集合
		//从所有集合中都找一遍A点


		bool nodeAIsInSet = false;
		bool nodeBIsInSet = false;

		// 点所在的集合下标，可能为一个集合，也可能为多个集合的下标
		int nodeAInSetLabel = -1;
		int nodeBInSetLabel = -1;
		
		// 查找A点是否在已有的点集中，如果存在返回点集的索引 ，也就是在nodeSet中的位置
		for (int i = 0; i < nodeSets.size(); i++)
		{
			nodeAIsInSet = isInSet(nodeSets[i], nodeAIndex);
			if (nodeAIsInSet)
			{
				nodeAInSetLabel = i;
			}
		}
		// 查找B点是否在已有的点集中，如果存在返回点集的索引 ，也就是在nodeSet中的位置
		for (int i = 0; i < nodeSets.size(); i++)
		{
			nodeBIsInSet = isInSet(nodeSets[i], nodeBIndex);
			if (nodeBIsInSet)
			{
				nodeBInSetLabel = i;
			}
		}

		//5. 根据点所在集合的不同做出不同的处理
		//AB 都不在集合中，都没有找到集合中对应的点
		if (nodeAInSetLabel == -1 && nodeBInSetLabel == -1)
		{
			//如果都不在已有点集的集合中，则将这两个点压入点集
			vector<int> vec;
			vec.push_back(nodeAIndex);
			vec.push_back(nodeBIndex);
			nodeSets.push_back(vec);
		}
		//b在集合中，a没有对应的点集归属
		else if (nodeAInSetLabel == -1 && nodeBInSetLabel != -1)
		{
			// 将A放入B集合中
			nodeSets[nodeBInSetLabel].push_back(nodeAIndex);
		}
		//a在集合中，b没有对应的点集归属
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel == -1)
		{
			//	将B点放入A集合中
			nodeSets[nodeAInSetLabel].push_back(nodeBIndex);
		}
		// 如果都有点集归属，但不属于同一个点集，则将两个点集合并，b所在的点集合合并到a点中
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel != -1 && nodeAInSetLabel != nodeBInSetLabel)
		{
			//将B点移动到A点的集合中
			mergeNodeSet(nodeSets[nodeAInSetLabel], nodeSets[nodeBInSetLabel]);
			// B点所在的点集已经没有意义，队列前移
			for (int k = nodeBInSetLabel; k < (int)nodeSets.size() - 1; k++)
			{
				nodeSets[k] = nodeSets[k + 1];
			}
		}
		//	当前两个集合的值相等,当前两个点在一个集合中，也就是形成了回路
		//  这两个点在已有的集合中存在，并且处于同一个点集合，也就是说他们已经存在集合中，现在他们两个点现在又存在了。
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel != -1 && nodeAInSetLabel == nodeBInSetLabel)
		{
			continue;
		}

		//	将最小边存入m_pEdge中
		m_pEdge[edgeCount] = edgeVec[minEdgeIndex];
		edgeCount++;

		
		//打印选出边
		cout << m_pNodeArray[edgeVec[minEdgeIndex].m_iNodeIndexA].m_cData << "---" << m_pNodeArray[edgeVec[minEdgeIndex].m_iNodeIndexB].m_cData << endl;
		cout << edgeVec[minEdgeIndex].m_iWeightValue << endl;
	}

}
//	查找nodeIndex是否在集合中
bool CMap::isInSet(vector<int> nodeSet, int target)
{
	//	查找集合中是否有索引为target的点
	for (int i = 0; i < nodeSet.size(); i++)
	{
		if (nodeSet[i] == target)
		{
			return true;
		}
	}
	return false;
}
// 经NodeB集合合并到NodeA中
void CMap::mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB)
{
	// 取出B点放入A点的集合
	for (int i = 0; i < nodeSetB.size(); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}
}
