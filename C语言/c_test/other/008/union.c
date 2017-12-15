#include <stdio.h>

union perdata
{
	char a[5];
	int class;
	struct 
	{
		char score;
	}x;
} per ={.class = 100};

int main()
{	
	printf("%d\n", sizeof(union perdata));	
}
