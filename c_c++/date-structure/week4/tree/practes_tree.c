#include<stdio.h>
#include<stdlib.h>
typedef int date_t;


typedef struct tree
{
	date_t date;
	struct tree *lchlden,*rchlden;
}tree;

tree *creat_tree(int i,int n)
{
	tree *root=(tree *)malloc(sizeof(tree));
	if(root==NULL)
		return NULL;
	root->date=i;
	if(2*i<=n)
		root->lchlden=creat_tree(2*i,n);
	else
		root->lchlden=NULL;
	if(2*i+1<=n)
		root->rchlden=creat_tree(2*i+1,n);
	else
		root->rchlden=NULL;
	return root;
}
//先续
int q_bianli(tree *root)
{
	if(NULL==root)
		return -1;
	printf("%d ",root->date);
	q_bianli(root->lchlden);
	q_bianli(root->rchlden);
}

int main()
{
	tree *root=creat_tree(1,12);
	q_bianli(root);
	printf("\n");
	return 0;
}
