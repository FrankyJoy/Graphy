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

	bool addNode(Node * pNode);//��ͼ�м��붥�㣨�ڵ㣩
	void resetNode();			//���ö���
	//Ϊ����ͼ�����ڽӾ���
	bool setValueMatrixForDirectedGraphy(int row, int col, int val = 1);
	//Ϊ����ͼ�����ڽӾ���
	bool setValueMatrixForUndirectedGraphy(int row, int col, int val = 1);


	//��ӡ�ڽӾ���
	void printMatrix();

	//����ķ�㷨  ����Ϊָ���ĵ�һ����
	void PrimeTree(int nodeIndex);

private:
	//�Ӿ����л�ȡȨֵ
	bool getValueFromMatrix(int row, int col, int & val);
	//������ȱ���ʵ�ֺ���
	void breathFirstTraverseImpl(vector<int> preVec);
	//��ȡ��С��
	int getMinEdge(vector<Edge> edgeVec);

private:
	int m_iCapacity;//ͼ�����������ɵĶ�����
	int m_iNodeCount;//�Ѿ���ӵĶ���(�ڵ�)����
	Node * m_pNodeArray;// ������Ŷ�������
	int *m_pMatrix;		//��������ڽӾ���

	Edge * m_pEdge;     //�����洢��С·��
};

#endif