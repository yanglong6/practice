#include<iostream>
#include<cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
class Clock
{
	public:
		void set_time(int h,int m,int s)
		{
			hour=h;
			minute=m;
			second=s;
			int ret;
			while(1)
			{
				second++;
				if(second==60)
				{
					minute++;
					second=0;
					if(minute==60)
					{
						hour++;
						minute=0;
						if(hour==24)
							hour=0;
					}
				}
				ret=alarm_time(8,11);
		//	printf("%d:%d:%d",hour,minute,second);
			cout<<hour<<":"<<minute<<":"<<second;
			fflush(stdout);
			sleep(1);
			printf("\r");
			printf("         ");
				printf("\r");
			}

		}
		int alarm_time(int hh,int mm)
		{
			h1=hh;
			m2=mm;
			if((hour==hh)&&(minute==mm))
				cout<<"clarm time to up  ";
			return 0;
		}
	private:
		int hour;
		int minute;
		int second;
		int h1,m2;
};
		int main()
		{
			Clock a;
			a.alarm_time(8,11);
			a.set_time(8,10,56);
			//a.show_time();
			return 0;
		}
