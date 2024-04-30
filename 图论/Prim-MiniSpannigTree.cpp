#include"Ggraph.cpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define v0 0    //��ʼ�����±�
void Prim(MGraph G)
{
	int adjvex[MAXVEX]; //�浱ǰ���Ķ��㼯�Ͽ��Ե����ÿ�������±�
	int lowcost[MAXVEX];//�浱ǰ�㵽��ÿ�������Ȩֵ
	
	//1.��ʼ����������
	lowcost[v0] = 0; //��0����������
	adjvex[0] = v0; //��һ�������±�
	for(int i=0;i<G.numVertexes;i++)
	{
		lowcost[i] = G.arc[v0][i]; // ��ǰ����(v0) ����ÿ��i����ľ���
		adjvex[i] = v0;  // �±� i ����һ�������� v0
	}
	
	//2.��ѭ�����������С��
	for(int i=0;i<G.numVertexes;i++)
	{
		int min = INFINITY;
		int k;
		for(int j=0;j<G.numVertexes;j++)
		{
			//����С��
			if(lowcost[j]!=0 && min>lowcost[j])
			{
				k = j;
				min = lowcost[j];
			}
		}
		if(k!=adjvex[k]) printf("(%d,%d) ",adjvex[k],k);
		//3.�ҵ���ˢ�µ�ǰ���㣬ͬʱ���µ���ÿ������ľ��루��Ϊ0�򲻼��룩
		for(int j = 0;j<G.numVertexes;j++) 
		{
			if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j]) //�������������ٸ���
			{
				adjvex[j] = k;   //���µ���ÿ��i�������̾���
				lowcost[j] = G.arc[k][j];	 //���µ��� i ������ϸ�����			
			}
		}
		
	}
	
}
int main(void)
{
	MGraph g;
	CreateMGraph(&g);
	Prim(g);
}
/*
9 15
0 1 2 3 4 5 6 7 8 

0 1 10
1 2 18
2 3 22
3 4 20
4 5 26
5 0 11
6 1 16 
6 5 17
6 3 24
8 1 12
8 2 8
8 3 21
7 6 19
7 3 16
7 4 7
*/
