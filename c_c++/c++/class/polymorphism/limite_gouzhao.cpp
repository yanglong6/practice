#include<iostream>
using namespace std;

class father
{
	public:
	//friend father* get();
	private:
		father()
		{
			cout<<"father 构造"<<endl;
		}
};
class son:public father
{
	public:
		son()
		{
			cout<<"son 构造"<<endl;
		}
		~son()
		{
			cout<<"son 析构"<<endl;
		}
};

father * get()
{
	//father f;
	//father *p=new father;
	//return p;
}

int main()
{
	//father a;
	//father *q=get();
	return 0;
}
