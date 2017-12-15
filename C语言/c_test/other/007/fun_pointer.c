#include <stdio.h>

int max(int a, int b);
void exchange(int a, int b);

int main()
{
	int a, b;

	int (*p[2])(int ,int);
	p[0] = max;

	void (*pp)(int ,int);
	pp = exchange;

	scanf("%d%d", &a, &b);

	pp(a ,b);
	printf("the max== %d\n",p[0](a ,b));
	printf("%d      %d\n", a, b);

	return 0;
}

int max(int a, int b)
{
	return a>b?a:b;
}

void exchange(int a, int b)
{
	a = a^b;
	b = b^a;
	a = a^b;
	printf("%d    %d\n", a ,b);
}

