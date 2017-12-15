#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
	struct hostent *p = gethostbyname("www.baidu.com");

	printf("h_name = %s\n", p->h_name);
	switch(p->h_addrtype)
	{
		case AF_INET:
				printf("ipv4\n");break;
		case AF_INET6:
				printf("ipv6\n");break;
	}
	printf("addr length = %d\n", p->h_length);

	int i = 0;
	printf("size = %d\n", sizeof (*(p->h_aliases[0])));
	printf("size = %d\n", sizeof (*(p->h_addr_list[0])));
	
	while(*(p->h_aliases) != NULL)
	{
		if(*(p->h_aliases) == NULL)
			break;
		printf("h_aliases = %s\n", *p->h_aliases[++i]);
	}
	printf("flag\n");
	
	i = 0;
	while(*(p->h_addr_list) != NULL)
	{
		if(*(p->h_addr_list) == NULL)
			break;
		printf("h_aliases = %s\n", p->h_addr_list[++i]);
	}
	
	return 0;
}






























