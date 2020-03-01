#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct student
{
	int id;
	char name[32];
	int score;
}student;

//学生信息输入
int cin_msg(student *st,int n)
{
	int id=0;
	int score=0;
	char name[32]={0};
	int i;
	for(i=0;i<n;i++)
	{
		cout<<"id:"<<" name"<<" score"<<endl;
		cin>>id>>name>>score;
		st[i].id=id;
		strcpy(st[i].name,name);
		st[i].score=score;
	}
}

//排名输出
int out_score(student *st,int n)
{
	int i,j=1;
	for(i=0;i<n;i++)
	{
		cout<<j<<":"<<st[i].id<<" "<<st[i].name<<" "<<st[i].score<<endl;
		j++;
	}
}

//按成绩排名
int sort_score(student *st,int n)
{
	int i,j;
	student tep;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n-i;j++)
		{
			if(st[i].score<st[j].score)
			{
				tep=st[i];
				st[i]=st[j];
				st[j]=tep;
			}
		}
	}
	return 0;
}
int main()
{
	int n;
	cout<<"学生人数"<<endl;
	cin>>n;
	student st[n];
	cin_msg(st,n);
	sort_score(st,n);
	cout<<"score sort"<<endl;
	out_score(st,n);
	return 0;
}
