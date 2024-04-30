#include<iostream>
#include<queue>
using namespace std;
#define INFINITY 65535
#define MAXVEX 100
typedef struct {
	char vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;
bool visited[MAXVEX];


void CreateMGraph(MGraph* G)
{
	int i,j,k,w;
	printf("输入顶点数和边数：\n");
	scanf("%d%d",&G->numVertexes,&G->numEdges);
	fflush(stdin);
	printf("依次输入%d个顶点的名称：\n",G->numVertexes);
	for(i=0;i<G->numVertexes;i++)
		cin>>G->vexs[i];
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
			if(i!=j) G->arc[i][j] = INFINITY;
	for(k=0;k<G->numEdges;k++)
	{
		fflush(stdin);
		printf("输入边(vi,vj)上的下标i，下标j和权w：\n");
		scanf("%d %d %d",&i,&j,&w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
	printf("输入成功！\n");
}
int getV_index(MGraph g,char c)
{
	for(int i=0;i<g.numVertexes;i++)
		if(g.vexs[i]==c) return i;
	
	
	printf("%c不存在\n",c);
	return INFINITY;
}
void DestroyGraph(MGraph* G)
{
	if(G->numEdges)
		for(int i=0;i<G->numEdges;i++){
			for(int j=0;j<G->numEdges;j++){
				G->arc[i][j] = INFINITY;
			}
		}
	G->numEdges = 0;
	if(G->numVertexes)
		for(int i=0;i<G->numVertexes;i++){
			G->vexs[i] = 0;
		}
	G->numVertexes=0;
	printf("删除成功\n");
}
void LocateVex(MGraph G)
{
	printf("请输入定位的字符：");
	char u;cin>>u;
	int j = getV_index(G,u);
	if(j==INFINITY) {
		printf("该字符不存在");
		return ;
	}
	cout<<G.vexs[j]<<": ";
	for(int i=0;i<G.numVertexes;i++)
	{
		if(G.arc[i][j]!=INFINITY&&G.arc[i][j]!=0&&i!=j)
			printf("(%c,%c)  ",G.vexs[i],G.vexs[j]);
		if(G.arc[j][i]!=INFINITY&&G.arc[j][i]!=0&&i!=j)
			printf("(%c,%c)  ",G.vexs[j],G.vexs[i]);
	}
	
	
}

char FirstAdjVex(MGraph G)
{
	char v;
	printf("请输入要寻找邻接顶点的顶点：");
	cin>>v;
	int index = getV_index(G,v);
	for(int i=0;i<G.numEdges;i++)
	{
		if(G.arc[index][i]!=0&&G.arc[index][i]!=INFINITY){
			return G.vexs[i];
		}
	}
	printf("不存在邻接顶点");
	return ' ';
}
char NextAdjVex(MGraph G,char v,char w)
{

	int v_index = getV_index(G,v);
	int w_index = getV_index(G,w);

	for(int i=w_index+1;i<G.numVertexes;i++)
	{
		if(G.arc[v_index][i]!=0&&G.arc[v_index][i]!=INFINITY){
			return G.vexs[i];
		}
	}
	for(int i = 0;i<w_index;i++){
		if(G.arc[v_index][i]!=0&&G.arc[v_index][i]!=INFINITY){
			return G.vexs[i];
		}
	}
	return ' ';
}
void InsertVex(MGraph* G)
{
	printf("插入一个顶点:");
	char v;cin>>v;
	G->vexs[G->numVertexes++]  = v;
	printf("插入顶点成功！\n");
}
void InsertArc(MGraph* G)
{
	char v,c;
	int w;
	printf("插入一条边，请依次输入<v1,v2>对应字符，以及权值w:\n");
	cin>>v>>c;
	cin>>w;
	int v_index = getV_index(*G,v);
	int c_index = getV_index(*G,c);
	if(v_index==INFINITY||c_index==INFINITY){cout<<"添加失败。"<<endl;return;}
	G->arc[v_index][c_index] = w;
	G->arc[v_index][c_index] = w;
	cout<<"插入边成功\n";
}
void DeleteArc(MGraph* G)
{
	printf("依次输入删除边<v1,v2>的字符");
	char v,c;
	cin>>v>>c;
	int v_index = getV_index(*G,v);
	int c_index = getV_index(*G,c);
	if(v_index==INFINITY||c_index==INFINITY){cout<<"删除失败。"<<endl;return;}
	G->arc[v_index][c_index] = INFINITY;
	G->arc[v_index][c_index] = INFINITY;
	cout<<"删除边成功\n";
	
}
void DeleteVex(MGraph* G)
{
	printf("输入你要删除的顶点：");
	char c ;cin>>c;
	int index = getV_index(*G,c);
	if(index==INFINITY){cout<<"删除失败";return;}
	for(int i=0;i<G->numVertexes;i++){
		if(G->arc[index][i]!=0&&G->arc[index][i]!=INFINITY){
			G->arc[index][i] = INFINITY;
			G->numEdges--;
		}
		if(G->arc[i][index]!=0&&G->arc[i][index]!=INFINITY){
			G->arc[i][index] = INFINITY;
		}
	}
	for(int i=index;i<G->numVertexes;i++)
	{
		G->vexs[i] = G->vexs[i+1];
	}
	G->numVertexes--;
}
void DFS(MGraph G,int i)
{
	int j;
	visited[i] = true;
	printf("%c ",G.vexs[i]);
	for(j=0;j<G.numVertexes;j++)
		if(G.arc[i][j]==1&&!visited[j])
			DFS(G,j);
}
void DFSTraverse(MGraph G)
{
	int i;
	for(int i=0;i<G.numVertexes;i++)
	{
		visited[i] =false;
	}
	for(int i=0;i<G.numVertexes;i++)
	{
		if(!visited[i])
			DFS(G,i);
	}

}
void BFS(MGraph G)
{
	queue<int> q;
	for(int i=0;i<G.numVertexes;i++)
		visited[i] = false;
	for(int i=0;i<G.numVertexes;i++) //每个点走一遍
	{
		if(!visited[i])
		{
			visited[i] = true;
			printf("%c ",G.vexs[i]);
			q.push(i);
			while(!q.empty())
			{
				q.pop();
				for(int j=0;j<G.numVertexes;j++) //此节点的邻点
				{
					if(G.arc[i][j]==1&&!visited[j])
					{
						visited[j] = true;
						printf("%c ",G.vexs[j]);
						q.push(j);
					}
				}
			}
		}
	}
}

void Traverse(MGraph G)
{
	for(int i=0;i<G.numVertexes;i++)
	{
		cout<<"点"<<G.vexs[i]<<"的边：";
		for(int j=0;j<G.numVertexes;j++)
		{
			if(G.arc[i][j]&&G.arc[i][j]!=INFINITY){
				//if(!visited[j]) 
				printf("(%c,%c) w=%d  ",G.vexs[i],G.vexs[j],G.arc[i][j]);
			}
		}
		//visited[i] = true;
		cout<<endl;
	}
	if(G.numVertexes==0) cout<<"空图无法输出";

}
int main()
{
	MGraph g;
	CreateMGraph(&g);
	Traverse(g);
	InsertVex(&g);
	InsertArc(&g);
	DeleteArc(&g);
	DeleteVex(&g);
	Traverse(g);
	return 0;
}

/*
4 4
a b c d 
3 0 1
0 1 2
1 2 3
2 3 4
*/
