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
		printf("1��ջ 2��ջ 3���� 4����\n������ѡ��");
		scanf("%d",&i);
		switch(i){
			case 1:
				if(s->top1+1==s->top2) exit(-1);			   
			    printf("����ջ1orջ2:");
			    scanf("%d",&stanum);
			    printf("���������ֵ��");
			    scanf("%d",&temp);
			    if(stanum==1)
			        s->data[++s->top1]=temp;
			        else s->data[--s->top2]=temp;
			        break;
			case 2:
				printf("����ջ1orջ2:");
	            scanf("%d",&stanum);
	            if(stanum==1&&s->top1!=-1) printf("����λ�ã�%d\n ɾ����ֵ��%d\n",s->top1,s->data[(s->top1)--]);
		        if(stanum==2&&s->top2!=maxsize-1) printf("����λ�ã�%d\n ɾ����ֵ��%d\n",s->top2,s->data[(s->top2)--]);
		        break;
		    case 3:
		    	for(k=s->top1;k!=-1;k--)
		    	printf("ջһλ�ã�%d\n ջһ��ֵ��%d\n",k,s->data[k]);
		    	for(k=s->top2;k!=maxsize-1;k++)
		        printf("ջ��λ�ã�%d\n ջ����ֵ��%d\n",k,s->data[k]);
		        break;
		    case 4:
		    	flag=1;break;
	      }   
	      if(flag==1) {free(s);break;}
	    }
}
