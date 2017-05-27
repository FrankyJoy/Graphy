克鲁斯卡尔算法最小生成树 Kruskal
算法内容参考与慕课网的视频

【图的形状】：
             A
		  /  |  \
		B----F---E
		 \  / \ /
		  C -- D

【节点索引】：

A  B  C  D  E  F
0  1  2  3  4  5

【边的权重】：

A-B 6  A-E 5   A-F 1
B-C 3  B-F 2   
C-F 8  C-D 7
D-F 4  D-E 2
E-F 9

【算法思想】：
1. 找出所有的边

2. 找出这些边组成的最小生成树
	2.1 找到算法结束条件
	2.2 从边集合中找到最小边
	2.3 找出最小边连接的点
	2.4 找出点所在的点集合
	2.5 根据点所在集合的不同做出不同处理


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