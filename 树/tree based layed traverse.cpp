#include<iostream>
#include<queue>
#include<stack>
using namespace std;
typedef struct ABCD
{
	char data;
	struct ABCD* lchild;
	struct ABCD* rchild;
} treenode;
typedef struct EFGH
{
	int leavecount;
	int twocount;
} counts;

void layer_create(treenode*& root,deque<treenode**>& q);
int layer_traverse(treenode*& root,deque<treenode**>& q);

void in_order(treenode* rode);
void pre_order(treenode* rode);
void post_order(treenode* T);
void iter_pre_order(treenode* T);
void iter_post_order(treenode* T);

int depth_max(treenode* node,int deep);
int location(treenode* node, char data, int deep);
void treeleaves(treenode* root,counts& c);

int main(void)
{  
	int x=0;
	treenode* root = NULL;
	deque<treenode**> q;
	printf("1.层次创建树(重复创建会覆盖),#为空 @结束输入\n");
	printf("2.层次遍历树并输出最大宽度\n");
	printf("3.搜索特定结点\n");
	printf("4.输出该树的深度\n");
	printf("5.前序遍历\n");
	printf("6.中序遍历\n");
	printf("7.后序遍历\n");
	printf("8.获取叶子节点个数\n"); 
	while(x!=-1)
	{
		printf("输入指令号："); 
		scanf("%d",&x);
		switch(x)
		{
			case 1:{
				layer_create(root,q);
				break;
			}
			case 2:{
				printf("\n最大宽度：%d\n",layer_traverse(root,q));
			
				break;
			}
			case 3:{
				fflush(stdin);
				char n;scanf("%c",&n);
				int res = location(root,n,1);
				if(res!=-1)
					printf("该结点所在层次：%d\n",res);
				else 
					printf("该结点不存在\n");
				break;
			}
			case 4:{
				printf("该树的深度：%d\n",depth_max(root,0));
				break;
			}
			case 5:{
				char a;
				printf("a.迭代遍历\nb.递归遍历\n请输入：");
				cin>>a;
				if(a=='a') iter_pre_order(root);
				else if(a=='b') pre_order(root);
					else printf("输错了\n");
				
				printf("\n");
				break;
			}
			case 6:{
				in_order(root);
				printf("\n");
				break;
			}
			case 7:{
				char a;
				printf("a.迭代遍历\nb.递归遍历\n请输入：");
				cin>>a;
				if(a=='a') iter_post_order(root);
				else if(a=='b')	post_order(root); 
					else printf("输错了\n");
		
				printf("\n");
				break;
			}
			case 8:{
				counts c;
				c.leavecount = 0;
				c.twocount = 0;
				treeleaves(root,c);
				printf("叶子结点：%d\n度为2的结点:%d\n",c.leavecount,c.twocount);
				break;
			}
			default:{
				printf("无效输入\n");
				break;
			}
		}
	}
	
}

void layer_create(treenode*& root,deque<treenode**>& q)
{
	q.push_front(&root);
	while(!q.empty())
	{
		treenode*& new_node = *q.front();
		char data;
		cin>>data;
		if(data=='@') break;
		if(data=='#'){
			new_node = NULL;
		}
		else {
			new_node = new treenode;
			new_node->data = data;
			q.push_back(&(new_node->lchild));
			q.push_back(&(new_node->rchild));
		}
		q.pop_front();
	}
	while(!q.empty())
	{
		treenode*& new_node = *q.front();
		new_node = NULL;
		q.pop_front();
	}
}
int layer_traverse(treenode*& root,deque<treenode**>& q) 
{
	if(root == NULL){
		return -1;
	}
	int max_width = 0;
	q.push_front(&root);
	while(!q.empty())
	{
		int width = q.size();
		for(int i = 0;i<width;i++)
		{
			treenode*& new_node = *q.front();
			q.pop_front();
			if(new_node==NULL) continue;
			else printf("%c ",new_node->data);
			if(new_node->lchild) q.push_back(&new_node->lchild);
			if(new_node->rchild) q.push_back(&new_node->rchild);
		}
		max_width = width > max_width ? width:max_width;
	}
	return max_width;
}

int depth_max(treenode* node,int deep)
{
	if(node==NULL) return deep;
	int num1 = depth_max(node->lchild,deep+1);
	int num2 = depth_max(node->rchild,deep+1);
	return num1>num2?num1:num2;
}
int location(treenode* node, char data, int deep)
{
	if(node == NULL)
		return -1;
	
	if(node->data == data)
		return deep; 
	
	int num1 = location(node->lchild, data, deep + 1);
	int num2 = location(node->rchild, data, deep + 1);

	if(num1 == -1&&num2 ==-1) return -1; 
	if(num1!=-1) return num1;
	if(num2!=-1) return num2;
}

void in_order(treenode* rode)
{
	if(rode == NULL) return ;
	in_order(rode->lchild);
	cout<<rode->data<<" ";
	in_order(rode->rchild);	
	
};


void pre_order(treenode* rode)
{
	if(rode == NULL) return ;
	cout<<rode->data<<" ";
	pre_order(rode->lchild);
	pre_order(rode->rchild);
	
};


void iter_post_order(treenode* T)
{
	if (T==NULL) {
		printf("空树");
		return ;
	}
	
	stack<treenode*> stack1;
	stack<treenode*> stack2;
	stack1.push(T);
	while(!stack1.empty())
	{
		treenode* new_node = stack1.top();
		stack1.pop();
		stack2.push(new_node);
		if(new_node->lchild) stack1.push(new_node->lchild);
		if(new_node->rchild) stack1.push(new_node->rchild);
	}
	while(!stack2.empty())
	{
		cout<<stack2.top()->data<<" ";
		stack2.pop();
	}
};

void iter_pre_order(treenode* T)
{
	if (T==NULL) {
		printf("空树");
		return ;
	}
	stack<treenode*> stack1;
	stack1.push(T);
	while(!stack1.empty())
	{
		treenode* new_node = stack1.top();
		cout<<new_node->data<<" ";
		stack1.pop();
		if(new_node->lchild) stack1.push(new_node->lchild);
		if(new_node->lchild) stack1.push(new_node->rchild);
	}
}

void post_order(treenode* T)
{
	if (T==NULL) {
		return ;
	}
	post_order(T->lchild);
	post_order(T->rchild);
	cout<<T->data<<" ";
}

void treeleaves(treenode* root,counts& c){
	if(root == NULL){
		return ;
	}
	if(root->lchild == NULL && root->rchild == NULL){
		c.leavecount++;
	}
	if(root->lchild != NULL && root->rchild != NULL){
		c.twocount++;
	}
	treeleaves(root->lchild,c);
	treeleaves(root->rchild,c);
}
