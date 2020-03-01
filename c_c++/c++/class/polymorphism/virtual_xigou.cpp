#include<iostream>
using namespace std;

class father
{
	public:
		father()
		{
			cout<<"father 构造"<<endl;
		}
		virtual ~father()
		{
			cout<<"father 析构"<<endl;

		}
};
class son:public father
{
	public:
		son ()
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
	father *p=new son;
	delete p;
	return 0;
}
