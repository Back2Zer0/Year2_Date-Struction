//静态链表
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
	int data;
	int cur;
} component,slinklist[100];
void print(slinklist link)
{
	int i;
    for(i=link[99].cur; link[i].cur;i=link[i].cur){
        printf("%d ", link[i].data);
	}
	    printf("%d ", link[i].data);
}
void InitLink(slinklist &link)
{
//链表创建
	int i, K;
	srand(time(0));
	for (i = 0; i < 100; i++) {
		link[i].cur = i + 1;
	}
	link[99].cur = 0;
	scanf("%d", &K);
	for (i = 1; i <= K; i++) { //由于0下标处仅作头指针作用，不赋值
		link[i].data = rand()%100+1;
		}
		link[99].cur=1;
		link[0].cur=K+1;
		link[K].cur=0;
	
		print(link);
	
}
void InsertLink(slinklist& link)
{
//静态链表插入 
int num,add,i;
printf("\n插入位置与插入数值:");
scanf("%d%d",&add,&num);
 int b,tail = link[0].cur;
 if(link[0].cur){                  //这里已经把后一个空闲位置赋给0了 后面不要担心 
 	link[0].cur=link[tail].cur;
    } 	
    if(add<1||add>99) printf("无效位置");
	   else if(tail){ b=99;
	     	for(int i=1;i<=add-1;i++){
		     	b=link[b].cur;
		     }
		    link[tail].data=num;
            link[tail].cur=link[b].cur;
			link[b].cur=tail;             //这两步和指针大同小异 
            
	   } 
    print(link);
   
}
void DeleteNode(slinklist& link)
{
	//删除元素
	int k,i,del;
	printf("输入删除元素的位置"); 
	scanf("%d",&del); 
	k=99;
	for(i=1;i<=del-1;i++){//从99开始因为要从第一个有效元素开始。循环是找删除元素的前一个进行地址替代 
		k=link[k].cur;
	}
	del=link[k].cur;
	link[k].cur=link[del].cur;
	//把k降格为空闲位置，将这个新的空闲位置和下一个连接起来。
	link[del].cur=link[0].cur;
	link[0].cur=del;
	print(link);
	
}
int main(void) {
	slinklist link; 
	InitLink(link);
	InsertLink(link);
	DeleteNode(link);

	int length=0,end=link[99].cur;
	while(end){
		end=link[end].cur;
		length++;
	}
	printf("此时静态链表总长度为%d",length);
	 
	return 0;
}
