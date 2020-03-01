#include<iostream>
#include<cstring>
#include<stdlib.h>

using namespace std;

class arry
{
	public:
		arry(int N=0)
		{
			this->N=N;
			q=new int [N];
		}
		~arry()
		{
			delete [] q;
		}
		void date_in()
		{
			int i,j;
			for(i=0;i<N;i++)
			{
				cout<<"第"<<i<<"个数据"<<endl;
				cin>>j;
				q[i]=j;
			}
		}

		void date_out()
		{
			int i;
			for(i=0;i<N;i++)
			{
				cout<<q[i]<<" ";
			}
			cout<<endl;
		}
		arry operator+(const arry &obj)
		{
			arry tep;
			int i;
			for(i=0;i<N;i++)
			{
				tep.q[i]=this->q[i]+obj.q[i];
			}
			return tep;
		}
		int & operator[](int id)
		{
		try{
			if(id<0||id>N)
			{
			//	return -1;
			throw -1;
			}
		}catch(int)
			{
				cerr<<"error put"<<endl;
				exit(1);
			}
			int i=0;
			for(i=0;i<N;i++)
			{
				if(i==id)
				{
					return q[i];
				}
			}
		}
		
		arry & operator=(const arry &obj)
		{
			int i;
			for(i=0;i<N;i++)
			{
				this->q[i]=obj.q[i];
			}
			return *this;
		}
		
	private:
		int N;
		int *q;
};

int main()
{
	int N;
	cout<<"put arry leng:";
	cin>>N;
	arry a(N);

	a.date_in();
	a.date_out();
	arry b(N);

	b.date_in();
	b.date_out();

	arry c(N);

	c=a+b;
	c.date_out();

	b[100]=200;
	b.date_out();
}
