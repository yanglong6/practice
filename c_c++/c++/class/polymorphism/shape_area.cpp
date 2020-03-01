#include<iostream>
using namespace std;

class shape
{
	public:
		shape(){
			cout<<"shape"<<endl;
		}
		virtual double getc()=0;
};

class cicle:public shape
{
	public:
		cicle(int r=0){
			this->r=r;
			cout<<"cicle"<<endl;
		}
		double getc()
		{
			return (2*3.14*r);
		}
	private:
		int r;
};

class triangel:public shape
{
	public:
		triangel(int a=0,int b=0,int c=0)
		{
			this->a=a;
			this->b=b;
			this->c=c;
			cout<<"triangel"<<endl;
		}
		double getc()
		{
			return (a+b+c);
		}
	private:
		int a,b,c;
};

double countc(shape *a[],int n)
{
	int i=0;
	double sum=0;
	for(i=0;i<n;i++)
	{
		sum+=a[i]->getc();
	}
	return sum;
}
int main()
{
	cicle a(2);
	cicle b(3);
	triangel c(1,2,3);
	triangel d(2,2,2);
	shape *q[]={&a,&b,&c,&d};
	cout<<"square="<<countc(q,4)<<endl;
	return 0;
}
