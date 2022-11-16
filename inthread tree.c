//线索二叉树

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode 
{
	char data;
	struct treenode* lchild;
	struct treenode* rchild;
	int lflag;
	int rflag;
}tree;
tree* pre;
void init_tree(tree** T)
{
//AB#D##C##
	char ch=(char)getchar();
	if(ch=='#') *T = NULL;
	else{
		(*T) = (tree*)malloc(sizeof(tree));
		(*T)->lflag = 0;
		(*T)->rflag = 0; 
		(*T)->data = ch;
		init_tree(&((*T)->lchild));
		init_tree(&((*T)->rchild));
	}


}
void inthread(tree* T,tree* minus)
{
	if(T!=NULL)
	{
		inthread(T->lchild,minus);
		if(!T->lchild)
		{
			T->lflag = 1;
			T->lchild = pre;
		}
		if(!pre->rchild&& pre!=minus) //跟头结点没什么关系。。。 
		{
			pre->rflag = 1;
			pre->rchild = T;
		}
		if(T!=minus) 
		{
			pre = T;
		}
				if(T!=minus)
				printf("%c , pre:%c\n",T->data,(pre)->data);
				else printf("Box\n");
		inthread(T->rchild,minus);
	}
	if(T==minus&& pre!=minus) //仅仅针对一种情况：线索化遍历到最后，也就是回到头结点时 
	{
		T->rchild = pre;
		T->rflag = 1;
	}
}
void dfs(tree* T,tree* minus)
{
	if(T==NULL) return ;
	if(!T->lflag)dfs(T->lchild,minus);
	if(T!=minus)printf("node：%c - ",T->data);
	else printf("node:box - ");
	
	if(T->lchild!=minus) printf("left:%c",T->lchild->data);
	else printf("left = box");
	
	if(T->rchild!=minus) printf(" right:%c\n",T->rchild->data);
	else printf("right = box\n");
	if(!T->rflag)dfs(T->rchild,minus);
	
}
void test()
{//AB#D##C##
	tree* box = (tree*)malloc(sizeof(tree));
	box->lflag = box->rflag = 0;
	box->rchild = NULL;
	pre = box;
	init_tree(&box->lchild);
	inthread(box,box);
	dfs(box,box);
	
}
int main(void)
{
	test();
	return 0;
}
void iter_dfs(tree* T){
	tree*p;
	p=T->lchild;
	while(p!=T){ 
	    while(!p->lflag) p=p->lchild;
	    printf("%c ",p->data);
	    while(p->rflag&&p->rchild!=T){
			p=p->rchild;
	    	printf("%c ",p->data);
		}
		p=p->rchild;
	}
}
void allin(tree* T,tree* box){
    if(T==box) while(!T->lflag) T=T->lchild;
	if(T->rchild==box){
		free (T->rchild);	
	    free (T);
		T=box=NULL;
	}
        else if(T->rchild){
			allin(T->rchild,box);
			free (T);
			T=NULL;
        }
		    else free (box); 
			//正常情况右孩子是一定存在的，除非是空树 
}
