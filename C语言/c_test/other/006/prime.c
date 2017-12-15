#include <stdio.h>
#include <math.h>

int main()
{
	int k, m, i, n = 0;
	for(m=100; m<=200; m++)
	{
		k = (int)sqrt(m);
		for(i=2; i<=k; i++)
			if(m%i==0)
				break;
		if(i>=k)
		{
			printf("%5d", m);
			n++;
			if(n%4==0)
				printf("\n");
		}
	}
	
	return 0;
}
