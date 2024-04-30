#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
int main(void)
{
	struct stack{
		int data[maxsize];
		int top1;
		int top2;
	}*s;
	typedef struct stack node;
	int i,k,temp,stanum,flag=0;
	s=(node*)malloc(sizeof(node));
    
    s->top1=-1;
    s->top2=maxsize-1;
	while(1){
		printf("1入栈 2弹栈 3遍历 4结束\n请输入选择：");
		scanf("%d",&i);
		switch(i){
			case 1:
				if(s->top1+1==s->top2) exit(-1);			   
			    printf("插入栈1or栈2:");
			    scanf("%d",&stanum);
			    printf("输入插入数值：");
			    scanf("%d",&temp);
			    if(stanum==1)
			        s->data[++s->top1]=temp;
			        else s->data[--s->top2]=temp;
			        break;
			case 2:
				printf("弹出栈1or栈2:");
	            scanf("%d",&stanum);
	            if(stanum==1&&s->top1!=-1) printf("弹出位置：%d\n 删除数值：%d\n",s->top1,s->data[(s->top1)--]);
		        if(stanum==2&&s->top2!=maxsize-1) printf("弹出位置：%d\n 删除数值：%d\n",s->top2,s->data[(s->top2)--]);
		        break;
		    case 3:
		    	for(k=s->top1;k!=-1;k--)
		    	printf("栈一位置：%d\n 栈一数值：%d\n",k,s->data[k]);
		    	for(k=s->top2;k!=maxsize-1;k++)
		        printf("栈二位置：%d\n 栈二数值：%d\n",k,s->data[k]);
		        break;
		    case 4:
		    	flag=1;break;
	      }   
	      if(flag==1) {free(s);break;}
	    }
}
