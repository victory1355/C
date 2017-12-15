#include <stdio.h>

int main()
{

	int i, n = 10, j, num[10];	
	printf("please input 10 number:");
	for(i=0;i<10;i++)
		scanf("%d", &num[i]);
	for(i=0; i<n; i++)
	{
		if(num[i]<0)
		{
			for(j=i;j<n;j++)
				num[j] = num[j+1];
	//		n--;
		}
	}
	for(i=0;i<n;i++)
		printf("%-5d",num[i]);
	printf("\n");
	for(i=0; i<10; i++)
		printf("%-5d", num[i]);
	
	printf("\n");
	
	return 0;
}
