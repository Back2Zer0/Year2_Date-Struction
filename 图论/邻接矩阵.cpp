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
	printf("���붥�����ͱ�����\n");
	scanf("%d%d",&G->numVertexes,&G->numEdges);
	fflush(stdin);
	printf("��������%d����������ƣ�\n",G->numVertexes);
	for(i=0;i<G->numVertexes;i++)
		cin>>G->vexs[i];
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
			if(i!=j) G->arc[i][j] = INFINITY;
	for(k=0;k<G->numEdges;k++)
	{
		fflush(stdin);
		printf("�����(vi,vj)�ϵ��±�i���±�j��Ȩw��\n");
		scanf("%d %d %d",&i,&j,&w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
	printf("����ɹ���\n");
}
int getV_index(MGraph g,char c)
{
	for(int i=0;i<g.numVertexes;i++)
		if(g.vexs[i]==c) return i;
	
	
	printf("%c������\n",c);
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
	printf("ɾ���ɹ�\n");
}
void LocateVex(MGraph G)
{
	printf("�����붨λ���ַ���");
	char u;cin>>u;
	int j = getV_index(G,u);
	if(j==INFINITY) {
		printf("���ַ�������");
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
	printf("������ҪѰ���ڽӶ���Ķ��㣺");
	cin>>v;
	int index = getV_index(G,v);
	for(int i=0;i<G.numEdges;i++)
	{
		if(G.arc[index][i]!=0&&G.arc[index][i]!=INFINITY){
			return G.vexs[i];
		}
	}
	printf("�������ڽӶ���");
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
	printf("����һ������:");
	char v;cin>>v;
	G->vexs[G->numVertexes++]  = v;
	printf("���붥��ɹ���\n");
}
void InsertArc(MGraph* G)
{
	char v,c;
	int w;
	printf("����һ���ߣ�����������<v1,v2>��Ӧ�ַ����Լ�Ȩֵw:\n");
	cin>>v>>c;
	cin>>w;
	int v_index = getV_index(*G,v);
	int c_index = getV_index(*G,c);
	if(v_index==INFINITY||c_index==INFINITY){cout<<"���ʧ�ܡ�"<<endl;return;}
	G->arc[v_index][c_index] = w;
	G->arc[v_index][c_index] = w;
	cout<<"����߳ɹ�\n";
}
void DeleteArc(MGraph* G)
{
	printf("��������ɾ����<v1,v2>���ַ�");
	char v,c;
	cin>>v>>c;
	int v_index = getV_index(*G,v);
	int c_index = getV_index(*G,c);
	if(v_index==INFINITY||c_index==INFINITY){cout<<"ɾ��ʧ�ܡ�"<<endl;return;}
	G->arc[v_index][c_index] = INFINITY;
	G->arc[v_index][c_index] = INFINITY;
	cout<<"ɾ���߳ɹ�\n";
	
}
void DeleteVex(MGraph* G)
{
	printf("������Ҫɾ���Ķ��㣺");
	char c ;cin>>c;
	int index = getV_index(*G,c);
	if(index==INFINITY){cout<<"ɾ��ʧ��";return;}
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
	for(int i=0;i<G.numVertexes;i++) //ÿ������һ��
	{
		if(!visited[i])
		{
			visited[i] = true;
			printf("%c ",G.vexs[i]);
			q.push(i);
			while(!q.empty())
			{
				q.pop();
				for(int j=0;j<G.numVertexes;j++) //�˽ڵ���ڵ�
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
		cout<<"��"<<G.vexs[i]<<"�ıߣ�";
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
	if(G.numVertexes==0) cout<<"��ͼ�޷����";

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
