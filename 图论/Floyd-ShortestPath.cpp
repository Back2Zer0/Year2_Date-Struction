#include"Ggraph.cpp"
#include<stdio.h>

#define INFINITY 65535
typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
//二维：没有设置起点，遍历所有点为起点
//Patharc[v1][v2] = k : v1到v2要经过的第一个顶点k
//ShortPathTable[v1][v2] = k : v1到v2 的最短路径
void Floyd(MGraph G, Patharc *P,ShortPathTable *D)
{
	//1.初始化（所有点到点的初始化）
	for(int v=0;v<G.numVertexes;v++)
	{
		for(int w=0;w<G.numVertexes;w++)
		{
			(*D)[v][w] = G.arc[v][w];
			(*P)[v][w] = w;
		}
	}
	//2.遍历查找所有以 点 k 为中间点，v为起点，w为终点的最短路径。
	for(int k=0;k<G.numVertexes;k++)
	{
		for(int v=0;v<G.numVertexes;v++)
		{
			for(int w = 0;w<G.numVertexes;w++)
			{
				if((*D)[v][w]>(*D)[v][k]+(*D)[k][w])
				{
					(*D)[v][w] = (*D)[v][k]+(*D)[k][w];
					(*P)[v][w] = (*P)[v][k];
				}
			}
		}
	}
	//3.输出
	for(int v=0;v<G.numVertexes;v++) //遍历以 v 为起点, w 为终点的路径
	{
		for(int w=v+1;w<G.numVertexes;w++)
		{
			//1.打印权值
			
			printf("v%d-v%d weight: %d \n",v,w,(*D)[v][w]);
			
			//2.输出路径（这里的输出类似链表~）
			
			int k=(*P)[v][w]; //让 当前顶点k 作为第一个路径顶点下标（初始化）
			printf(" path: %d",v); //打印该路径源点
			
			while(k!=w) //如果 k 不是终点
			{
				printf(" -> %d",k); //打印
				k=(*P)[k][w]; //获取下一个顶点
			}
			printf(" -> %d\n",w);//打印终点
		}
		
		printf("\n");//打印下一个起点终点不同的路径
	}
}

int main(void)
{
	MGraph g;
	CreateMGraph(&g);
	Patharc p;
	ShortPathTable s;
	Floyd(g,&p,&s);

}
/*
9 16
0 1 2 3 4 5 6 7 8 

0 1 1
0 2 5
1 2 3
1 3 7
1 4 5
2 4 1
2 5 7
3 4 2
4 5 3
3 6 3
4 6 6 
4 7 9
5 7 5
6 7 2
6 8 7
7 8 4
*/
