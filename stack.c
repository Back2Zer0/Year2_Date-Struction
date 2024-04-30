#include<stdio.h>
#include<stdlib.h>
int main(void)
{
  struct stack{          //元素形式+连接 
  	int data;
  	struct stack *next;
  }*p1,*pp;
  struct linkstack{        //栈链表 
  	struct stack *top;
  	int count;
  }*s;
    int i,a,k=0; 
    s=(struct linkstack*)malloc(sizeof(struct linkstack));
    s->top=NULL;
    s->count=0;
    while(1){
    	printf("1入栈2弹栈3遍历4清空\n请输入选择：");
    	scanf("%d",&i);
		switch(i){
			case 1:
				p1=(struct stack*)malloc(sizeof(struct stack));
				scanf("%d",&a);
				p1->data=a;
				p1->next=s->top;
				s->top=p1;
				s->count++;
				break;
			case 2: //下面两种弹栈方法大同小异。 
				p1=s->top;
				s->top=s->top->next;
				free(p1);
				s->count--;
				break;
			/*	s->top=p1->next;                        
				free(p1);
				p1=s->top;
				s->count--;
				break;*/
		    case 3:
				for(pp=s->top;pp!=NULL;pp=pp->next) {
				 	printf("位置：%d  栈值：%d\n ",s->count-k++,pp->data);
				    }
				k=0;
				break;
			case 4:
				pp=s->top;
				while(pp!=NULL){
					s->top=s->top->next;
					free(pp);
					pp=s->top;
				}
				break;
		}
	}
	
}
