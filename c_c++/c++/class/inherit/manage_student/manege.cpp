#include<iostream>
#include"stu.h"

class stu
{
	public:
		stu(){};
		~stu(){};
		void inscore(int date)
		{
			score.set(date);
		}
		int getscore(int id)
		{
			return score.get(id);
		}
		void show()
		{
			score.show();
		}
		A &getdemo()
		{
			return score;
		}
	private:
		A score;
};

class student:public stu
{
public:
	student(){};
	~student(){};
	int average()
	{
		int i=0,sum=0;
		cout<<getdemo().relast()<<endl;
		for(i=0;i<getdemo().relast();i++)
			sum+=getscore(i);
		return (sum/getdemo().relast());
	}
};

int main()
{
	student s;
	s.inscore(100);
	s.inscore(10);
	s.inscore(60);
	
	s.show();
	cout<<s.average()<<endl;
	return 0;
}
