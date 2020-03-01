#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int date_t;
typedef struct tree
{
	date_t date;
	struct tree *lson,*rson;
}tree;

//创建树
//i:节点编号
//n:总的节点数
tree *creat_tree(int i,int n)
{
	tree *root=(tree *)malloc(sizeof(tree));
	if(NULL==root)
		return NULL;
	root->date=i;
	if(2*i<=n)
		root->lson=creat_tree(2*i,n);
	else
		root->lson=NULL;
	if(2*i+1<=n)
		root->rson=creat_tree(2*i+1,n);
	else
		root->rson=NULL;
	return root;
}

//先序遍历
int q_bianli(tree *root)
{
	if(NULL==root)
		return -1;
	printf("%d ",root->date);
	q_bianli(root->lson);
	q_bianli(root->rson);
	return 0;
}

//中序遍历
int z_bianli(tree *root)
{
	if(NULL==root)
		return -1;
	z_bianli(root->lson);
	printf("%d ",root->date);
	z_bianli(root->rson);
	return 0;
}

//后续遍历
int h_bianli(tree *root)
{
	if(NULL==root)
		return -1;
	h_bianli(root->lson);
	h_bianli(root->rson);
	printf("%d ",root->date);
	return 0;
}
int main()
{
	tree *root=creat_tree(1,12);
	if(root==NULL)
		printf("malloc fail\n");
	q_bianli(root);
	printf("\n");
	z_bianli(root);
	printf("\n");
	h_bianli(root);
	printf("\n");

	return 0;
}
