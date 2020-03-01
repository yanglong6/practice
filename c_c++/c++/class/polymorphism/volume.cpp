#include<iostream>
#include<cmath>
using namespace std;

class volume
{
	public:
		volume(){}
		virtual ~volume(){}
		virtual double getv()=0;
};

class sphere:public volume
{
	public:
		sphere(double r=0)
		{
			this->r=r;
		}
		virtual ~sphere(){}
		double getv()
		{
			return (4*3.14*r*r*r/3);
		}
	private:
		double r;
};

class bulk:public volume
{
	public:
		bulk(double a=0,double b=0,double c=0)
		{
			this->a=a;
			this->b=b;
			this->c=c;
		}
		double getv()
		{
			return (a*b*c);
		}
	private:
		double a,b,c;
};

class triangel:public volume
{
	public:
		triangel(double a=0,double b=0,double c=0,double h=0)
		{
			this->a=a;
			this->b=b;
			this->c=c;
			this->h=h;
		}
		double getv()
		{
			double s=(a+b+c)/2.0;
			s=sqrt(s*(s-a)*(s-b)*(s-c));
			return (s*h/3);
		}
	private:
		double a,b,c,h;
};
double test(volume *q)
{
	return (q->getv());
}

int main()
{
	sphere a(1);
	cout<<test(&a)<<endl;
	bulk b(1.0,2.0,3.0);
	cout<<test(&b)<<endl;
	triangel c(1.0,2.0,2.0,4.0);
	cout<<test(&c)<<endl;
	return 0;
}
