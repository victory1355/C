#include <stdio.h>

extern  int a;
extern void fun(void);


int main()
{
	printf("a = %d\n", a);
	fun();
	
	return 0;
}