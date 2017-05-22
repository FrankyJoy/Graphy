// graphy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CMap.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CMap *pMap = new CMap(8);
	
	Node *nodeA = new Node('A'); //nodeIndex = 0;
	Node *nodeB = new Node('B'); //nodeIndex = 1;
	Node *nodeC = new Node('C'); //nodeIndex = 2;
	Node *nodeD = new Node('D'); //nodeIndex = 3;
	Node *nodeE = new Node('E'); //nodeIndex = 4;
	Node *nodeF = new Node('F'); //nodeIndex = 5;
	Node *nodeG = new Node('G'); //nodeIndex = 6;
	Node *nodeH = new Node('H'); //nodeIndex = 7;

	pMap->addNode(nodeA);
	pMap->addNode(nodeB);
	pMap->addNode(nodeC);
	pMap->addNode(nodeD);
	pMap->addNode(nodeE);
	pMap->addNode(nodeF);
	pMap->addNode(nodeG);
	pMap->addNode(nodeH);

	pMap->setValueMatrixForUndirectedGraphy(0, 1);
	pMap->setValueMatrixForUndirectedGraphy(0, 3);
	pMap->setValueMatrixForUndirectedGraphy(1, 2);
	pMap->setValueMatrixForUndirectedGraphy(1, 5);
	pMap->setValueMatrixForUndirectedGraphy(3, 6);
	pMap->setValueMatrixForUndirectedGraphy(3, 7);
	pMap->setValueMatrixForUndirectedGraphy(6, 7);
	pMap->setValueMatrixForUndirectedGraphy(2, 4);
	pMap->setValueMatrixForUndirectedGraphy(4, 5);
	
	cout << "邻接矩阵如下所示 :" << endl;
	pMap->printMatrix();
	cout << endl;
	cout << "其深度优先遍历是：" << endl;
	pMap->depthFirstTraverse(0);
	pMap->resetNode();
	cout << endl;
	cout << "其广度优先遍历是：" << endl;
	pMap->breadthFirstTraverse(0);
	cout << endl;
	delete pMap;
	getchar();
	return 0;
}

