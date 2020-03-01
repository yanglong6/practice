#include<iostream>
using namespace std;
class a
{
	public:
		a(int n=0):va(n)
		{
			cout<<"va="<<va<<endl;
		}
		void fun()const
		{
			cout<<"vv="<<va<<endl;
		}
	//private:
		 int va;
};
int main()
{
	const a b(10);
	cout<<"va "<<b.va<<endl;
	b.fun();
	return 0;
}
