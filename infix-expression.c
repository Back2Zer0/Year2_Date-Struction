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
	printf("输入计算表达式（以@结尾）");
	scanf("%s",str);
	if(str[strlen(str)-1]!='@'){
		printf("输入时请在末尾添加@");
		exit(66);
	}

	Pushc_stack(cstack1,'@');
	
	int i = 0;
	int len = strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]>='0'&&str[i]<='9'){ //数字 
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
		else{     //加减乘除 
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
char getc_Top(cstack* cstack1) //c1栈内 c2栈外 
{
   return cstack1->data[cstack1->top-1];
}
char cmp(char in,char out) //1先入站 0后入站 
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
int mathcal(int b, int a, char ch ){  //calculate函数里的参数运算是左到右 
		if(ch == '+'){                //由于出栈顺序是右到左，所以这里需要改参数顺序 
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
