#include<stdio.h>
#define MAX_NUM 100
typedef struct node
{
	int num;
	int next;
}node ;
void Initnum(node num[])
{
	int i;
	for(i=0;i<MAX_NUM-1;i++){
		num[i].next = i+1;
	}
	num[MAX_NUM-1].next = 1;
}
int malloc_s(node* num)
{
	int index = num[0].next;
	num[0].next = num[index].next;
	return index;
}
int length(node* num)
{
	int index = num[MAX_NUM-1].next;// index = 1
	int i = 0;
    while(index!=num[0].next)  //num[0].next = 3
    {
		i++;//1 2
		index = num[index].next;//2 3
	}
	return i;
}
void addnum(node* num,int val)
{
    int i = malloc_s(num);
    num[i].num = val;
}
void modifynum(node* num,int order,int val)
{
	int real_ord = MAX_NUM-1;
	int i ;
	for(i=0;i<order;i++){
		real_ord = num[real_ord].next;
	}
	num[real_ord].num = val;
	
}
void insertnum(node* num,int order,int val)
{
	int  last = length(num);
	int real_ord = MAX_NUM-1;
	int i ;
	for(i=1;i<order;i++){
		real_ord = num[real_ord].next;
	}
	int new_index = malloc_s(num); //ÐÂ½Úµã 
	num[last].next = num[new_index].next;
	num[new_index].num = val;
    
	int temp = num[real_ord].next;  //real_ord 2 temp 3   new_index 5
	num[real_ord].next = new_index;  //2->5
	num[new_index].next = temp;      //5->3
	
}
void deletenum(node* num,int order)
{
	int  last = length(num);
	int real_ord = MAX_NUM-1;
	int i ;
	for(i=1;i<order;i++){
		real_ord = num[real_ord].next;
	}
	int nnext = num[real_ord].next ; //nnext = 2  real_ord = 1
	num[real_ord].next = num[nnext].next; //1->3
	
    num[last].next = nnext;
	num[nnext].next = num[0].next;//2->5
	num[0].next = nnext; //0->2
}
void print_num(node num[])
{	
    int size = length(num);
    int real_ord = MAX_NUM-1;
	int i ;
	for(i=0;i<size;i++){
		real_ord = num[real_ord].next;
		printf("%d ",num[real_ord].num);
	}
	printf("\n");
}
int main(void)
{
    node staticnum[100];
    Initnum(staticnum);

	
}
