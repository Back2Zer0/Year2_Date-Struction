#include<stdio.h>
#include<stdlib.h>
int main(void)
{
  struct stack{          //Ԫ����ʽ+���� 
  	int data;
  	struct stack *next;
  }*p1,*pp;
  struct linkstack{        //ջ���� 
  	struct stack *top;
  	int count;
  }*s;
    int i,a,k=0; 
    s=(struct linkstack*)malloc(sizeof(struct linkstack));
    s->top=NULL;
    s->count=0;
    while(1){
    	printf("1��ջ2��ջ3����4���\n������ѡ��");
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
			case 2: //�������ֵ�ջ������ͬС�졣 
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
				 	printf("λ�ã�%d  ջֵ��%d\n ",s->count-k++,pp->data);
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
