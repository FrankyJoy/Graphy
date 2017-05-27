// KruskalMinTree.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "CMap.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CMap *pMap = new CMap(6);

	Node *nodeA = new Node('A'); //nodeIndex = 0;
	Node *nodeB = new Node('B'); //nodeIndex = 1;
	Node *nodeC = new Node('C'); //nodeIndex = 2;
	Node *nodeD = new Node('D'); //nodeIndex = 3;
	Node *nodeE = new Node('E'); //nodeIndex = 4;
	Node *nodeF = new Node('F'); //nodeIndex = 5;


	pMap->addNode(nodeA);
	pMap->addNode(nodeB);
	pMap->addNode(nodeC);
	pMap->addNode(nodeD);
	pMap->addNode(nodeE);
	pMap->addNode(nodeF);

	pMap->setValueMatrixForUndirectedGraphy(0, 1, 6);
	pMap->setValueMatrixForUndirectedGraphy(0, 4, 5);
	pMap->setValueMatrixForUndirectedGraphy(0, 5, 1);
	pMap->setValueMatrixForUndirectedGraphy(1, 2, 3);
	pMap->setValueMatrixForUndirectedGraphy(1, 5, 2);
	pMap->setValueMatrixForUndirectedGraphy(2, 5, 8);
	pMap->setValueMatrixForUndirectedGraphy(2, 3, 7);
	pMap->setValueMatrixForUndirectedGraphy(3, 5, 4);
	pMap->setValueMatrixForUndirectedGraphy(3, 4, 2);
	pMap->setValueMatrixForUndirectedGraphy(4, 5, 9);


	cout << "邻接矩阵如下所示 :" << endl;
	pMap->printMatrix();
	cout << endl;

	pMap->KruskalTree();

	delete pMap;
	getchar();
	return 0;
}

