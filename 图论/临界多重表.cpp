#include<iostream>
using namespace std;

const int N = 20;
//���ڽӱ������������ڣ�ͬһ���ߣ��ڽӱ��������㶼Ҫ���棬�����ر�ֻ��Ҫһ�����㱣��

/*
�ʣ�����ʱ�����0��Ϊβ��(�ұ��±�������ʱ��data�Ѿ�����0�ˣ�����ô���룿�ѵ�ȫ������һ����
�𣺲���Ҫ����(0,1)Ϊ����ֻ��Ҫ����һ��e(0,1)����e���뵽0��jlink��1��ilink���ɡ�һ��e�������±���ʹ���ˡ�
����Ҳ�������������һ��data��ֱ�ӱ�������ilink��jlink�Ϳ��ԡ���������ظ�����һ��flag��Ա�����жϾ�ok)

�ʣ����þ�̬����ʵ����
�𣺿��ԡ��������þ�̬����ʵ������һ������Ҫ������ĩ�˵����䵱 malloc �ġ�����ռ䡱������һ�֡�׾��ģ�¡�������������Խ��
*/
typedef struct Edge
{
	int weight;
	int visitFlag;//����ȥ��ʹ�ã��ɴ��ɲ�����
	int ivex;
	int jvex;
	Edge* ilink;  //��i��β
	Edge* jlink;  //��j��β
}Edge;

typedef struct Vex
{
	char data;
	Edge* firstVex;
}Vlist;

typedef struct Graph
{
	Vlist* vexlist; //˳���
	int numsVex,numsEdge;
}Graph;
void InitAMLGraph(Graph *G)
{
    G->numsVex = 0;
    G->numsEdge = 0;
    G->vexlist = (Vex *)malloc(N * sizeof(Vex));
    // ��ʼ��������ͷ��㣨Ҳ�ɲ���ͷ��㣩
    int i;
    for (i = 0; i < N; i++)
    {
        G->vexlist[i].firstVex = (Edge *) malloc(sizeof(Edge));
        G->vexlist[i].firstVex->ilink = NULL;
        G->vexlist[i].firstVex->jlink = NULL;
    }
    printf("�ѳ�ʼ���ڽӶ��ر�!\n");
}
void createGraph(Graph* G)
{
	cout<<"�����붥�����ͱ���"<<endl;
	cin>>G->numsVex>>G->numsEdge;
	cout<<"�������붥����ţ�";
    for (int i = 0; i < G->numsVex; i++)
    {
        cin>>G->vexlist[i].data;
    }

    int i,j,w;
    printf("�����������(vi, vj)��ͷ��β���㼰��Ȩֵ:");
    for (int k = 0; k < G->numsEdge; k++)
    {

        cin>>i>>j>>w;

        Edge *e;
        e = (Edge *) malloc(sizeof(Edge));
        e->visitFlag = 0;
        e->weight = w;
        e->ivex = i;
        e->jvex = j;

        // ͷ�巨������ͬͷ����ı߽��
        e->ilink = G->vexlist[i].firstVex->ilink;
        G->vexlist[i].firstVex->ilink = e;
        
        // ͷ�巨������ͬβ����ı߽��
        e->jlink = G->vexlist[j].firstVex->jlink;
        G->vexlist[j].firstVex->jlink = e;
    }
    printf("������ڽӶ��ر�Ĵ���!\n");
} 
void Traverse(Graph G)
{
 
    Edge *p;
    for (int i = 0; i < G.numsVex; i++)
    {
        p = G.vexlist[i].firstVex->ilink;
        while (p && !p->visitFlag)
        {
            printf("�ߣ� <%c,%c> w=%d \n", G.vexlist[p->ivex].data,G.vexlist[p->jvex].data,p->weight
        		 );
            p->visitFlag = 1;
            p = p->ilink;
        }
    } 

}
void Traverse_all(Graph g)
{
    Edge *pi,*pj;
    for (int i = 0; i < g.numsVex; i++)
    {
        pi = g.vexlist[i].firstVex->ilink;
        pj = g.vexlist[i].firstVex->jlink;
        cout<<g.vexlist[i].data<<" :";
        while(pi)
        {
            printf(" <%c,%c> w=%d ", g.vexlist[pi->ivex].data,g.vexlist[pi->jvex].data,pi->weight
        		 );
            pi = pi->ilink;
		}
		while(pj)
		{
            printf(" <%c,%c> w=%d ", g.vexlist[pj->ivex].data,g.vexlist[pj->jvex].data,pj->weight
        		 );
        	pj = pj->jlink;
		}
        cout<<endl;
    } 
	
}
int main(void)
{
	Graph g;
	InitAMLGraph(&g);
	createGraph(&g);
	Traverse_all(g);
}
/*
4 5
a b c d 
0 1 1
0 2 2
0 3 3
1 2 4
3 2 5
*/
