#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    struct quene{
   	int front;
   	int rear;
   	int data[5];
   }s;
    s.front=0;
    s.rear=0;
	
	int n,num,temp;
	printf("1入列 2出列 3遍历 4长度 \n");
	while(1){
	  scanf("%d",&n);
	  switch(n){
	   	case 1: //if((s.rear-s.front+5)%5==5) exit(-1);
	   	        if((s.rear+1)%5==s.front) exit(-1);
	   	        printf("入列位置：%d 输入数据:\n",s.rear);
	   	        scanf("%d",&num);
	   	        s.data[s.rear]=num;
	   	        if(s.rear==4) s.rear=0; //s.rear=(s.rear+1)%5;
	   	           else s.rear=s.rear+1;
	   	        
	   	        break;
			
		case 2:
			    if(s.rear==s.front) exit(-2);
			    printf("出列位置：%d 出列数据%d\n",s.front,s.data[s.rear-1]);
	   	        if(s.front==5-1) s.front=0;//s.front(s.front+1)%5;
	   	           else s.front=s.front+1;
	   	        break;
			    
	    case 3: 
	            temp=s.front;
	    	    while((s.rear)%5!=s.front){
	    	    	printf("数组位置：%d 队列数据：%d\n",s.front,s.data[s.front++]);
	    	        if(s.front==4) s.front = 0;
	            }
	    	    s.front=temp;
	    	    break;
	    case 4:
	    	printf("队列长度为%d",(s.rear-s.front+5)%5);
	    	break;
		
	  }  
	
	}
	
}
