#include<iostream>
using namespace std;
const int N = 100;
typedef struct Edge{
	int adjvex;
	int weight;
	struct Edge* next;
}Edge;

typedef struct Vex{
	char data;
	struct Edge* next;
}Vex,AdjList[N];

typedef struct{
	AdjList vexlist;
	int numsEage,numsVex;
}AGraph;

void lastInsert(AGraph* G)
{	
	cout<<"请依次输入边(vi,vj)的下标,以及其权值：";
	for(int k=0;k<G->numsEage;k++)
	{
		int i,j;cin>>i>>j; 
		int w;cin>>w;
		Edge* e = G->vexlist[i].next;
		while(e!=NULL&&e->next!=NULL) e = e->next;

		if(e==NULL){
			G->vexlist[i].next = (Edge*)malloc(sizeof(Edge));
			e = G->vexlist[i].next;
			e->adjvex = j;
			e->weight = w;
			e->next = NULL;			
		}
		else {
			e->next = (Edge*)malloc(sizeof(Edge));
			e->next->adjvex = j;
			e->next->weight = w;
			e->next->next = NULL;				
		}
		
		e = G->vexlist[j].next;
		while(e!=NULL&&e->next!=NULL) e = e->next;

		if(e==NULL){
			G->vexlist[j].next = (Edge*)malloc(sizeof(Edge));
			e = G->vexlist[j].next;
			e->adjvex = i;
			e->weight = w;
			e->next = NULL;			
		}
		else {
			e->next = (Edge*)malloc(sizeof(Edge));
			e->next->adjvex = j;
			e->next->weight = w;
			e->next->next = NULL;				
		}		
	}
	cout<<"插入成功！\n";	
}

void headInsert(AGraph& G)
{
	cout<<"请依次输入边(vi,vj)的下标,以及其权值：";	
	for(int k=0;k<G.numsEage;k++)
	{
		int i,j;cin>>i>>j;
		int w;cin>>w;
		Edge* e = (Edge*) malloc(sizeof(Edge));
		e->adjvex = j;
		e->weight = w;
		e->next = G.vexlist[i].next;
		G.vexlist[i].next = e;
		
		e = (Edge*) malloc(sizeof(Edge));
		e->adjvex = i;
		e->weight = w;
		e->next = G.vexlist[j].next;
		G.vexlist[j].next = e;
		
	}
	cout<<"插入成功！\n";
}

void CreateAGraph(AGraph* G)
{
	int i,j,k;
	Edge* e;
	printf("输入顶点数和边数\n");
	scanf("%d %d",&G->numsVex,&G->numsEage);
	
	cout<<"请输入顶点：";
	for(int i=0;i<G->numsVex;i++)
	{
		char c;
		cin>>c;
		G->vexlist[i].data = c;
		G->vexlist[i].next = NULL;
	}
	headInsert(*G);
	
}
void Traverse(AGraph g)
{
	for(int k=0;k<g.numsVex;k++)
	{
		cout<<g.vexlist[k].data<<":  ";
		Edge*e = g.vexlist[k].next;
		while(e!=NULL)
		{
			int i = e->adjvex;
			printf("(%c,%c) w=%d ",g.vexlist[k].data,g.vexlist[i].data,e->weight);
			e = e->next;
		}
		cout<<endl;
	}
}

int main()
{
	AGraph g;
	CreateAGraph(&g);
	Traverse(g);	
}
/*
4 4
a b c d 
3 0 1
0 1 2
1 2 3
2 3 4
*/
