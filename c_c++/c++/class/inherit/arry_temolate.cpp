#include<iostream>
#include<cstring>
using namespace std;
class A;

template <typename T>
class arry
{
	public:
		arry(int N=0)
		{
			this->N=N;
			a=new T [this->N+1];
			
		}
	
		~arry()
		{
			delete  [] a;
		}
	
		void date_in()
		{
			int i;
			T j;
			for(i=0;i<N;i++)
			{
				cin>>j;
				*(a+i)=j;
			}
		}
			
		void date_out()
		{
			int i;
			for(i=0;i<N;i++)
			{
				cout<<a[i]<<" ";
			}
			cout<<endl;
		}
		void sort()
		{
			int i,j;
			T tep;
			for(i=0;i<N-1;i++)
			{
				for(j=0;j<N-i-1;j++)
				{
					if(a[j]>a[j+1])
					{
						tep=a[j];
						a[j]=a[j+1];
						a[j+1]=tep;

					}
				}
			}
		}
		
		void revers()
		{
			int i,j;
			T *p=a;
			T *q=a+N-1;
			T tep;
			for(i=0;i<N/2;i++)
			{
				tep=*q;
				*q=*p;
				*p=tep;
				p++;
				q--;
			}
		}
	
	private:
		int N;
		T *a;
	

};

class A
{
	public:
		A(int a=0,int b=0)
		{
			x=a;
			y=b;
		}
	bool operator>(A &obj)
	{
		return ((x+y)>(obj.x+obj.y)?true:false);
	}
	friend istream & operator>>(istream &in,A &obj);
	friend ostream & operator<<(ostream &out,A &obj);
	private:
		int x,y;
};

	istream & operator>>(istream &in,A &obj)
{
	cout<<"x=";
	in>>obj.x;
	cout<<"y=";
	in>>obj.y;
	return in;
}
	ostream & operator<<(ostream &out,A &obj)
{
	out<<"["<<obj.x<<","<<obj.y<<"]";
	return out;
}


int main()
{
#if 0
	int N;
	cout<<"put arry leng:";
	cin>>N;
	arry <A> a(N);
	//arry <string> a(N);
	a.date_in();
	a.date_out();

	a.sort();
	a.date_out();

	a.revers();
	a.date_out();
#endif
	A a(4,4);
	A b(4,3);
	cout<<(a>b)<<endl;
	return 0;
}

