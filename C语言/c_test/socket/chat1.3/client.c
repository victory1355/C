#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#include "kernel_list.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: ./client IP PORT\n");
		return -1;
	}
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser_addr;
	int len = sizeof ser_addr;
	bzero(&ser_addr, len);
	
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[2]));
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	const int on = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
	
	if((connect(fd, (struct sockaddr *)&ser_addr, len)) == -1)
	{
		perror("connect");
		return -1;
	}
	printf("[%d]\n", __LINE__);
	fd_set set;
	bzero(&set, sizeof set);
	char buf[128];
	int nread;
	
	while(1)
	{
		FD_ZERO(&set);
		FD_SET(fd, &set);
		FD_SET(STDIN_FILENO, &set);
		printf("[%d]\n", __LINE__);
		select(fd+1, &set, NULL, NULL, 0);
		printf("[%d]\n", __LINE__);
		
		if(FD_ISSET(fd, &set) > 0)
		{
			bzero(buf, sizeof buf);
			while((nread = read(fd, buf, sizeof buf)) == -1 && errno == EINTR);
			if(nread == 0)
			{
				break;
			}
			else if(nread > 0)
			{
				printf("get from %s", buf);
			}
		}
		if(FD_ISSET(STDIN_FILENO, &set) > 0)
		{
			bzero(buf, sizeof buf);
			if(fgets(buf, sizeof buf, stdin) == NULL)
			{
				break;
			}
			write(fd, buf, strlen(buf));
		}
	}
	
	return 0;
}





































