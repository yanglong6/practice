#include<iostream>
#include<memory>
using namespace std;
class A
{
	public:
		A()
		{
			cout<<"aaaa"<<endl;
		}
		void show()
		{
			cout<<"show-----"<<endl;
		}
};

int main()
{
	shared_ptr <A> p(new A);
	p->show();
	return 0;
}
