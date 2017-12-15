#include <stdio.h>

int fibonacci(int i);

int main()
{
	int num;
	
	num = fibonacci(40);
	printf("%d\n", num);

	return 0;
}

int fibonacci(int i)
{
	int num;
	if(i==0||i==1)
		return 1;
	num = fibonacci(i-1)*fibonacci(i-2);
	
	return num;
} 
