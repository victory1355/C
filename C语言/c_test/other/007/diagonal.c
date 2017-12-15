#include <stdio.h>

int main()
{
	int num[4][4], number = 0;

	int i ,j;
	printf("input 4x4  number\n");
	
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			scanf("%d", &num[i][j]);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{	
			if(i>=j)
			number += num[i][j];
		}
	}
	printf("the diagonal number is %d\n", number);
	

	return 0;
}
