#include <stdio.h>

int main()
{
	int day, month,year, num = 0;
	printf("please input a day in 2017\n");
	printf("input format like 2017-12-12\n");
	scanf("%4d-%2d-%2d",&year,&month,&day);
	while(year<0||month<0||month>12||day>31||day<0)
	{
		scanf("%4d-%2d-%2d",&year,&month,&day);
		printf("input format like 2017-12-12\n");
	}
	switch(month-1)
	{
		case 12:num += 31;
		case 11:num += 30;
		case 10:num += 31;
		case 9 :num += 30;
		case 8 :num += 31;
		case 7 :num += 31;
		case 6 :num += 30;
		case 5 :num += 31;
		case 4 :num += 30;
		case 3 :num += 31;
		case 2 :if(year%400==0||(year%4==0&&year%100!=0))
			{		
				num += 29;
			}
			else
				num += 28;
		case 1 :num += 31;
		default:break;
	}
	num += day;
//	day_th = num;
	printf("the day is %dth day in %d\n", num, year);
	return 0;
}
