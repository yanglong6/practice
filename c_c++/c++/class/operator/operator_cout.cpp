#include<iostream>
#include<cstring>
#include<stdio.h>

using namespace std;
class mystring
{
	public:
		mystring(const char *p="0")
		{
			int n=strlen(p);
			str=new char [n+1];
			strcpy(str,p);
		}
		
		mystring(mystring &obj)
		{
			int n=strlen(obj.str);
			this->str=new char [n+1];
			strcpy(this->str,obj.str);
		}
		~mystring()
		{
			delete [] str;
		}
		
		mystring operator+(const mystring &a)
		{
			int n=strlen(a.str)+strlen(this->str)+1;
			mystring tep;
			tep.str=new char [n];
			strcat(tep.str,this->str);
			strcat(tep.str,a.str);
			return tep;
		}
		int operator==(const mystring &a)
		{
			int i=strcmp(this->str,a.str);
			return i;
		}
			
		mystring &operator=(const mystring &t)
		{
			int n=strlen(t.str);
			delete this->str;
			this->str=new char [n+1];
			strcpy(this->str,t.str);
			return *this;
		}
		
		void print()
		{
			cout<<"str="<<str<<endl;
		}
	friend ostream & operator<<(ostream &out,mystring &s);
	private:
		char *str;
};

ostream & operator<<(ostream &out,mystring &s)
{
	out<<s.str;
	return out;
}
int main()
{
	mystring a("123");
	cout<<"a="<<a<<endl;

	mystring b(" 456");
	cout<<"b="<<b<<endl;

	mystring c=b;
	c=a+b;
	
	cout<<"c="<<c<<endl;
	cout<<"b="<<b<<endl;
#if 0
	mystring d;
	d=a+b+c+a;
	cout<<d<<endl;

	int i=(a==b);
	cout<<i<<endl;
#endif
	return 0;
}
