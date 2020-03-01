#include<iostream>

using namespace std;

template <typename t1>
t1 add(t1 x,t1 y,t1 z=0)
{
	return (x+y+z);
}

template <>
double add(double x,double y,double z)
{
	cout<<"tttt"<<endl;
	return (x+y+z);
}

int main(void)
{
	cout<<add(3,4)<<endl;
	cout<<add(3.3,4.3,2.4)<<endl;
//	cout<<add(3,4.5)<<endl;
//	cout<<add('a',1)<<endl;
	return 0;
}
