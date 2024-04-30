#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	struct queue{
		int data;
		struct queue *next;
	}*s,*front,*rear,*p;
	int num,n,count=0;
	
	s=(struct queue*)malloc(sizeof(struct queue));
	front=s;
	rear=s;
	while(1){
		scanf("%d",&n);
	    switch (n) {
		    case 1:
			    p=(struct queue*)malloc(sizeof(struct queue));
				scanf("%d",&num);
				p->data=num;
				p->next=NULL;
			    rear->next=p;
			    rear=p;
			
			    break;
		    case 2:
		    	p=front->next;
		    	front->next=p->next;
		    	printf("É¾³ýÊý¾Ý£º%d\n",p->data);
		    	free(p);
			    break;
		    case 3:
			    for(p=front->next;p!=NULL;p=p->next)
			    printf("%d\n",p->data);
			    
			    break;
			case 4:
			     for(p=front->next;p!=NULL;p=p->next)
				 count++;	
				break;
	    }	    
	}
	
	
}
