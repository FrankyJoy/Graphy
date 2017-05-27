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

	m_pEdge = new Edge[m_iCapacity-1];//�洢�ı���Ϊ����-1
}
CMap::~CMap()
{
	delete[] m_pEdge;
	delete[] m_pNodeArray;
	delete[] m_pMatrix;
}

//	��ӽڵ�
bool CMap::addNode(Node *pNode)
{
	if (m_pNodeArray == NULL)
		return false;
	if (pNode == NULL)
		return false;
	// ���������m_pNodeArray������±�
	// ����ڵ㼰����
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}

//�������нڵ��isVisit��Ϊfalse
void CMap::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}

// �������ͼ��ͼ
bool CMap::setValueMatrixForUndirectedGraphy(int row, int col, int val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;
	m_pMatrix[row*m_iCapacity + col] = val;
	//�Գ�λ��
	m_pMatrix[col*m_iCapacity + row] = val;
	return true;
}

//	���Ҷ�Ӧ���е�ֵ
bool CMap::getValueFromMatrix(int row, int col, int &val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;
	//val �˴�Ϊ����
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

//��ȡ��С�ߵ�Ȩֵ
int CMap::getMinEdge(vector<Edge> edgeVec)
{
	int minWeight = 0;//��СȨֵ
	int edgeIndex = 0;
	int i = 0;

	for (; i < edgeVec.size(); i++)
	{
		//���ҵ���һ��û�б�ѡ�еı�
		if (!edgeVec[i].m_bSelected)//���û�б�ѡ��
		{
			minWeight = edgeVec[i].m_iWeightValue;
			//�õ���СȨֵ�ߵ�����
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
	vector<vector<int>> nodeSets;//�㼯��

	vector<Edge> edgeVec;  //	��űߵ�����
	//�������еı�
	for (int i = 0; i < m_iCapacity; i++)
	{	//	���������Ǿ����ҳ��ཻ�㲢ȡֵ
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

	//��һ���ҵ�ѭ����ֹ������,����=������-1
	while (edgeCount < m_iCapacity-1)
	{
		//	2.�ӱߵļ������ҵ���С��
		int minEdgeIndex = getMinEdge(edgeVec);
		edgeVec[minEdgeIndex].m_bSelected = true;

		//	3.�ҳ���С�����ӵĵ�
		int nodeAIndex = edgeVec[minEdgeIndex].m_iNodeIndexA;
		int nodeBIndex = edgeVec[minEdgeIndex].m_iNodeIndexB;

		//	4.�ҳ������ڵĵ㼯��
		//�����м����ж���һ��A��


		bool nodeAIsInSet = false;
		bool nodeBIsInSet = false;

		// �����ڵļ����±꣬����Ϊһ�����ϣ�Ҳ����Ϊ������ϵ��±�
		int nodeAInSetLabel = -1;
		int nodeBInSetLabel = -1;
		
		// ����A���Ƿ������еĵ㼯�У�������ڷ��ص㼯������ ��Ҳ������nodeSet�е�λ��
		for (int i = 0; i < nodeSets.size(); i++)
		{
			nodeAIsInSet = isInSet(nodeSets[i], nodeAIndex);
			if (nodeAIsInSet)
			{
				nodeAInSetLabel = i;
			}
		}
		// ����B���Ƿ������еĵ㼯�У�������ڷ��ص㼯������ ��Ҳ������nodeSet�е�λ��
		for (int i = 0; i < nodeSets.size(); i++)
		{
			nodeBIsInSet = isInSet(nodeSets[i], nodeBIndex);
			if (nodeBIsInSet)
			{
				nodeBInSetLabel = i;
			}
		}

		//5. ���ݵ����ڼ��ϵĲ�ͬ������ͬ�Ĵ���
		//AB �����ڼ����У���û���ҵ������ж�Ӧ�ĵ�
		if (nodeAInSetLabel == -1 && nodeBInSetLabel == -1)
		{
			//������������е㼯�ļ����У�����������ѹ��㼯
			vector<int> vec;
			vec.push_back(nodeAIndex);
			vec.push_back(nodeBIndex);
			nodeSets.push_back(vec);
		}
		//b�ڼ����У�aû�ж�Ӧ�ĵ㼯����
		else if (nodeAInSetLabel == -1 && nodeBInSetLabel != -1)
		{
			// ��A����B������
			nodeSets[nodeBInSetLabel].push_back(nodeAIndex);
		}
		//a�ڼ����У�bû�ж�Ӧ�ĵ㼯����
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel == -1)
		{
			//	��B�����A������
			nodeSets[nodeAInSetLabel].push_back(nodeBIndex);
		}
		// ������е㼯��������������ͬһ���㼯���������㼯�ϲ���b���ڵĵ㼯�Ϻϲ���a����
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel != -1 && nodeAInSetLabel != nodeBInSetLabel)
		{
			//��B���ƶ���A��ļ�����
			mergeNodeSet(nodeSets[nodeAInSetLabel], nodeSets[nodeBInSetLabel]);
			// B�����ڵĵ㼯�Ѿ�û�����壬����ǰ��
			for (int k = nodeBInSetLabel; k < (int)nodeSets.size() - 1; k++)
			{
				nodeSets[k] = nodeSets[k + 1];
			}
		}
		//	��ǰ�������ϵ�ֵ���,��ǰ��������һ�������У�Ҳ�����γ��˻�·
		//  �������������еļ����д��ڣ����Ҵ���ͬһ���㼯�ϣ�Ҳ����˵�����Ѿ����ڼ����У��������������������ִ����ˡ�
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel != -1 && nodeAInSetLabel == nodeBInSetLabel)
		{
			continue;
		}

		//	����С�ߴ���m_pEdge��
		m_pEdge[edgeCount] = edgeVec[minEdgeIndex];
		edgeCount++;

		
		//��ӡѡ����
		cout << m_pNodeArray[edgeVec[minEdgeIndex].m_iNodeIndexA].m_cData << "---" << m_pNodeArray[edgeVec[minEdgeIndex].m_iNodeIndexB].m_cData << endl;
		cout << edgeVec[minEdgeIndex].m_iWeightValue << endl;
	}

}
//	����nodeIndex�Ƿ��ڼ�����
bool CMap::isInSet(vector<int> nodeSet, int target)
{
	//	���Ҽ������Ƿ�������Ϊtarget�ĵ�
	for (int i = 0; i < nodeSet.size(); i++)
	{
		if (nodeSet[i] == target)
		{
			return true;
		}
	}
	return false;
}
// ��NodeB���Ϻϲ���NodeA��
void CMap::mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB)
{
	// ȡ��B�����A��ļ���
	for (int i = 0; i < nodeSetB.size(); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}
}
