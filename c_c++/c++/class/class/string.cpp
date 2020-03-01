#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	string a="hallo";
	string b="yyy";
	cout<<"leng="<<a.length()<<endl;

	a.append(" world!");
	cout<<"a:"<<a<<endl;

	char buf[32]={0};
	a.copy(buf,6);
	cout<<"buf:"<<buf<<endl;
	
	cout<<"a+b:"<<a+b<<endl;
	return 0;
}
