#include<stdio.h>
#include<math.h>
int main()
{
	int i,tep=0,sum=0;
	int ge=0,shi=0,bai=0;
	for(i=100;i<=999;i++)
	{
		bai=i/100;
		shi=(i/10)%10;
		ge=i%10;
//tep=bai*bai*bai+shi*shi*shi+ge*ge*ge;
                tep=pow(bai,3)+pow(shi,3)+pow(ge,3);
		if(tep==i)
		{
			printf("%d\n",i);
			sum++;

		}
	}
	printf("sum=%d\n",sum);
	return 0;
}
