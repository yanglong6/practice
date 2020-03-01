#include<iostream>
using namespace std;

class father
{
	public:
		int a;
	protected:
		int b;
	private:
		int c;
};
class son:public father
{
public:
	void print()
	{
		cout<<"a="<<a<<endl;
		cout<<"b="<<b<<endl;
//		cout<<"c="<<c<<endl;
	}

};
int main()
{
	son s;
	cout<<"s.a="<<s.a<<endl;
//	cout<<"s.b="<<s.b<<endl;
//	cout<<"s.c"<<s.c<<endl;
	return 0;
}
