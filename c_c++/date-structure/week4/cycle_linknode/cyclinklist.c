#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int data_t;//给int取别名
struct student
{
	char name[10];
	int id;
	int score;
}

//定义节点类型
typedef struct node{

	struct student data;
	struct node *next;
}linklist;

//创建空链表
linklist *createLinklist()
{
	linklist *head = (linklist *)malloc(sizeof(linklist));
	if(NULL == head)
		return NULL;
//	head->data = -1;
	head->next = head;//构建单向循环链表
	
	return head;
}

int input_student(linklist *head)
{
	if(head==NULL)
		return 0;
	linklist *q=head->next
}

//判空
int linklist_is_empty(linklist *head)
{

	if(head != NULL)
		return ((head->next == head)?1:0);
	return -1;

}

//求链表中的节点个数
int getLengthLinklist(linklist *head)
{
	if(NULL == head)								
		return -1;
	int num = 0;
	linklist *p = head->next;
	while(p != head)
	{
		num++;
		p = p->next;
	}
	
	return num;
}


//按位置添加节点
int insertLinklistByPos(linklist *head, int pos, data_t data)
{
	if(NULL == head)
		return -1;
	//判断位置是否合法
	int len = getLengthLinklist(head);
	if(pos < 0 || pos > len )
		return -1;
	
	linklist *new = (linklist *)malloc(sizeof(linklist));//创建新节点
	if(new == NULL)
		return -1;
	new->data = data;
	new->next = NULL;


	linklist *p = head;
	//找到要插入节点位置的前一个位置
	while(pos--)//pos从0开始
		p = p->next;//p指向插入位置的前一个位置节点

	//将新节点插入到链表中

	new->next = p->next;
	p->next = new;

	return 0;

}

//按位置删除链表节点
int deleteLinklistByPos(linklist *head, int pos)
{
	if(NULL == head)
		return -1;

	int len = getLengthLinklist(head);

	//判断位置是否有效
	if(pos < 0 || pos > len-1 )
		return -1;
	//判断链表是否为空
	linklist_is_empty(head);
	//删除pos位置的节点
	linklist *p = head;
	while(pos--) //得到pos-1位置  pos从0开始
		p = p->next;

	linklist *q = p->next;
	p->next = q->next;
	free(q);
	q = NULL;
	
	return 0;

}
//按值删除链表中节点
int deleteLinklistByData(linklist *head, data_t data)
{




}

//按位置查找节点，返回节点的地址
linklist *findLinklistByPos(linklist *head, int pos)
{
	if(NULL == head)
		return NULL;
	int len = getLengthLinklist(head);
	//判断位置是否有效
	if(pos < 0 || pos > len-1)
		return NULL;
#if 0
	linklist *p = head;
	while(pos--)
		p = p->next;

	return (p->next);
#endif
	linklist *p = head->next;
	while(pos--)
		p = p->next;

	return p;
	
}

//按值查找节点，返回节点的地址
linklist *findLinklistByData(linklist *head, data_t data)
{
	if(NULL == head)
		return NULL;

	linklist *p = head->next;
	while(p != head)
	{
		if(p->data == data)
			return p;
		else
			p = p->next;
	}


	return NULL;

}
//按位置修改链表节点的值
int changeLinklistByPos(linklist *head, int pos, data_t data)
{
	if(NULL == head)
		return -1;
	linklist * p = findLinklistByPos(head, pos);
	if(NULL == p)
		return -1;
	p->data = data;

	return 0;
}
//按值修改链表中节点的值
int changeLinklistByData(linklist *head, data_t old, data_t new)
{



}

//删除链表中的所有有效节点
void clearLinklist(linklist *head)
{
	if(head == NULL)
		return ;
	linklist *p = head->next;
	linklist *q = NULL;
	while(p != head)
	{
		q = p->next;
		free(p);
		p = NULL;
		p = q;
	}

	return;
}


//销毁链表
void destoryLinklist(linklist **head)
{

	if(NULL == head)
		return;

	clearLinklist(*head);
	free(*head);
	*head = NULL;

	return;
}




void printLinklist(linklist *head)
{
	if(NULL == head)
		return;
	linklist *p = head->next;
	while(p != head)
	{
		printf("%d ",p->data);
		p = p->next;

	}
	printf("\n");	

	return ;

}


int main()
{
	linklist *head = createLinklist();
	if(NULL == head)
	{
		printf("malloc failed\n");
		return -1;
	}
	int len = getLengthLinklist(head);
	printf("len=%d\n",len);
	
	int i = 0,ret;
	while(i <= 10)
	{
		ret = insertLinklistByPos(head, i,i);
		i++;
	}
	len = getLengthLinklist(head);
	printf("len=%d\n",len);

	printLinklist(head);

	i = 0;
	while(i<5)
	{
		deleteLinklistByPos(head, 0);
		i++;
	}

	printLinklist(head);

	linklist *p = findLinklistByData(head, 9);
	if(p == NULL)
	{
		printf("No find data\n");
		return -1;
	}
	printf("p->data=%d\n",p->data);

	p = findLinklistByPos(head, 2);
	if(p == NULL)
	{
		printf("pos invalid\n");
		return -1;
	}
	printf("p->data=%d\n",p->data);

	changeLinklistByPos(head, 5, 50);
	printLinklist(head);


	 destoryLinklist(&head);
	return 0;
}
