#include<iostream>
using namespace std;

const int N = 100;

typedef struct Edge
{
	int tailvex;
	int headvex;
	Edge* headlink; //ָ��headvex��ͬ�ģ���һ��ͬ������߶���
	Edge* taillink; //ָ��tailvex��ͬ�ģ���һ��ͬ���ĳ��߶���
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
	cout<<"�����붥�����ͱ���"<<endl;
	cin>>G->numsVex;cin>>G->numsEdge;
	cout<<"�������붥����ţ�";
	for(int i=0;i<G->numsVex;i++)
	{
		cin>>G->vexlist[i].data;
		G->vexlist[i].firstin = NULL;
		G->vexlist[i].firstout = NULL;
	}
	cout<<"����(v1,v2) w�±�����ߵ�ͷ��β��Ȩֵ";
	for(int k=0;k<G->numsEdge;k++)
	{
		int i,j,w;
		cin>>i>>j>>w;
		Edge* e = (Edge*)malloc(sizeof(Edge));
		e->tailvex = i;
		e->headvex = j;
		e->weight = w;
		//ͷ�巨
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
		cout<<"����: ";
		while(eo!=NULL)
		{
			int i = eo->tailvex;
			int j = eo->headvex;
			printf("(%c,%c) w=%d ",G.vexlist[i].data,G.vexlist[j].data,eo->weight);
			eo=eo-> taillink;
			cnt++;
		}
		printf("��%d������\n",cnt);
		
		cnt = 0;
		cout<<"��ȣ�";
		while(ei!=NULL)
		{
			int i = ei->tailvex;
			int j = ei->headvex;
			printf("(%c,%c) w=%d ",G.vexlist[i].data,G.vexlist[j].data,ei->weight);
			ei=ei->headlink;	
			cnt++;		
		}
		printf("��%d�����\n\n",cnt);
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
