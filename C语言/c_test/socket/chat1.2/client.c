#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
		exit(0);
	}
}

int main(int argc, char **argv) // ./client 192.168.10.xxx 50001
{
	usage(argc, argv);	

	// 1, 创建了一个TCP套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[2]));
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//地址复用
	const int on = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	// 2, 连接对端（IP + PORT）
	connect(fd, (struct sockaddr *)&srvaddr, len);

	// 3, 多路监听fd、STDIN_FILENO
	fd_set rset;

	// 4, 主线程专门负责监听标准输入，将数据及时发给服务端
	char *msg = calloc(1, 1024);
	int read_len;
	
	printf("welcome to cheap QQ\n");
	while(1)
	{
		FD_ZERO(&rset);

		FD_SET(fd, &rset);
		FD_SET(STDIN_FILENO, &rset);

		select(fd+1, &rset, NULL, NULL, NULL);

		// zz zz z 

		// 1, 你从键盘输入了一些东西
		if(FD_ISSET(STDIN_FILENO, &rset))
		{
			bzero(msg, 1024);
			fgets(msg, 1024, stdin);
			//printf("msg:%s\n", msg);
			if( strncasecmp(msg, "quit", 4) == 0 )
				break;
			if(write(fd, msg, strlen(msg)) == -1)
			{
				perror("write fail");
				return -1;
			}
		}

		// 2, 服务器那边发来的一些的东西
		if(FD_ISSET(fd, &rset))
		{
			bzero(msg, 1024);
			if( (read_len = read(fd, msg, 1024)) == -1)
			{
				perror("read fail");
				return -1;
			}
			else if(read_len == 0)
			{
				printf("server has closed\n");
				break;
			}else
				printf("get msg from server:%s\n", msg);
			//fprintf(stderr, "from server: %s", msg);
		}
	}

	close(fd);
	printf("close the fd\n");
	
	return 0;
}






















