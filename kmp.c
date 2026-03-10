//0.注意下标开始是0还是1
//1.写好初始状态，next和l和r。
//2.进行最长相等前后缀的判断：若相等，lr同时偏移
//3.若不等，l回溯
#include<stdio.h>
#include<string.h>
void get_next(char T[],int next[]) //下标从1开始
{
	// 初始状态
	next[1] = 0;
	int l = 0;
	int r = 1;
	
	while(T[r]!='\0')
	{
		if(l==0||T[l]==T[r])	next[++r]=++l;
		else l=next[l];  
	}
}
void get_next_0(char T[],int next[]) //下标从0开始
{
	// 初始状态
	next[0] = -1;
	int l = -1;
	int r = 0;
	
	while(T[r]!='\0')
	{
		if(l==-1||T[l]==T[r])	next[++r]=++l;
		else l=next[l];  
	}	
}
void get_nextval_0(char T[], int nextval[]) {
    int len = strlen(T);
    int next[80]; // 先生成普通next数组
    get_next_0(T, next);
    
    // 初始化nextval[0]
    nextval[0] = -1;
    
    // 遍历生成nextval（下标1到len-1）
    for (int j = 1; j < len; j++) {
        // 关键判断：当前字符 和 回溯位置的字符是否相同
        if (T[j] == T[next[j]]) {
            nextval[j] = nextval[next[j]]; // 直接继承更优位置的nextval
        } else {
            nextval[j] = next[j]; // 不同则保留原next值
        }
    }

int kmp(char S[],char T[])
{
	int i=0,j=0;//遍历比较指针初始化,i属于主串 j属于模式串
	int next[80];
	get_next_0(T,next);
	while(S[i]!='\0'&&T[j]!='\0')
	{
		if(S[i]==T[j])
		{
			i++;j++;
		}
		else{   //字符匹配失败，只需让模式串回溯即可，主串仍然前进，直到主串末尾宣告失败
			j=next[j]; //kmp无需全部回溯
			if(j==-1){i++;j++;}//特殊情况：j回溯到-1（彻底无匹配）
			
		}
	}
	if(T[j]=='\0') return(i-strlen(T)+1); //+1表示位置从1开始计数
	else return 0;//失败返回0
}

int main()
{
	char s[30]="abzababcdcsdabc";
	char t[20]="ababcd";
	int res = kmp(s,t);
	printf("%d",res);
}

/*
0123456
 ababcd
 011231

公共前后缀隐藏的“套娃性”，也可以叫局部对称性:c处next[5] = 3 ,
所以d处发现前后缀不匹配，就要回溯到next[next[l]]处，即next[3]=1。
此时最长公共前缀："ab" →"a"。
如果仍然不匹配，就会变成:"a"→""(空) next[1]=0。

这个过程就像 “剥洋葱”：从最长的公共前后缀开始，
一层层往回找更短的，直到找到能匹配的，或回到 0（空前缀），这就是的 所谓的“套娃性”。


-ababcd
初始轮 l=0,r=1,next[1]=0
lr
 0
第一轮 符合l==0，整体后移next[2]=1;
 lr
 01
第二轮 不符合，走else，l回溯，l = next[l] = 0
l r
 01
第三轮 符合l==0，整体后移next[3]=1
 l r
 011
第四轮，符合T[1] == T[3] 即a==a，整体连续后移next[4]=2
  l r
 0112
第五轮，符合T[2] == T[4] 即b==b，整体连续后移next[5]=3
   l r
 01123
第六轮，不符合，T[3]a != T[5]c ,走else，l回溯，l = next[l] = 1处
 l   r
 01123
第七轮，不符合，T[1]a != T[5]c ,走else，l回溯，l = next[l] = 0处
l    r
 01123
第八轮，符合l==0，整体后移next[6]=1

得到最终next数组：
ababcd
011231
*/

