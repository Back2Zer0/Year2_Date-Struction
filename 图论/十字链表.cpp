#include<iostream>
using namespace std;

const int N = 100;

typedef struct Edge
{
	int tailvex;
	int headvex;
	Edge* headlink; //指向headvex相同的，下一个同样的入边顶点
	Edge* taillink; //指向tailvex相同的，下一个同样的出边顶点
	int weight;
}Edge;

typedef struct Vex
{
	char data;
	Edge* firstin;
	Edge* firstout;
}Vlist[N];

typedef struct Graph
{
	Vlist vexlist;
	int numsVex,numsEdge;
}Graph;

void createGraph(Graph* G)
{
	cout<<"请输入顶点数和边数"<<endl;
	cin>>G->numsVex;cin>>G->numsEdge;
	cout<<"依次输入顶点符号：";
	for(int i=0;i<G->numsVex;i++)
	{
		cin>>G->vexlist[i].data;
		G->vexlist[i].firstin = NULL;
		G->vexlist[i].firstout = NULL;
	}
	cout<<"按照(v1,v2) w下标输入边的头、尾、权值";
	for(int k=0;k<G->numsEdge;k++)
	{
		int i,j,w;
		cin>>i>>j>>w;
		Edge* e = (Edge*)malloc(sizeof(Edge));
		e->tailvex = i;
		e->headvex = j;
		e->weight = w;
		//头插法
		e->taillink = G->vexlist[i].firstout;
		G->vexlist[i].firstout = e;
		e->headlink = G->vexlist[j].firstin;
		G->vexlist[j].firstin = e;
	}	
} 
void Traverse(Graph G)
{
	for(int k=0;k<G.numsVex;k++)
	{
		cout<<G.vexlist[k].data<<": ";
		Edge* eo = G.vexlist[k].firstout;
		Edge* ei = G.vexlist[k].firstin;
		int cnt = 0;
		cout<<"出度: ";
		while(eo!=NULL)
		{
			int i = eo->tailvex;
			int j = eo->headvex;
			printf("(%c,%c) w=%d ",G.vexlist[i].data,G.vexlist[j].data,eo->weight);
			eo=eo-> taillink;
			cnt++;
		}
		printf("共%d个出度\n",cnt);
		
		cnt = 0;
		cout<<"入度：";
		while(ei!=NULL)
		{
			int i = ei->tailvex;
			int j = ei->headvex;
			printf("(%c,%c) w=%d ",G.vexlist[i].data,G.vexlist[j].data,ei->weight);
			ei=ei->headlink;	
			cnt++;		
		}
		printf("共%d个入度\n\n",cnt);
	}
}
int main(void)
{
	Graph g;
	createGraph(&g);
	Traverse(g);
	
	return 0;
}
/*
4 5
a b c d 
0 3 1
2 0 2
1 0 3
2 1 4
1 2 5
*/
