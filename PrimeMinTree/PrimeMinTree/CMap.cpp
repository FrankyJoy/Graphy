#include "stdafx.h"
#include "CMap.h"
#include "Edge.h"
#include <iostream>
//#include <vector>

CMap::CMap(int capacity)
{
	//�����������˼�ǽڵ������
	m_iCapacity = capacity;
	//��¼�ڵ������
	m_iNodeCount = 0;
	//m_pNodeArray Ϊ*Node
	m_pNodeArray = new Node[m_iCapacity];
	//������ͬ
	m_pMatrix = new int[m_iCapacity *m_iCapacity];
	// memset �����Ĺ��ܾ����ڴ���趨������Ҫ���������Ĵ�С,
	// ��Ҫ����ÿһ ����ռ�ڴ�Ĵ�С
	// memset(m_pMatrix, 0, m_iCapacity*m_iCapacity*sizeof(int));
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
	{
		m_pMatrix[i] = 0;
	}

	//����С�������ϵıߣ���С�������ߵĸ���ΪN-1
	m_pEdge = new Edge[m_iCapacity - 1];

}

CMap::~CMap()
{
	delete[] m_pNodeArray;//�ڵ�����
	delete[] m_pMatrix;//�ڽӾ�������
}
/*��ӽڵ�*/
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
// ������ͼ������ֵ
bool CMap::setValueMatrixForDirectedGraphy(int row, int col, int val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;
	//rowΪ�У�colΪ�е�ƫ�ƣ�����ӳ�䵽�к�������
	m_pMatrix[row*m_iCapacity + col] = val;
	return true;
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

//����ķ������
void CMap::PrimeTree(int nodeIndex)
{
	int value = 0; //����ȡ��
	int edgeCount = 0;
	vector<int> nodeVec; //�洢�ߵ�����
	vector<Edge> edgeVec; 

	cout << m_pNodeArray[nodeIndex].m_cData << endl;


	nodeVec.push_back(nodeIndex);//ѹ���һ����
	m_pNodeArray[nodeIndex].m_bIsVisited = true;//���õ���Ϊ�ѷ���
	//�����õ��ı���=��ǰ����-1
	while (edgeCount < m_iCapacity-1)
	{
		//��Ҫһ����ʱ����
		int temp = nodeVec.back();//ȡ����β����Ԫ��
		//Ѱ����ýڵ����ӵ����б�
		for (int i = 0; i < m_iCapacity; i++)
		{
			getValueFromMatrix(temp, i, value);
			if (value != 0) //�����֮�������
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else // ���û�б����ʹ�
				{
					//������ظ��ı�
					Edge edge(temp, i, value);
					edgeVec.push_back(edge);
				}
			}

		}
		//�ӿ�ѡ�߼������ҳ���С�ı�,����ߵļ��ϣ�������С�ߵ�����
		int edgeIndex = getMinEdge(edgeVec);
		//�趨�ñ߱�ѡ��
		edgeVec[edgeIndex].m_bSelected = true;
		cout << edgeVec[edgeIndex].m_iNodeIndexA << "---" << edgeVec[edgeIndex].m_iNodeIndexB <<"   ";
		cout << edgeVec[edgeIndex].m_iWeightValue << endl;
		// ����ǰ�߷�����С������������
		m_pEdge[edgeCount] = edgeVec[edgeIndex];
		edgeCount++;

		//�ҵ��뵱ǰ��С�����ӵĵ�
		int nextNodeIndex = edgeVec[edgeIndex].m_iNodeIndexB;
		
		nodeVec.push_back(nextNodeIndex);
		m_pNodeArray[nextNodeIndex].m_bIsVisited = true;

		cout << m_pNodeArray[nextNodeIndex].m_cData << endl;
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