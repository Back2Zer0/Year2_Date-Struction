//��̬����
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void) {
	typedef struct{
		int data;
		int cur;
	} component,slinklist[100];
	int i, K; slinklist link; srand(time(0));
//������
	for (i = 0; i < 100; i++) {
		link[i].cur = i + 1;
	}
	link[99].cur = 0;
	scanf("%d", &K);
	for (i = 1; i <= K; i++) { //����0�±괦����ͷָ�����ã�����ֵ
		link[i].data = rand()%100+1;
		}
		link[99].cur=1;
		link[0].cur=K+1;
		link[K].cur=0;
	
		for(i=link[99].cur;link[i].cur;i=link[i].cur){
			printf("%d ",link[i].data);
		}printf("%d",link[i].data);
//��̬������� 
int num,add;
printf("\n����λ���������ֵ:");
scanf("%d%d",&add,&num);
 int b,tail = link[0].cur;
 if(link[0].cur){                  //�����Ѿ��Ѻ�һ������λ�ø���0�� ���治Ҫ���� 
 	link[0].cur=link[tail].cur;
    } 	
    if(add<1||add>99) printf("��Чλ��");
	   else if(tail){ b=99;
	     	for(i=1;i<=add-1;i++){
		     	b=link[b].cur;
		     }
		    link[tail].data=num;
            link[tail].cur=link[b].cur;
			link[b].cur=tail;             //��������ָ���ͬС�� 
            
	   } 
    for(i=link[99].cur; link[i].cur;i=link[i].cur){
          printf("%d ", link[i].data);
	 }
	      printf("%d ", link[i].data);
//ɾ��Ԫ��
int k,del;
printf("����ɾ��Ԫ�ص�λ��"); 
scanf("%d",&del); 
k=99;
for(i=1;i<=k-1;i++){//��99��ʼ��ΪҪ�ӵ�һ����ЧԪ�ؿ�ʼ��ѭ������ɾ��Ԫ�ص�ǰһ�����е�ַ��� 
	k=link[k].cur;
}
del=link[k].cur;
link[k].cur=link[del].cur;
//��k����Ϊ����λ�ã�������µĿ���λ�ú���һ������������
link[del].cur=link[0].cur;
link[0].cur=del;
 
   for(i=link[99].cur; link[i].cur;i=link[i].cur){
          printf("%d ", link[i].data);
	 }
	      printf("%d ", link[i].data);
	      
int length=0,end=link[99].cur;
while(end){
	end=link[end].cur;
	length++;
}
printf("��ʱ��̬�����ܳ���Ϊ%d",length);
 
return 0;
}

struct dlinklist{
struct dlinklist *prior;
//elemtyep data;
struct dlinklist *next;
}
/*
��Ϊ���飬��̬�����һ��Ԫ��������ָ���ÿռ�ģ����һ��Ԫ��������ָ���һ��Ԫ�صģ�ͷ��㣩��

��̬������λ�õĽ������ùܵ�һ�ڶ�Ԫ�أ�����ֻ����ɾ�����½�(ʹ��һ�����ÿռ�)���������������ȡ��Ĺ����иı䡣

����̬����λ�ý���Ҳ��Ҫ���±��ָ��curŪ�졣�ڽ���λ��ʱ��curΪ˳��������±꣬�±������ʵ�ֹ���ʱ���ã�����˳����cur��ָ��

*/
