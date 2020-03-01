#include<iostream>
using namespace std;

template <typename T> 
T mutiply (T a,T b,T c=1)
{
	return a*b*c;
}
int main()
{
	cout<<mutiply<double>(5.0,6.1,2)<<endl;
	return 0;
}
