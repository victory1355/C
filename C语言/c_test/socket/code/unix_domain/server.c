//:server.c
#include <stdio.h>
#include "head4sock.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define LISTENQ 5

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Usage:%s <path>\n",argv[0]);
		exit(1);
	}

	int fd;
	fd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	struct sockaddr_un local_address;
	bzero(&local_address, sizeof local_address);

	local_address.sun_family = AF_LOCAL;
	memcpy(local_address.sun_path,argv[1],strlen(argv[1]));
	
	Bind(fd,(struct sockaddr *)&local_address,sizeof(local_address)); 

	Listen(fd, LISTENQ);

	struct sockaddr_un peer_address;
	socklen_t peer_address_length;
	peer_address_length = sizeof(peer_address);

	ssize_t written;
	char *welcome_message="welcome to unix domain programming.\n";

	int connfd;

	while(1)
	{
		connfd = Accept(fd,(struct sockaddr *)&peer_address,&peer_address_length);

		written = write(connfd, welcome_message, strlen(welcome_message));
		printf("written %d bytes to %d.\n",written,connfd);

		close(connfd);
	}

	close(fd);
	exit(0);
}
