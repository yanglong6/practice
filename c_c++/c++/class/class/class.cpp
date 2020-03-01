#include<iostream>
#include<cstdlib>
#define PI 3.14159

using namespace std;
class cicle
{
	public:
		cicle()
		{
		//	 r=R;
			cout<<"gz"<<endl;
		}
		~cicle()
		{
			cout<<"係构"<<endl;
		}
		void area()
		{
			double s;
		//	r=R;
			s=PI*r*r;
			cout<<"area:"<<s<<endl;
		}
		void perimeter()
		{
			double len;
			len=2*PI*r;
			cout<<"len:"<<len<<endl;
		}
		void test()
		{
			cout<<"tt"<<endl;
		}
	private:
		double r;
		int i;
};

int main()
{
//	cicle yuan(10);
//	yuan.area();
//	yuan.perimeter();

	cicle *p=(cicle *)malloc(sizeof(cicle));
	p->test();
	free(p);
	cout<<sizeof(cicle)<<endl;
/*
	cicle *q=new cicle;
	q->test();
	delete q;
	return 0;
*/
}
