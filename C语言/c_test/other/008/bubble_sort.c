#include <stdio.h>

void bubble_sort_1(int *,int);
void bubble_sort_2(int *a, int len);

int main()
{
	int s[5];
	int i, j, k;
	for(i=0;i<5;i++)
		scanf("%d", &s[i]);
	bubble_sort_1(s, 5);
	bubble_sort_2(s, 5);
	
	return 0;
}

void bubble_sort_1(int *a, int len)
{
	int i,j,k;
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-i-1;j++)
		{
			if(a[j]>=a[j+1])
			{	
				a[j] = a[j+1]^a[j];
				a[j+1] = a[j]^a[j+1];							    a[j] = a[j+1]^a[j];	
			}
		}
		
	}
	for(k=0;k<len;k++)
		printf("%-5d", a[k]);
	printf("\n");
}



void bubble_sort_2(int *a, int len)
{
	int i,j,k;
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-i-1;j++)
		{
			if(a[j]<=a[j+1])
			{	
				a[j] = a[j+1]^a[j];
				a[j+1] = a[j]^a[j+1];							    a[j] = a[j+1]^a[j];	
			}
		}
	}	
	for(k=0;k<len;k++)
		printf("%-5d", a[k]);
	printf("\n");
}
