#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


int main()
{
	char buf[128];
	char *p = buf;
	while(1)
	{
		bzero(buf, 128);
		fgets(p, 128, stdin);
		printf("%s\n", p);
		if(!strncasecmp(p,"quit", 4))  
		{
			break;
		}
	}
	
	return 0;
}