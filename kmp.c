//kmp
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>//ABACABC
 int * get_next(char* str) //ģʽ�������ĸ�λ�ú������Ƚ� 
 {
 	int *next = (int *)malloc(sizeof(int)*(strlen(str)+1));
 	int former,latter;
 	former = 0;//��Ȼǰ׺�Ǵ�ģʽ����0����ʼ����ôformer��ȻҪ��ͣ���� 
 	latter = 1;//��׺�᲻�Ϻ��ƣ������Ӵ��������� 
 	next[1]=0; //���ݳ�ʼ�㣨�ַ�����һ��Ԫ���±���0�� 
 	while(latter<strlen(str))   
	{ 
		if(str[former-1]==str[latter-1]||former==0) //��Ⱦͺ��� ���������Ϊformer=0ʱ�� 
		{
			former++; //former�ڵ�ǰλ����ȵ�����¼�һ����һ��ʼ�� 
			latter++; //latter��֮���ƣ�ֱ���Ӵ��յ� 
			//next[latter] = former; //�ں��ƹ����У�˳�����ǰ�±�ĵ�λ��ֵ 
			
			if(next[latter-1] !=  next[former-1]){
					}
			else next[latter-1] = next[former-1];

		}
		else
		{   
			former = next[former]; //ǰ��׺�ַ����Ⱦͻ���ǰ׺ 
		} 	
	} 
	
 	return next;
 } 
 
 int kmp(char* s1,char* s2,int pos)
 {
 	int mainstr_index = pos;
 	int substr_index = 1;
 	int* next = get_next(s2);

 	while(mainstr_index<=strlen(s1) && substr_index<=strlen(s2))
 	{
	 	if(substr_index==0||s1[mainstr_index-1]==s2[substr_index-1]){
		 	mainstr_index++;
		 	substr_index++;
		 }
		 else{
		 	substr_index = next[substr_index];
		 }
	}

 	if(substr_index > strlen(s2)){
	 	return mainstr_index-1 - strlen(s2) ;
	}
	else return -1;
 	
 }
 
int kmp1(char* S,char* T,int pos)
{
 	int* next = get_next(T);
	int i,j;
	i=pos;j=1;
	while(i<=(int)strlen(S)&&j<=(int)strlen(T)){
	if(j==0||S[i-1]==T[j-1]){
	  	i++;
	  	j++;
	  }
	else
	    j=next[j];
	
	}
	printf("%d \n",j);
	printf("%d \n",strlen(T));
	printf("%d \n",i);
	if(j>(int)strlen(T)) return i-(int)strlen(T) ;
	 else return -1;


}
 
 int main(void)
 {
 	char* s1 = (char*)malloc(sizeof(10));
	char* s2 = (char*)malloc(sizeof(10));
	s1 = "ABCABACABC";
	s2 = "ABC";
	int pos = kmp(s1,s2,3);
	printf("%d",pos);
 }
 
