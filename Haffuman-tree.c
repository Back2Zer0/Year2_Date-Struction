#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//构造哈夫曼树和生成哈夫曼编码。
#define max_num 20
#define max_len 2*max_num-1
typedef struct 
{
	int weight;
	int parent;
	int left_child;
	int right_child;
	
}HuffNode,HuffTree[max_len+1];
void find_min(HuffTree tree,int len ,int* num1,int* num2)
{
	int i;
	int min = -1;
	int min_num = INT_MAX;
	for( i = 0;i<len;i++)
	{
		if(tree[i].parent==-1&&min_num>=tree[i].weight){
			min = i;
			min_num = tree[i].weight;
		}
	}
	*num1 = min;
	min = -1;
	min_num = INT_MAX;
	for( i = 0;i<len;i++)
	{
		if(tree[i].parent==-1&&min_num>=tree[i].weight&&i!=*num1){
			min = i;
			min_num = tree[i].weight;
		}
	}
	*num2 = min;
}
void create_Huffman_Tree(HuffTree tree,int weight[],int len)
{
	int i;
	for(i=0;i<2*len-1;i++)
	{
		if(i<len)
			tree[i].weight = weight[i];
		tree[i].parent = -1;
		tree[i].left_child = -1;
		tree[i].right_child = -1;
	}
	for(i = len;i<2*len-1;i++ )  
	{
		int num1,num2;
		find_min(tree,i,&num1,&num2);
		tree[i].weight = tree[num1].weight+tree[num2].weight;
		tree[i].left_child = num1;
		tree[i].right_child = num2;
		tree[num1].parent = i;// from 0
		tree[num2].parent = i;
	}
	
}
char** create_Huffman_Code(HuffTree tree,int len)
{
//不能获取每一条路径的长度
	char* temp_ch = (char*)malloc(sizeof(char)*len);
    char** code = (char**)malloc(sizeof(char*)*len);
	temp_ch[len-1] = '\0';
	for(int i = 0;i<len;i++)
	{
		int index = len-1; //index:编码字符串下标 
		int current = i;   //current:树的最底层结点下标 
		int parent = tree[current].parent;
	
		while(parent!=-1)
		{
			index--;
			if(tree[parent].left_child == current){
				temp_ch[index] = '1';
			}
			else{
				temp_ch[index] = '0';
			}
			current = parent;
			parent = tree[parent].parent;
		}
		code[i] = (char*)malloc(sizeof(char)*(len-index));
		strcpy(code[i],&temp_ch[index]);		
	}
	return code; 
	
}

int main(void)
{
	int i,n;
	printf("权重个数:");
	scanf("%d",&n);
	if(n<=1) {printf("无效输入(amount need >= 1)"); return 0;}
	int weight[n];
	for( i = 0;i<n;i++)
	{
		scanf("%d",&weight[i]);
	}
	HuffTree HTree;
	create_Huffman_Tree(HTree,weight,n);
	char** code = create_Huffman_Code(HTree,n);
	for(int i=0;i<n;i++)
	{
		printf("权重%d的编码:",weight[i]);
		printf("%s\n",code[i]);

	}
	
	return 0;
}
