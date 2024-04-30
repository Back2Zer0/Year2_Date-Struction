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
//�߼����鹹������
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
				//g.arc[i][j]>0����ֹ�γɻ�·
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
Kruskal������С�������ĳ�ʼ״ֻ̬��n��������ޱߵķ���ͨͼ��
��ʼʱ��ÿ�����㶼�Գ�һ����ͨ������
��Щ��������ѡ�������С�ıߣ��˴������γɸ���ķ�����
(����˴���һ�����������ȥ�˱ߣ�ѡ����һ�����۸�С�ı�)��
ֱ�����ж�����ͬһ��ͨ�����ϡ�
*/
void Kruskal(MGraph g)
{
	Edge* edges = EdgeSetArray(g);
	//�߼�����Ĵ��������ˣ�����begin��end����һ�µĵ�����
	//���Բ�����ֻ�·����
	int parent[g.numVertexes];//����ĸ��ڵ�
	memset(parent,0,sizeof(parent));
	for(int i=0;i<g.numEdges;i++)
	{
		int n = Find(parent,edges[i].begin);
		int m = Find(parent,edges[i].end);
		if(n!=m)
		{
			parent[n] = m;//��һ���ܹؼ�����ʾ�˶������������������С�
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
