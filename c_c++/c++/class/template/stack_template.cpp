#include<iostream>

//#define N 20
using namespace std;
//typedef int date_t;
template <typename T,int N=20>
class stack
{
	public:
		stack()
		{
			date=new T [N];
			top=-1;
		}
		~stack()
		{
			delete [] date;
		}
		int stack_empty()
		{
			return ((top==-1)?1:0);
		}
		int stack_full()
		{
			return ((top==N-1)?1:0);
		}
		int  in_stack(T a)
		{
			if(stack_full()==1)
			{
				cout<<"stack full"<<endl;
				return 0;
			}
			date[top+1]=a;
			top++;
		}
		T out_stack();

		void printf_stack()
		{
			if(stack_empty()==1)
			{
				cout<<"stack empty"<<endl;
				return ;
			}
			int i;
			for(i=top;i>=0;i--)
			{
				cout<<date[i]<<" ";
			}
			cout<<endl;
		}
	private:
		T *date;
		int top;
};
template <typename T,int N>
T stack<T,N>::out_stack() 
{
	if(stack_empty()==1)
	{
		cout<<"stack empty"<<endl;
		return 0;
	}
	T d=date[top];
	top--;
	return d;

}

int main()
{
	stack <double> s;
	int i=0;
	double  j=3.3;
	while(i<10)
	{
		s.in_stack(j);
		i++;
		j=j+2;
	}
	s.printf_stack();
	i=0;
	while(i<4)
	{
		s.out_stack();
		i++;
	}
	s.printf_stack();
	return 0;
}

