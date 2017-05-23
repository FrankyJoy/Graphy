#include "stdafx.h"
#include "CMap.h"
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
/*�����������*/
void CMap::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	//�ַ��ʵ�ǰ��������Ľڵ�
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	// �õ�ǰ�ڵ�ȥ�����������ӵĵ㣬���Ƿ���ڻ�
	// ������������Ƚϼ򵥣����������˳���Ǹ����±�����
	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex,i,value);
		if (value != 0)//�ҵ���
		{
			//�����ǰ���Ѿ������ʹ�
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;
			}
			else//���û�з��ʹ�
			{
				//���õ�ǰ�������еݹ�
				depthFirstTraverse(i);
			}
		}
		else	//���=0��ʾû�����ڵ�
		{
			continue;
		}
	}


}
/*�����������*/
void CMap::breadthFirstTraverse(int nodeIndex)
{
	//���������ǰ�ڵ��ֵ
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	//����ǰ�ڵ�ѹ��curVec������
	vector<int> curVec;
	curVec.push_back(nodeIndex);
	
	breathFirstTraverseImpl(curVec);
}

void CMap::breathFirstTraverseImpl(vector<int> preVec)
{
	//�������Ϊ��һ��ڵ�
	//���ڽӾ���ȡֵ
	int value = 0;
	vector<int> curVec;

	for (int j = 0; j < (int)preVec.size(); j++)
	{
		//�鴫���ֵ������ֵ�Ƿ�������
		for (int i = 0; i < m_iCapacity; i++)
		{
			//	ѭ�����ÿһ�������ϲ��֮���Ƿ�����
			getValueFromMatrix(preVec[j],i,value);
			if (value != 0)//���������
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[i].m_cData << " ";
					m_pNodeArray[i].m_bIsVisited = true;

					curVec.push_back(i);//�������ӵ������������һ���ȡ�㼯������ò���֮�����ĵ㼯��
				}
			}

		}

	}
	//�жϵ�ǰ����ĸ����Ƿ�Ϊ0��Ҳ���Ǳ����Ƿ���ڸձ����ʵĵ�
	if (curVec.size() == 0)//�����޵㣬���²�Ҳ�����ܴ���
	{
		return;
	}
	else   //��������ݹ飬ֱ�����еĲ㶼�����ꡣ
	{
		breathFirstTraverseImpl(curVec);
	}
}