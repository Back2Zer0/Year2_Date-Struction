#include<stdio.h>
#include<stdlib.h>
const int MAXVEX = 100;
//拓扑排序为 TopologicalSort()
//关键路径算法为 CriticalPath()
//TopologicalSort 为 通过拓扑排序求 etv 的代码
//CriticalPath 为 求ltv 和后续的关键路径工作
//关键路径的步骤：1.拓扑排序求etv 2.求ltv  3.通过etv和ltv 求e(i) 和 v(i)
//etv:活动最早发生时间 ltv 活动最晚发生时间
//e(i) 事件最早发生时间   l(i) 事件最晚发生时间啊
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


bool CriticalPath(GraphAdjList GL)
{
	printf("TopologicalSort:");
	int stack[MAXVEX];
	int top = 0;
	int cnt=0;
	int etv[GL->numVertexes+5];
	int stack2[GL->numVertexes+5];
	int top2 = 0;
	//1.初始化：将第一批入度为0的顶点入栈
	for(int i=0;i<GL->numVertexes;i++) 
		if(GL->adjList[i].in==0)
			stack[++top] = i;
	
	top2 =0;
	for(int i=0;i<GL->numVertexes;i++) etv[i] = 0;
	//2.拓扑排序：对出栈顶点输出，并遍历其弧顶点(邻点)
	while(top!=0)
	{
		int gettop = stack[top--]; //k为弹出来的序列顶点（入度为0）
		printf("%d ",gettop);
		cnt++;//cnt用来判断最后出栈的顶点数，得出是否拓扑排序成功。
		stack2[++top2] = gettop; //stack2 存储拓扑排序序列的栈
		for(EdgeNode* e = GL->adjList[gettop].firstedge;e;e=e->next)
		{
			int k = e->adjvex; //k为该顶点之后的临点
			if(--GL->adjList[k].in==0){  //如果入度为0继续入栈（注意-1）
				stack[++top] = k;
			}		
			//求各顶点事件的最早发生时间值 etv：max{ltv[k]+len<k,j>}
			if((etv[gettop]+e->weight)>etv[k]){ //前点+权值 > 后点的etv。（遍历前点，找到后点的max(etv)）
				etv[k] = etv[gettop] + e->weight;
			}
		}
		if(top!=0) printf("->");
	}
	if(cnt!=GL->numVertexes) return false;
	else printf("\n");
	
	//关键路径算法CriticalPath()
	//3.用栈2找ltv
	printf("CriticalPath:\n");

	int ltv[GL->numVertexes+5];
	//初始化ltv ,最迟发生时间
	for(int i = 0;i<GL->numVertexes;i++)
		ltv[i] = etv[GL->numVertexes-1]; //ltv全部初始化为最后一个事件结束的最迟发生时间，为回溯求ltv做准备
	while(top2!=0)
	{
		int gettop = stack2[top2--]; //从拓扑序列里逆向找
		for(EdgeNode* e = GL->adjList[gettop].firstedge;e;e = e->next)
		{
			int k = e->adjvex;
			if(ltv[k]- e->weight<ltv[gettop])  //正推取大，回推取小  min{ltv[k]-len<j,k>}
				ltv[gettop] = ltv[k] - e->weight;
		}
	}
	//stack1里求etv,stack2里求ltv  (同一个顶点，最早在etv开始，最晚在ltv开始)
	//4.最后求ete和ite，并判断输出
	for(int i=0;i<GL->numVertexes;i++) //对邻接表顶点遍历
		for(EdgeNode* e = GL->adjList[i].firstedge;e;e=e->next) //对该顶点的弧顶点遍历
		{
			int k = e->adjvex;
			int ete = etv[i];
			int lte = ltv[k] - e->weight;
			if(ete == lte)
				printf("<v%d,v%d> length: %d ,",GL->adjList[i].data,GL->adjList[k].data,e->weight);
			
		}
	
	return true;
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
	CriticalPath(&g);
	
	
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
/*
10 13

0 0
1 1
2 1
3 2
4 2 
5 1
6 1
7 2
8 1
9 2


0 2 4
0 1 3
1 4 6
1 3 5
2 5 7
2 3 8
3 4 3
4 7 4
4 6 9
5 7 6
6 9 2
7 8 5
8 9 3


*/
