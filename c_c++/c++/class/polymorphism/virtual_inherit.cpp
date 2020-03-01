
#include<iostream>
using namespace std;
class man
{
	public:
		int i;
};

class father:public virtual man
{
	public:
		father()
		{
			cout<<"father 构造"<<endl;
		}
};
class mather:public virtual man
{

};

class son:public father,public mather
{
	public:
		son()
		{
			cout<<"son 构造"<<endl;
		}
		~son()
		{
			cout<<"son 析构"<<endl;
		}
};

int main()
{
	son s;
	s.i=10;
	return 0;
}
