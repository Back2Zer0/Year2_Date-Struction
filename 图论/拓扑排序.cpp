#include<stdio.h>
#include<stdlib.h>
const int MAXVEX = 100;

typedef struct EdgeNode
{
	int adjvex;
	int weight;
	struct EdgeNode *next;
}Edge,EdgeNode;

typedef struct VertexNode
{
	int in;
	int data;
	EdgeNode *firstedge;
}Vex,VertexNode,AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;
}AGraph,graphAdjList,*GraphAdjList;
bool TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int k,gettop;
	int top = 0;
	int count = 0;
	int *stack;
	stack = (int*) malloc(GL->numVertexes*sizeof(int));
	for(int i = 0;i<GL->numVertexes;i++)
		if(GL->adjList[i].in == 0)
			stack[++top] = i;
	while(top!=0)
	{
		gettop = stack[top--];
		printf("%d ",GL->adjList[gettop].data);
		count++;
		for(e=GL->adjList[gettop].firstedge;e;e=e->next)
		{
			k = e->adjvex;
			if(!(--GL->adjList[k].in))
				stack[++top]=k;
		}
		if(top!=0) printf("->");
	}
	if(count < GL->numVertexes) return false;
	else return true;
}


void headInsert(AGraph& G)
{
	printf("请依次输入边(vi,vj)的下标,以及其权值：\n");	
	for(int k=0;k<G.numEdges;k++)
	{
		int i,j; scanf("%d %d",&i,&j);
		int w; scanf("%d",&w);

		Edge* e = (Edge*) malloc(sizeof(Edge));
		e->adjvex = j;
		e->weight = w;
		e->next = G.adjList[i].firstedge;
		G.adjList[i].firstedge = e;

//      注意：这里不是无向图，而是有向图。		
//		e = (Edge*) malloc(sizeof(Edge));
//		e->adjvex = i;
//		e->weight = w;
//		e->next = G.adjList[j].firstedge;
//		G.adjList[j].firstedge = e;
		
	}
	printf("插入成功！\n");
}

void CreateAGraph(AGraph* G)
{
	int i,j,k;
	Edge* e;
	printf("输入顶点数和边数\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	printf("请输入顶点和入度：");
	for(int i=0;i<G->numVertexes;i++)
	{
		int c;
		scanf("%d %d",&c,&G->adjList[i].in);
		//printf("cnt==%d  vexc==%d\n",i,G->numVertexes);
		G->adjList[i].data = c;
		G->adjList[i].firstedge = NULL;
	}
	headInsert(*G);
	
}
void Traverse(AGraph g)
{
	for(int k=0;k<g.numVertexes;k++)
	{
		printf("%d: ",g.adjList[k].data);
		Edge*e = g.adjList[k].firstedge;
		while(e!=NULL)
		{
			int i = e->adjvex;
			printf("(%d,%d) w=%d ",g.adjList[k].data,g.adjList[i].data,e->weight);
			e = e->next;
		}
		printf("\n\n");
	}
}
int main()
{
	AGraph g;
	CreateAGraph(&g);
	//Traverse(g);
	if(!TopologicalSort(&g)) printf("不符合拓扑条件。");
	
	return 0;
}
/* 

14 20
0 0
1 0
2 2
3 0
4 2
5 3
6 1
7 2
8 2
9 1
10 1
11 2
12 1 
13 2

0 5 1
0 11 1
0 4 1
1 4 1
1 2 1
1 8 1
2 5 1
2 6 1
2 9 1
3 2 1
3 13 1
4 7 1
5 8 1
5 12 1
6 5 1
8 7 1
9 10 1
9 11 1
10 13 1
12 9 1


*/
