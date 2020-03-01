#include<iostream>
using namespace std;

class father
{
	public:
	father(int n)
	{
		a=n;
	}
	~father()
	{
		cout<<"ff xigou"<<endl;
	}
	void print()
	{
		cout<<"a="<<a<<endl;
	}
	private:
	int a;
};

class son:public father
{
public:
	son(const int m=0,const int n=0):father(n),val2(m)
	{
	//	this->a=250;
	}
int val2;

};

int main()
{
	son s(11,12);
	s.print();
	cout<<sizeof(s)<<endl;
	return 0;
}
