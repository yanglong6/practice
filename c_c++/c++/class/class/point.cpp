#include<iostream>
#include<math.h>

using namespace std;
class Point
{
	public:
		Point (int x=0,int y=0)
		{
			this->x=x;
			this->y=y;
			n++;
		}

		static int n;
		void put()
		{
		//	cout<<"n:"<<n<<endl;
			cout<<"("<<x<<","<<y<<")"<<endl;
		}

		void number()
		{
			cout<<"point number:"<<n<<endl;
		}
	private:
		friend double Distance(Point a,Point b);
		int x,y;
};

double Distance(Point a,Point b)
{
	double N;
	N=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	N=sqrt(N);
	cout<<"N="<<N<<endl;
}

int Point::n;

int main()
{
	Point a(5,5);
	a.put();
	Point b(4,4);
	b.put();
	a.number();

	Distance(a,b);
	Point::n=100;
	cout<<"n="<<Point::n<<endl;

	return 0;
}
