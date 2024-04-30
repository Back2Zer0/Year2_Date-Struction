#include"Ggraph.cpp"
#include<stdio.h>

#define INFINITY 65535
typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
//��ά��û��������㣬�������е�Ϊ���
//Patharc[v1][v2] = k : v1��v2Ҫ�����ĵ�һ������k
//ShortPathTable[v1][v2] = k : v1��v2 �����·��
void Floyd(MGraph G, Patharc *P,ShortPathTable *D)
{
	//1.��ʼ�������е㵽��ĳ�ʼ����
	for(int v=0;v<G.numVertexes;v++)
	{
		for(int w=0;w<G.numVertexes;w++)
		{
			(*D)[v][w] = G.arc[v][w];
			(*P)[v][w] = w;
		}
	}
	//2.�������������� �� k Ϊ�м�㣬vΪ��㣬wΪ�յ�����·����
	for(int k=0;k<G.numVertexes;k++)
	{
		for(int v=0;v<G.numVertexes;v++)
		{
			for(int w = 0;w<G.numVertexes;w++)
			{
				if((*D)[v][w]>(*D)[v][k]+(*D)[k][w])
				{
					(*D)[v][w] = (*D)[v][k]+(*D)[k][w];
					(*P)[v][w] = (*P)[v][k];
				}
			}
		}
	}
	//3.���
	for(int v=0;v<G.numVertexes;v++) //������ v Ϊ���, w Ϊ�յ��·��
	{
		for(int w=v+1;w<G.numVertexes;w++)
		{
			//1.��ӡȨֵ
			
			printf("v%d-v%d weight: %d \n",v,w,(*D)[v][w]);
			
			//2.���·��������������������~��
			
			int k=(*P)[v][w]; //�� ��ǰ����k ��Ϊ��һ��·�������±꣨��ʼ����
			printf(" path: %d",v); //��ӡ��·��Դ��
			
			while(k!=w) //��� k �����յ�
			{
				printf(" -> %d",k); //��ӡ
				k=(*P)[k][w]; //��ȡ��һ������
			}
			printf(" -> %d\n",w);//��ӡ�յ�
		}
		
		printf("\n");//��ӡ��һ������յ㲻ͬ��·��
	}
}

int main(void)
{
	MGraph g;
	CreateMGraph(&g);
	Patharc p;
	ShortPathTable s;
	Floyd(g,&p,&s);

}
/*
9 16
0 1 2 3 4 5 6 7 8 

0 1 1
0 2 5
1 2 3
1 3 7
1 4 5
2 4 1
2 5 7
3 4 2
4 5 3
3 6 3
4 6 6 
4 7 9
5 7 5
6 7 2
6 8 7
7 8 4
*/
