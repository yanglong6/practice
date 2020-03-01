#include<iostream>
#include<cstring>
using namespace std;

class arry
{
	public:
		void leng(int n,int *a);
		void date_out();
	    void date_in();
		void sort();
		void revers();
	private:
		int N;
		int *a;

};

int main()
{
	arry a;
	int N;
	cin>>N;
	int *q=new int [N];
	a.leng(N,q);
	a.date_in();
	a.date_out();
	a.sort();
	a.date_out();
	a.revers();
	a.date_out();
	return 0;
}
void arry::leng(int N,int *q)
{
	this->N=N;
	a=q;
}
void arry::date_in()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		j=0;
		cin>>j;
		*(a+i)=j;
	}
}
void arry::date_out()
{
	int i;
	for(i=0;i<N;i++)
	{
		cout<<*(a+i)<<" ";
	}
	cout<<endl;
}
void arry::sort()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				a[i]=a[j]^a[j+1];
				a[j+1]=a[j]^a[j+1];
				a[i]=a[j]^a[j+1];
			}
		}
	}
}
void arry::revers()
{
	int i,j;
	for(i=0;i<N/2;i++)
	{
		a[i]=a[i]^a[N-1-i];
		a[N-1-i]=a[i]^a[N-1-i];
		a[i]=a[i]^a[N-1-i];
	}
}

