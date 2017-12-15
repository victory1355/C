#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "kernel_list.h"


void *routine(void *arg)
{
	pthread_detach(pthread_self());
	
	int fd = (int)arg;
	int readn;
	char buf[128];
	
	while(1)
	{
		bzero(buf, sizeof buf);
		while((readn = read(fd, buf, sizeof buf)) == -1 && errno == EINTR);
		if(readn == 0)
		{
			printf("server has close\n");
			break;
		}else if(readn > 0)
		{
			printf("recive :%s", buf);
		}
			
	}
	pthread_exit(NULL);
}



int main(int argc, char **argv)
{
	
	//printf("[%d]\n",__LINE__);
	if(argc != 3)
	{
		printf("Usage:  ./client   PORT    IP\n");
		return -1;
		
	}
	int fd  = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1)
	{
		perror("socket ");
		return -1;
	}
	
	//printf("[%d]\n",__LINE__);
	struct sockaddr_in ser_addr;
	int len = sizeof ser_addr;
	bzero(&ser_addr, len);
	
	//printf("[%d]\n",__LINE__);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[1]));
	//printf("PORT = %hu\n", ntohs( ser_addr.sin_port));
	ser_addr.sin_addr.s_addr = inet_addr(argv[2]);           //已经转换成网络字节序，无需再转换
	
	
	//printf("[%d]\n",__LINE__);
	if( connect(fd, (struct sockaddr *)&ser_addr, sizeof ser_addr) == -1)
	{
		perror("connect");
		return -1;
	}
	
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)fd);
	
	char buf[128];
	//printf("[%d]\n",__LINE__);
	while(1)
	{
		//printf("[%d]\n",__LINE__);
		bzero(buf,sizeof buf);
		if( fgets(buf, sizeof buf, stdin) == NULL)
			break;
		
		if((len =write(fd, buf, strlen(buf))) ==-1)
			break;
	}
	
	
	close(fd);
	
	return 0;
	
}



















