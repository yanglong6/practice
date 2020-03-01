#include<iostream>
#include"stu.h"
using namespace std;
A::A()
{
	last=0;
}

void A::set(int date)
{
	a[last]=date;
	this->last++;
}

int & A::get(int id)
{
	return a[id];
}

void A::show()
{
	int i=0;
	for(i=0;i<last;i++)
	cout<<i<<":"<<a[i]<<"  ";
	cout<<endl;
}
int A::relast()
{
	return this->last;
}

