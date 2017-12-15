#include <stdio.h>

int main()
{
	int a[10];
	int i =0 ;
	for(i; i<10; i++)
		scanf("%d", &a[i]);
	for(i=0; i<5; i++)
	{
		a[9-i] = a[9-i]^a[i];
		a[i] = a[i]^a[9-i];
		a[9-i] = a[9-i]^a[i];
	}
	for(i=0;i<10;i++)
		printf("%d    ", a[i]);
	printf("\n");

	return 0;
}
