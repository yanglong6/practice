#include<iostream>
#include<cstring>

using namespace std;
template <typename T>
class A
{
	public:
		A (T a,T b)
		{
			this->x=a;
			this->y=b;
		}
		void print()
		{
			cout<<"x="<<x<<" "<<"y="<<y<<endl;
		}
	/*	
		A operator+(A &obj)
		{
			A tep;
			tep.x=this->x+obj.x;
			tep.y=this->y+obj.y;
			return tep;
		}
	*/
		template <typename C>
		friend A<C> operator+(const A<C> &a,const A<C> &b);
		A operator++(int)
		{
			cout<<"hou"<<endl;
			A tep=*this;
			x++;
			y++;
			return tep;
		}
		A operator++()
		{
			cout<<"qian"<<endl;
			x++;
			y++;
			A tep=*this;
			return tep;
		}
	private:
		T x,y;
};

template <typename T>
A<T> operator+(const A<T> &a,const A<T> &b)
{
	A <T> tep;
	tep.x=a.x+b.x;
	tep.y=a.y+b.y;
	return tep;
}

int main()
{
//	A <double> a(3.1,6.1);
//	A <double> b(2,4);
	A <string> a("aa","bb");
	A <string> b("dd","cc");

	A <string> c=a+b;
	c.print();
	return 0;
}
