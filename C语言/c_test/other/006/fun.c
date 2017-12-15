#include <stdio.h>

int main()
{
	int p, m, n, value1, value2, value3;

	scanf("%d%d", &m, &n);
	value1 = factorial(m);
	value2 = factorial(n);
	value3 = factorial(m-n);
	p = value1/value2*value3;
	printf("%d\n", p);

	return  0;
}

int factorial(int a)
{
	int num;
	if(a==0||a==1)	
		return 1;
	num = factorial(a-1)*a;
	
	return num;
}
