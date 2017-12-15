#include <stdio.h>

struct date
{
	int year;
	int month;
	int day;
	struct
	{	
		int hour;
		int minute;
		int second;
	}d;	
};
int main()
{
	struct date *p;
	struct date dat = 
	{
		.year=2017,
		.month=7,	
		.day=19,	
		.d =
		{
			.hour = 18,
			.minute = 38,
			.second = 23,
		}
	};
	p = &dat;
	printf("%4d-%2d-%2d, %2d-%2d-%2d\n"
			, dat.year, dat.month, dat.day 
		        , dat.d.hour, dat.d.minute, dat.d.second);

	printf("%4d-%2d-%2d, %2d-%2d-%2d\n"
			, p->year, p->month, p->day 
		        , p->d.hour, p->d.minute, p->d.second);
	return 0;
}
