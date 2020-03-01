#include <iostream>
using namespace std;
//声明一个基类（父类）
class A{       
public:
	A(const int n=0){ 
		this->val=n;
	}
	~A(){
	}
public:
	void showa(){
		cout << val <<endl;
	}
	int& getval(){
		return val;
	}
	void setval(const int data){
		this->val = data;
	}
protected:    //保护成员，只有类的派生类可以调用
	void show(){
		cout << "toupifama!" << endl;	
	}
private:
	static int val;
};
int A::val;

class B: public A{  //声明一个子类（派生类），继承它的父类的所有数据（属性）、方法（行为）
public:
	void showb(){
	}
	int get_val(){
		return (getval() = 125) ;
	}
	
private:
	 int ival;
};

int main()
{
	A a;
	a.showa();
	//a.show();
	B b;
	b.showa();
	cout << b.get_val() << endl;
//	b.setval(2);
	//b.show();  //不能直接调用类的保护成员（protected:）
	a.showa();
	
}

