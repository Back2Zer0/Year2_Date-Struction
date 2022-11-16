#include<stdio.h>
#include<stdlib.h>
int Map[10][10] =
{
	1,1,1,1,1,1,1,1,1,1,
	1,0,0,1,0,0,0,1,0,1,
	1,0,0,1,0,0,0,1,0,1,
	1,0,0,0,0,1,1,0,0,1,
	1,0,1,1,1,0,0,0,0,1,
	1,0,0,0,1,0,0,0,0,1,
	1,0,1,0,0,0,1,0,0,1,
	1,0,1,1,1,0,1,1,0,1,
	1,1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1
};
int u;
int direct[4][2]= {{1,0},{0,1},{-1,0},{0,-1}};
typedef struct node {
	int x;
	int y;
	int dir;
} node;
typedef struct stack {
	node data[1024];
	int top;
} Stack;
Stack minstack;
void InitStack(Stack* stack);
void Push(Stack* stack, node cur);
int EmptyStack(Stack* stack);
void GetTop(Stack* stack, node* cur);
void PopStack(Stack* stack);

void  route_find(Stack* stack,node* cur)
{
	cur->x=1;
	cur->y=1;
	cur->dir = -1;
	Map[cur->x][cur->y] = -1;
	Push(stack,*cur);
	while(!EmptyStack(stack)){
		GetTop(stack,cur);
		if(cur->x==8&&cur->y==8){ //终点 
			if(stack->top<=minstack.top){
				for(int i = 0;i<stack->top;i++){
					minstack.data[i] = stack->data[i];
				}
				minstack.top = stack->top;
			}
			int i;
			printf("\n第%d条记录，长度为%d: ",++u,stack->top);
			for(i=0;i<stack->top;i++){
				printf("(%d,%d) ",stack->data[i].x,stack->data[i].y);
				if(i!=stack->top-1) printf(",");
				    else printf("\n");
			}
			Map[cur->x][cur->y] = 0;
			PopStack(stack);
		}
		else {
			int k;
			int temp_x,temp_y;

			for (k = cur->dir + 1; k < 4; k++)
			{
				temp_x = cur->x+direct[k][0];
				temp_y = cur->y+direct[k][1];
				if(temp_x >=1&&temp_x <=8&&temp_y>=1&&temp_y<=8&&Map[temp_x][temp_y] == 0){
			    	stack->data[stack->top-1].dir  = k;	
			    	cur->x = temp_x;
			    	cur->y = temp_y;
					Push(stack, *cur);
					stack->data[stack->top-1].dir  = -1;
					Map[cur->x][cur->y] = -1;
					break;
				}	
			}
			if(k==4){
				PopStack(stack);
				Map[cur->x][cur->y] = 0;		
			}
		}
	}	
	
}
int main(void) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	node* cur = (node*)malloc(sizeof(cur));
    minstack.top=1023;
    InitStack(stack);
    route_find(stack,cur);
    printf("最短路径为如下,长度为：%d\n",minstack.top);
    int i=0;
	for(;i<minstack.top;i++)
	    printf("(%d,%d) ",minstack.data[i].x,minstack.data[i].y);
}

void InitStack(Stack* stack) {
	(*stack).top = 0;
}

void Push(Stack* stack, node cur) {
	if ((*stack).top == 1023) exit(999);
	(*stack).data[(*stack).top] = cur;
	(*stack).top++;
}

int EmptyStack(Stack* stack) {
	if ((*stack).top == 0)
		return 1;
	return 0;
}

void GetTop(Stack* stack, node* cur) {
	*cur = (*stack).data[(*stack).top-1];
}

void PopStack(Stack* stack) {
	if ((*stack).top > -1)
		(*stack).top--;
	else exit(666);

}
