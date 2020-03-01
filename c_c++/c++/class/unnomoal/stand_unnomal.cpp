#include<iostream>
#include<stdexcept>
#include<exception>
#include<typeinfo>

using namespace std;
class erro:public exception
{
	public:
		erro(const char *q):msg(q){};
		const char * what()
		{
			return msg;	
		}
	private:
		const char * msg;
};

class A
{
	public:
		A(int r=0)
		{
			if(r<0)
				throw length_error();
			else 
				this->r=r;
		}
		double getc()
		{
			return (2*3.14*r);
		}
	private:
		int r;
};

int main()
{
	try
	{
		A a(-2);
	}catch(length_error &obj){
		cout<<obj.what()<<endl;
	}
		return 0;
}
