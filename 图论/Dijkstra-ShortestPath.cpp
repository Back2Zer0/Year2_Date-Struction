#include"Ggraph.cpp"
#include<stdio.h>

#define INFINITY 65535
typedef int Patharc[MAXVEX];
typedef int ShortPathTable[MAXVEX];

void Dijkstra(MGraph G, int v0, Patharc *P,ShortPathTable *D)
{
	//P[v]:����v�����·���ϵ�ǰһ������   D:v0������������·����Ȩֵ��
	bool final[MAXVEX]; //final[v] Ϊ�棬��ʾv0��v �����·�������
	//1.��ʼ����������
	for(int v = 0;v<G.numVertexes;v++)
	{
		final[v] = false;
		(*D)[v] = G.arc[v0][v];
		(*P)[v] = 0;
	} 
	(*D)[v0] = 0; //v0��v0 ȨֵΪ0
	final[v0] = 1;
	//2.��ʼ��ѭ����ÿ�����v0 ��һ��v��������·��
	for(int v=1;v<G.numVertexes;v++)
	{
		int min = INFINITY;
		int k = 1;
		for(int w=1;w<G.numVertexes;w++)
		{
			if(final[w]==0 && min>(*D)[w]) //��v0����Ķ�����루��Ȩֵ��
			{
				k=w;
				min = (*D)[w];
			}
		}
		final[k] = 1; //�������·���ļ�����
		//3.�������飬��kΪ��ʼ��
		for(int w=0;w<G.numVertexes;w++)
		{
			if(!final[w] && (min+G.arc[k][w])<(*D)[w])
			{
				(*D)[w] = min + G.arc[k][w]; 
				(*P)[w] = k;//w�������һ������Ϊ k
			}
		}
	}
}
void dfs(Patharc p,int x)
{
	if(x) dfs(p,p[x]);
	printf("%d ",x);
}
int main(void)
{
	MGraph g;
	CreateMGraph(&g);
	Patharc p;
	ShortPathTable s;
	Dijkstra(g,0,&p,&s);
	
	dfs(p,8);
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
