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

template <typename T>
class point
{
	public:
		point(T *q)
		{
			this->q=q;
		}
		T *operator->()
		{
			return q; 
		}
		T &operator*()
		{
			return *q;
		}
	private:
		T *q;
};

int main()
{
	point<A>q(new A);
	q->show();
	(*q).show();
	return 0;
}
