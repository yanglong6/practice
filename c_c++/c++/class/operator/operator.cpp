#include<iostream>
#include<cstring>

using namespace std;
class B;
class A
{
	public:
		A (int a=0,int b=0)
		{
			this->x=a;
			this->y=b;
		}
		void print()
		{
			cout<<"x="<<x<<" "<<"y="<<y<<endl;
		}
		A operator+(A &obj)
		{
			A tep;
			tep.x=this->x+obj.x;
			tep.y=this->y+obj.y;
			return tep;
		}
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
	friend A operator+(A &a,B &b);
	private:
		int x,y;
};
class B
{
	public:
		B (int a=0,int b=0)
		{
			this->x=a;
			this->y=b;
		}
	friend A operator+(A &a,B &b);
		void print()
		{
			cout<<"x="<<x<<" "<<"y="<<y<<endl;
		}
				private:
		int x,y;
};
A operator+(A &a,B &b)
{
	A tep;
	tep.x=a.x+b.x;
	tep.y=a.y+b.y;
	return tep;
}

int main()
{
	A a(3,6);
	B b(2,4);

	A c=a+b;
	c.print();
	return 0;
}
