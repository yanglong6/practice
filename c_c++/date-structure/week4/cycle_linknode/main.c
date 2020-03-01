#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"linknode.h"

int main()
{
	lnode *q=creat_list();
	if(q==NULL)
	{
		printf("malloc fail\n");
	}
	int i=0,ret;
	while(i<10)
	{
	ret=addnode_load(q,i,i);
	i++;
	}
	printf_node(q);

	printf("num=%d\n",len(q));

	delete_load(q,8);
	printf_node(q);

	lnode *p=find_load(q,2);
	printf("p->date=%d\n",p->date);

	p=find_date(q,7);
	printf("%d\n",p->date);

	delete_date(q,7);
	printf_node(q);

	change_load(q,2,66);
	printf_node(q);

	change_date(q,9,77);
	printf_node(q);

	clear(q);
//	printf_node(q);

	distroy(&q);
	return 0;
}
