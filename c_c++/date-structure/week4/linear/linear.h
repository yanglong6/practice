#ifndef LINEAR_H
#define LINEAR_H
#define SIZE  64

typedef struct linear
{
	int date[SIZE];
	int last;
}list;
list *creat_list();

int full(list *seq);
int empty(list *seq);
int leng(list *seq);
int insert(list *seq,int poe,int date);
int printlist(list *seq);
int delet_load(list *seq,int poe);
int find(list *seq,int date);
int delet_zhi(list *seq,int date);
int chang_load(list *seq,int poe,int date);
int chang_zhi(list *seq,int old,int new);
#endif
