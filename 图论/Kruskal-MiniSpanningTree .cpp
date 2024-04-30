#include"Ggraph.cpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	int begin;
	int end;
	int weight;
}Edge;

int Find(int parent[],int f)
{
	while(parent[f]) f = parent[f];
	return f;
}
//边集数组构建函数
Edge* EdgeSetArray(MGraph g)
{
	Edge* edges = (Edge*)malloc(sizeof(Edge)*MAXVEX);

	int k =0;
	while(k<g.numEdges)
	{
		int x,y;
		int min = INFINITY;
		for(int i=0;i<g.numVertexes;i++)
			for(int j=0;j<g.numVertexes;j++)
			{
				//g.arc[i][j]>0：防止形成环路
				if(g.arc[i][j]>0&&min>g.arc[i][j]){
					min = g.arc[i][j];
					x = i;
					y = j;
				}
			}	
		g.arc[x][y] = 0;
		g.arc[y][x] = 0;
		edges[k].begin = x;
		edges[k].end = y;
		edges[k].weight = min;
		k++;
	}
//	for (int i = 0; i < g.numEdges; i++)
//	{
//		printf("\n%d ", edges[i].begin);
//		printf("%d ", edges[i].end);
//		printf("%d ", edges[i].weight);
//	}
	return edges;
}
/*
Kruskal：令最小生成树的初始状态只有n个顶点而无边的非连通图。
初始时，每个顶点都自成一个连通分量。
这些分量不断选择代价最小的边，彼此连接形成更大的分量。
(如果彼此在一个分量里，则舍去此边，选择下一个代价更小的边)。
直到所有顶点在同一连通分量上。
*/
void Kruskal(MGraph g)
{
	Edge* edges = EdgeSetArray(g);
	//边集数组的创建决定了，所有begin和end保持一致的单调性
	//所以不会出现回路现象。
	int parent[g.numVertexes];//顶点的父节点
	memset(parent,0,sizeof(parent));
	for(int i=0;i<g.numEdges;i++)
	{
		int n = Find(parent,edges[i].begin);
		int m = Find(parent,edges[i].end);
		if(n!=m)
		{
			parent[n] = m;//这一步很关键，表示此顶点已在生成树集合中。
			printf("(%d,%d) w=%d\n",edges[i].begin,edges[i].end,edges[i].weight);
		}
	}
	
}

int main(void)
{
	MGraph g;
	CreateMGraph(&g);
	Kruskal(g);
}
/*
9 15
0 1 2 3 4 5 6 7 8 

0 1 10
1 2 18
2 3 22
3 4 20
4 5 26
5 0 11
6 1 16 
6 5 17
6 3 24
8 1 12
8 2 8
8 3 21
7 6 19
7 3 16
7 4 7
*/
