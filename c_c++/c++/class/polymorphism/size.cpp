#include<iostream>
using namespace std;
class a
{
	public:
		virtual int fun()
		{
			return 0;
		}

	private:
};

class B:public virtual a
{

};

int main()
{
	a b;
	B c;
	cout<<sizeof(b)<<endl;
	cout<<sizeof(c)<<endl;
	return 0;
}
