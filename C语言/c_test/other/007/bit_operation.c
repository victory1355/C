#include <stdio.h>

int main()
{
	int a, b;
	int ans;
	scanf("%d%d", &a, &b);
	a  = ~a+1;
	printf("%d\n", a);
	while(b)
	{
		ans = a^b;
		b = ((a&b)<<1);
		a = ans;
	}
	printf("%d\n", a);
	return 0;
}
