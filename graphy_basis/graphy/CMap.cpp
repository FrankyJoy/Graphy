#include "stdafx.h"
#include "CMap.h"
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
/*深度优先搜索*/
void CMap::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	//现访问当前传入进来的节点
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	// 用当前节点去查找与其连接的点，看是否存在弧
	// 深度优先搜索比较简单，最初的搜索顺序是根据下标来的
	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex,i,value);
		if (value != 0)//找到弧
		{
			//如果当前点已经被访问过
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;
			}
			else//如果没有访问过
			{
				//调用当前函数进行递归
				depthFirstTraverse(i);
			}
		}
		else	//如果=0表示没有相邻点
		{
			continue;
		}
	}


}
/*广度优先搜索*/
void CMap::breadthFirstTraverse(int nodeIndex)
{
	//首先输出当前节点的值
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	//将当前节点压入curVec容器中
	vector<int> curVec;
	curVec.push_back(nodeIndex);
	
	breathFirstTraverseImpl(curVec);
}

void CMap::breathFirstTraverseImpl(vector<int> preVec)
{
	//传入参数为上一层节点
	//从邻接矩阵取值
	int value = 0;
	vector<int> curVec;

	for (int j = 0; j < (int)preVec.size(); j++)
	{
		//查传入的值与其他值是否有连接
		for (int i = 0; i < m_iCapacity; i++)
		{
			//	循环检查每一个点与上层点之间是否相连
			getValueFromMatrix(preVec[j],i,value);
			if (value != 0)//如果有连接
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[i].m_cData << " ";
					m_pNodeArray[i].m_bIsVisited = true;

					curVec.push_back(i);//放入连接点的索引，从上一层获取点集合求出该层与之相连的点集合
				}
			}

		}

	}
	//判断当前保存的个数是否为0，也就是本层是否存在刚被访问的点
	if (curVec.size() == 0)//本层无点，则下层也不可能存在
	{
		return;
	}
	else   //否则基础递归，直到所有的层都访问完。
	{
		breathFirstTraverseImpl(curVec);
	}
}