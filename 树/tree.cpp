#include <stdio.h> //ABC  DE G   F    ²âÊÔ°¸Àı
#include <stdlib.h>
typedef struct Tree{
    char data;
    struct Tree *lChild,*rChild;
}TreeNode;
 
struct Tree * CreateTreeNode(char e){
    TreeNode *p = (TreeNode *) malloc(sizeof (TreeNode));
    p->data = e;
    p->lChild = NULL;
    p->rChild = NULL;
    return p;
}
 
TreeNode * CreateTree(){
    char c = (char )getchar();
    if(c == ' ')return NULL;
    TreeNode *res = CreateTreeNode(c);
 
    res->lChild = CreateTree();
    res->rChild = CreateTree();
    return res;
}
 
void dfs(TreeNode *p){
    if(!p)return;
    printf("%c ",p->data);
    dfs(p->lChild);
    dfs(p->rChild);
 
}
 
int main() {
    TreeNode* p = CreateTree();
    dfs(p);
    return 0;
}
