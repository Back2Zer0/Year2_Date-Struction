#include<iostream>
using namespace std;

const int N = 20;
//与邻接表的区别仅仅在于，同一个边，邻接表两个顶点都要保存，而多重表只需要一个顶点保存

/*
问：创建时，如果0作为尾部(右边下表），而此时的data已经不是0了，该怎么插入？难道全部遍历一遍吗？
答：不需要。以(0,1)为例。只需要创建一个e(0,1)，将e插入到0的jlink，1的ilink即可。一份e，两个下表都能使用了。
遍历也是这个道理。对于一个data，直接遍历它的ilink和jlink就可以。（如果怕重复，加一个flag成员变量判断就ok)

问：能用静态数组实现吗？
答：可以。但就像用静态数组实现链表一样，需要在数组末端单独充当 malloc 的“申请空间”，算是一种“拙劣模仿”，不如链表优越。
*/
typedef struct Edge
{
	int weight;
	int visitFlag;//遍历去重使用，可带可不带。
	int ivex;
	int jvex;
	Edge* ilink;  //以i结尾
	Edge* jlink;  //以j结尾
}Edge;

typedef struct Vex
{
	char data;
	Edge* firstVex;
}Vlist;

typedef struct Graph
{
	Vlist* vexlist; //顺序表
	int numsVex,numsEdge;
}Graph;
void InitAMLGraph(Graph *G)
{
    G->numsVex = 0;
    G->numsEdge = 0;
    G->vexlist = (Vex *)malloc(N * sizeof(Vex));
    // 初始化边链表头结点（也可不带头结点）
    int i;
    for (i = 0; i < N; i++)
    {
        G->vexlist[i].firstVex = (Edge *) malloc(sizeof(Edge));
        G->vexlist[i].firstVex->ilink = NULL;
        G->vexlist[i].firstVex->jlink = NULL;
    }
    printf("已初始化邻接多重表!\n");
}
void createGraph(Graph* G)
{
	cout<<"请输入顶点数和边数"<<endl;
	cin>>G->numsVex>>G->numsEdge;
	cout<<"依次输入顶点符号：";
    for (int i = 0; i < G->numsVex; i++)
    {
        cin>>G->vexlist[i].data;
    }

    int i,j,w;
    printf("请依次输入边(vi, vj)的头、尾顶点及其权值:");
    for (int k = 0; k < G->numsEdge; k++)
    {

        cin>>i>>j>>w;

        Edge *e;
        e = (Edge *) malloc(sizeof(Edge));
        e->visitFlag = 0;
        e->weight = w;
        e->ivex = i;
        e->jvex = j;

        // 头插法插入相同头顶点的边结点
        e->ilink = G->vexlist[i].firstVex->ilink;
        G->vexlist[i].firstVex->ilink = e;
        
        // 头插法插入相同尾顶点的边结点
        e->jlink = G->vexlist[j].firstVex->jlink;
        G->vexlist[j].firstVex->jlink = e;
    }
    printf("已完成邻接多重表的创建!\n");
} 
void Traverse(Graph G)
{
 
    Edge *p;
    for (int i = 0; i < G.numsVex; i++)
    {
        p = G.vexlist[i].firstVex->ilink;
        while (p && !p->visitFlag)
        {
            printf("边： <%c,%c> w=%d \n", G.vexlist[p->ivex].data,G.vexlist[p->jvex].data,p->weight
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
