#include<stdio.h>
#include"linear.h"
int main()
{
	list *seqlist=creat_list();
	if(NULL==seqlist)
	{
		printf("malloc fail\n");
		return -1;
	}
	int i=0,ret;
	while(i<=10)
	{
	ret=insert(seqlist,i,i);
	i++;
	}
	 printlist(seqlist);
	 printf("sum=%d\n",leng(seqlist));
//	 delet_load(seqlist,4);
//	 printlist(seqlist);
	 delet_zhi(seqlist,9);
	 printlist(seqlist);
	 chang_load(seqlist,4,14);
	 printlist(seqlist);
	 chang_zhi(seqlist,7,17);
	 printlist(seqlist);
	return 0;
}
