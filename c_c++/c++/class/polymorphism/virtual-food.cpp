#include<iostream>
using namespace std;

class fash
{
	public:
	virtual void fun()
	{
		cout<<"鱼香肉丝"<<endl;
	}
	int a;
};
class meat:public virtual fash
{
	public:
	void fun()
	{
		cout<<"回锅肉"<<endl;
	}
//	int a;
};
class spice: public virtual fash,public meat
{
	public:
		spice(int n=0)
		{
			a=n;
		}
	void fun()
	{
		cout<<"青椒肉丝"<<endl;
	}
	int a;
};

void test(fash &obj)
{
	obj.fun();
}
int main()
{
	fash a;
	meat b;
	spice c(10);
	test(c);
	cout<<"c.a="<<c.a<<endl;
	cout<<"sizeof:="<<sizeof(c)<<endl;
	return 0;
}
