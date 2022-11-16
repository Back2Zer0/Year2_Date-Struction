#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct c_stack
{
	char data[1024];
	int top;
}cstack;
typedef struct d_stack
{
	double data[1024];
	int top;
}dstack;
char Popc_stack(cstack* stack);
void Pushc_stack(cstack* stack,char c);
void Pushd_stack(dstack* stack,double d);
double Popd_stack(dstack* stack);
char getc_Top(cstack* cstack1);
int mathcal(int a, int b, char ch );
double calculate();
char cmp(char c1,char c2); 

double calculate()
{
	cstack* cstack1 = (cstack*)malloc(sizeof(cstack));
	dstack* dstack1 = (dstack*)malloc(sizeof(dstack));
	char *str = (char*)malloc(sizeof(char)*15);
	printf("���������ʽ����@��β��");
	scanf("%s",str);
	if(str[strlen(str)-1]!='@'){
		printf("����ʱ����ĩβ���@");
		exit(66);
	}

	Pushc_stack(cstack1,'@');
	
	int i = 0;
	int len = strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]>='0'&&str[i]<='9'){ //���� 
			int temp = i+1;	
			int val = str[i]-'0';
			int k=10;
		    while(str[temp]>='0'&&str[temp]<='9'){
				val+=k*(str[temp++]-'0');
				k*=10;
			}
			Pushd_stack(dstack1,val);
		}
	    else if(str[i]=='@'){
	    	char tempc;
			while((tempc = Popc_stack(cstack1))!='@'){
				int num1 = Popd_stack(dstack1);
				int num2 = Popd_stack(dstack1);
				Pushd_stack(dstack1,mathcal(num1,num2,tempc));
			}	
			return Popd_stack(dstack1);
			}
		else if(str[i]=='('){
			Pushc_stack(cstack1,'(');
		}
		else if(str[i]==')'){
			char tempc;
			while((tempc = Popc_stack(cstack1))!='('){
				int num1 = Popd_stack(dstack1);
				int num2 = Popd_stack(dstack1);
				Pushd_stack(dstack1,mathcal(num1,num2,tempc));
			}	
		}
		else{     //�Ӽ��˳� 
			if(cmp(getc_Top(cstack1),str[i])=='>'){
				int num1 = Popd_stack(dstack1);
				int num2 = Popd_stack(dstack1);
				Pushd_stack(dstack1,mathcal(num1,num2,Popc_stack(cstack1)));
				Pushc_stack(cstack1,str[i]);
				
			}
			else{
				Pushc_stack(cstack1,str[i]);
			}
		
	    }
	}
}

int main(void)
{
    int res = calculate();
	printf("%d",res);
}
char Popc_stack(cstack* stack)
{
	return stack->data[--stack->top]; 
}
void Pushc_stack(cstack* stack,char c)
{
	stack->data[stack->top] = c;
	stack->top++;
}
void Pushd_stack(dstack* stack,double d)
{
	stack->data[stack->top] = d;
	stack->top++;
}
double Popd_stack(dstack* stack)
{
	return stack->data[--stack->top];
}
char getc_Top(cstack* cstack1) //c1ջ�� c2ջ�� 
{
   return cstack1->data[cstack1->top-1];
}
char cmp(char in,char out) //1����վ 0����վ 
{    //(*/+-)#
	
	if(out=='#')
		return '>';
	
	if(in=='+'||in=='-'){
		if(out=='*'||out=='/'){
			return '<';
		}
		else return '>';
	}
	if (in=='*'||in=='/'){
		if(out=='+'||out=='-'){
			return '>';
		}
		else return '<';
	}	
}
int mathcal(int b, int a, char ch ){  //calculate������Ĳ������������� 
		if(ch == '+'){                //���ڳ�ջ˳�����ҵ�������������Ҫ�Ĳ���˳�� 
			return a+b;
		}
		if(ch == '-'){
			return a-b;
		}
		if(ch == '*'){
			return a*b;
		}
		if(ch == '/'){
			return a/b;
		}
}
