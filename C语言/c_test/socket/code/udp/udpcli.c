#include "head4sock.h"

#define MAXSIZE 80 

void usage(const char *info)
{
	printf("Usage: %s <IP> <PORT>\n", info);	
	exit(0);
}


int main(int argc, char *argv[]) // ./udpcli 192.168.10.xxx 50001
{
	if(argc != 3)
		usage(argv[0]);

	int fd;

	fd = Socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in srv;
	bzero(&srv, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(argv[1]);
	srv.sin_port = htons(atoi(argv[2]));

	char buf[MAXSIZE];
	while(1)
	{
		bzero(buf, MAXSIZE);

		if(fgets(buf, MAXSIZE, stdin) == NULL)
			break;

		sendto(fd, buf, strlen(buf), 0,
			(struct sockaddr *) &srv, sizeof(srv));
	}

	close(fd);

	return 0;
}
