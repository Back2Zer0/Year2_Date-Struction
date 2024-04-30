#include"Ggraph.cpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define v0 0    //初始顶点下标
void Prim(MGraph G)
{
	int adjvex[MAXVEX]; //存当前树的顶点集合可以到达的每个顶点下标
	int lowcost[MAXVEX];//存当前点到达每个顶点的权值
	
	//1.初始化两个数组
	lowcost[v0] = 0; //点0加入生成树
	adjvex[0] = v0; //第一个定点下标
	for(int i=0;i<G.numVertexes;i++)
	{
		lowcost[i] = G.arc[v0][i]; // 当前顶点(v0) 到达每个i顶点的距离
		adjvex[i] = v0;  // 下标 i 的上一个顶点是 v0
	}
	
	//2.主循环：逐个找最小边
	for(int i=0;i<G.numVertexes;i++)
	{
		int min = INFINITY;
		int k;
		for(int j=0;j<G.numVertexes;j++)
		{
			//找最小边
			if(lowcost[j]!=0 && min>lowcost[j])
			{
				k = j;
				min = lowcost[j];
			}
		}
		if(k!=adjvex[k]) printf("(%d,%d) ",adjvex[k],k);
		//3.找到后，刷新当前定点，同时更新到达每个定点的距离（若为0则不计入）
		for(int j = 0;j<G.numVertexes;j++) 
		{
			if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j]) //满足两个条件再更新
			{
				adjvex[j] = k;   //更新到达每个i顶点的最短距离
				lowcost[j] = G.arc[k][j];	 //更新到达 i 顶点的上个顶点			
			}
		}
		
	}
	
}
int main(void)
{
	MGraph g;
	CreateMGraph(&g);
	Prim(g);
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
