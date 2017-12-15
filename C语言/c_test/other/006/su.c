#include <stdio.h>
#include <string.h>
#include <math.h>

int prime(int );

int main()
{
	int i, num;
	scanf("%d", &num);
	i = prime(num);
	if(i==1)
	{
		printf("the number %d is sushu!\n", num);
	}

	return 0 ;
}

int prime(int num)
{
	int i;
	for(i=2; i<=sqrt(num); i++)
	{
		if(num%i==0)
			return 1;
	//	else return 0;
	}
	return 0;
}
