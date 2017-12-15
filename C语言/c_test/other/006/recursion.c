#include <stdio.h>

int fun(int n);

int main()
{
	int number, i;
	scanf("%d", &i);
	number = fun(i);
	printf("number = %d\n", number);
	
	return 0;
}

int fun(int n)
{
	long long num;
	if(n==1||n==0)
	{
		return 1;
	}
	num = fun(n-1)*n;


	return num;	
}
