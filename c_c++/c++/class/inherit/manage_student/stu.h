#ifndef _STUDENT_H
#define _STUDENT_H

using namespace std;
class A
{
	public:
		A();
		void set(int date);
		int & get(int id);
		int relast();
		void show();
	private:
		int last;
		int a[100];
};

#endif
