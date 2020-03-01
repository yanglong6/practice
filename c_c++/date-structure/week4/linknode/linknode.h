#ifndef LINKNODE_H
#define LINKNODE_H

typedef int date_t;
typedef struct linknode
{
	date_t date;
	struct linknode *next;
}lnode;

lnode *creat_list();
int empty(lnode *head);
int len(lnode *head);
int addnode_load(lnode *head,int pos,date_t date);
lnode *find_load(lnode *head,int pos);
lnode *find_date(lnode *head,int date);
int delete_load(lnode *head,int pos);
int delete_date(lnode *head,date_t date);
int change_load(lnode *head,int pos,date_t new);
int change_date(lnode *head,date_t old,date_t new);
int clear(lnode *head);
int distroy(lnode **head);
void printf_node(lnode *head);
#endif
