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
		
		operator char *()
		{
			return str;
		}
		
		
		void print()const
		{
			cout<<"str="<<str<<endl;
		}
	private:
		char *str;
};

int main()
{
	mystring a="123";
	cout<<"a="<<a<<endl;

	mystring b=" 456";
	mystring c;

	strcpy((char *)a,"wewewfwfwf")	;
	cout<<a<<endl;

	return 0;
}
