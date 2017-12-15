#include <stdio.h>

int main()
{
	unsigned int a = 1,c, d = -1;
	int b = -2;
	c = b;
	printf("d == %d    d == %x\n", b,b);
	printf("c == %d c ==%u  b == %u\n", c, c, b);
		
	if(a+b==0xffffffffu)
		printf("a+b:%x      %d\n", a+b, a+b);
	else
		printf("you will get nothing.\n");

	return 0;
}
