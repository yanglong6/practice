#include<iostream>
#define N 10
typedef int date_t;
using namespace std;

class queue
{
	public:
	queue()
	{
		date =new date_t [10];
		front=0;
		rear=0;
	}
	int empty()
	{
		return ((front==rear)?1:0);
	}
	int full()
	{
		if(rear>front)
			return ((rear-front==N-1)?1:0);
		if(rear<front)
			return ((front-rear==1)?1:0);
	}
	int in_queue(date_t a)
	{
		if(full()==1)
		{
			cout<<"queue full"<<endl;
			return -1;
		}
		date[rear]=a;
		rear=(rear+1)%N;
		return 0;
	}
	int out_queue()
	{
		if(empty()==1)
		{
			cout<<"queue empty"<<endl;
			return -1;
		}
		date_t d=date[front];
		front=(front+1)%N;
	}
	void printf_queue()
	{
		int tep=front;
		while(tep!=rear)
		{
			cout<<date[tep]<<" ";
			tep=(tep+1)%N;
		}
		cout<<endl;
	}
	private:
		date_t *date;
		int front;
		int rear;
};
int main()
{
	queue q;
	date_t i=1;
	while(i<10)
	{
		q.in_queue(i);
		i++;
	}
	q.printf_queue();
	i=0;
	while(i<2)
	{
		q.out_queue();
		i++;
	}
	i=8;
	while(i<10)
	{
		q.in_queue(i);
		i++;
	}
	q.printf_queue();
	return 0;
}
