#include<stdio.h>
#include<stdlib.h>
const int MAXVEX = 100;
//��������Ϊ TopologicalSort()
//�ؼ�·���㷨Ϊ CriticalPath()
//TopologicalSort Ϊ ͨ������������ etv �Ĵ���
//CriticalPath Ϊ ��ltv �ͺ����Ĺؼ�·������
//�ؼ�·���Ĳ��裺1.����������etv 2.��ltv  3.ͨ��etv��ltv ��e(i) �� v(i)
//etv:����緢��ʱ�� ltv �������ʱ��
//e(i) �¼����緢��ʱ��   l(i) �¼�������ʱ�䰡
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
	//1.��ʼ��������һ�����Ϊ0�Ķ�����ջ
	for(int i=0;i<GL->numVertexes;i++) 
		if(GL->adjList[i].in==0)
			stack[++top] = i;
	
	top2 =0;
	for(int i=0;i<GL->numVertexes;i++) etv[i] = 0;
	//2.�������򣺶Գ�ջ����������������仡����(�ڵ�)
	while(top!=0)
	{
		int gettop = stack[top--]; //kΪ�����������ж��㣨���Ϊ0��
		printf("%d ",gettop);
		cnt++;//cnt�����ж�����ջ�Ķ��������ó��Ƿ���������ɹ���
		stack2[++top2] = gettop; //stack2 �洢�����������е�ջ
		for(EdgeNode* e = GL->adjList[gettop].firstedge;e;e=e->next)
		{
			int k = e->adjvex; //kΪ�ö���֮����ٵ�
			if(--GL->adjList[k].in==0){  //������Ϊ0������ջ��ע��-1��
				stack[++top] = k;
			}		
			//��������¼������緢��ʱ��ֵ etv��max{ltv[k]+len<k,j>}
			if((etv[gettop]+e->weight)>etv[k]){ //ǰ��+Ȩֵ > ����etv��������ǰ�㣬�ҵ�����max(etv)��
				etv[k] = etv[gettop] + e->weight;
			}
		}
		if(top!=0) printf("->");
	}
	if(cnt!=GL->numVertexes) return false;
	else printf("\n");
	
	//�ؼ�·���㷨CriticalPath()
	//3.��ջ2��ltv
	printf("CriticalPath:\n");

	int ltv[GL->numVertexes+5];
	//��ʼ��ltv ,��ٷ���ʱ��
	for(int i = 0;i<GL->numVertexes;i++)
		ltv[i] = etv[GL->numVertexes-1]; //ltvȫ����ʼ��Ϊ���һ���¼���������ٷ���ʱ�䣬Ϊ������ltv��׼��
	while(top2!=0)
	{
		int gettop = stack2[top2--]; //������������������
		for(EdgeNode* e = GL->adjList[gettop].firstedge;e;e = e->next)
		{
			int k = e->adjvex;
			if(ltv[k]- e->weight<ltv[gettop])  //����ȡ�󣬻���ȡС  min{ltv[k]-len<j,k>}
				ltv[gettop] = ltv[k] - e->weight;
		}
	}
	//stack1����etv,stack2����ltv  (ͬһ�����㣬������etv��ʼ��������ltv��ʼ)
	//4.�����ete��ite�����ж����
	for(int i=0;i<GL->numVertexes;i++) //���ڽӱ������
		for(EdgeNode* e = GL->adjList[i].firstedge;e;e=e->next) //�Ըö���Ļ��������
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
	printf("�����������(vi,vj)���±�,�Լ���Ȩֵ��\n");	
	for(int k=0;k<G.numEdges;k++)
	{
		int i,j; scanf("%d %d",&i,&j);
		int w; scanf("%d",&w);

		Edge* e = (Edge*) malloc(sizeof(Edge));
		e->adjvex = j;
		e->weight = w;
		e->next = G.adjList[i].firstedge;
		G.adjList[i].firstedge = e;

//      ע�⣺���ﲻ������ͼ����������ͼ��		
//		e = (Edge*) malloc(sizeof(Edge));
//		e->adjvex = i;
//		e->weight = w;
//		e->next = G.adjList[j].firstedge;
//		G.adjList[j].firstedge = e;
		
	}
	printf("����ɹ���\n");
}

void CreateAGraph(AGraph* G)
{
	int i,j,k;
	Edge* e;
	printf("���붥�����ͱ���\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	printf("�����붥�����ȣ�");
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
