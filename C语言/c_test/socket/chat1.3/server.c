#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "kernel_list.h"

typedef struct client_list
{
	unsigned short ID;
	int  fd;
	
	struct list_head list;
}client_node, *client_list;

client_list head;



void process_message(int fd);

client_list create_head(void )
{
	client_list new = malloc(sizeof(client_node));
	if(new == NULL)
		return NULL;
	
	INIT_LIST_HEAD(&new->list);
	
	return new;
}

bool addclient(client_list new)
{
	list_add(&new->list, &head->list);
	
}

void show_client(client_list head1)
{
	if(head1 == NULL)
		return ;
	client_list p = NULL;
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, &head1->list)
	{
		p = list_entry(pos, client_node, list);
		printf("ID = %hu,fd = %d\n", p->ID, p->fd);
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage:   ./server PORT\n");
		return -1;
	}
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1)
	{
		perror("socket");
		return -1;
	}
	pthread_mutex_init(&lock, NULL);
	
	struct sockaddr_in ser_addr, cli_addr;
	int len = sizeof ser_addr;
	bzero(&ser_addr, len);
	bzero(&cli_addr, len);
	
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[1]));
//	printf("PORT = %hu\n", ntohs(ser_addr.sin_port));
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

//	printf("IP = %s\n", inet_ntoa(ser_addr.sin_addr));        //为什么是0.0.0.0
	
	if (bind(fd, (struct sockaddr *)&ser_addr, sizeof ser_addr) == -1)
	{
		perror("bind");
		return -1;
	}
	
	if(listen(fd, 3) == -1)
	{
		perror("listen");
		return -1;
	}
	
	//创建头节点
	head = create_head();
	
	char buf[128];
	fd_set set;
	bzero(&set, sizeof set);
	
	int maxfd = -1;
	client_list p = NULL;
	struct list_head *pos, *n;
	
	while(1)
	{
		FD_ZERO(&set);
		bzero(buf, sizeof buf);
		FD_SET(fd, &set);
		
		list_for_each_safe(pos, n, &head->list)
		{
			p = list_entry(pos, client_node, list);
			FD_SET(p->fd, &set);
			maxfd = maxfd > p->fd ? maxfd:p->fd;
		}
		
		select(maxfd+1, &set, NULL ,NULL, 0);
		
		if(FD_ISSET(fd, &set) >0)
		{
			client_list new = malloc(sizeof client_node);
			if(new == NULL)
			{
				perror("malloc");
				return -1;
			}
			new->fd = confd;
			new->ID = ntohs(cli_addr.sin_port);
			//往描述符集合添加新的描述符
			addclient(new);
		}
		
		//检测描述符的状态
		list_for_each_safe(pos, n, &head1->list)
		{
			p = list_entry(pos, client_node, list);
		
			if(FD_ISSET(p->fd, &set) > 0)
			{
				process_message(p->fd);
			}
			
		}
		
	}
	
	return 0;
	
}

void process_message(int fd)
{
	char buf[128];
	bzero(buf, sizeof buf);
	
	while(read(fd, buf, sizeof buf) == -1 && errno == EINTR);
	
	if(strstr(buf, ":"))
	{
		//私聊
		private_talk(fd);
	}
	else
	{
		//群聊
		broadcast(fd);
	}
}








void *routine(void *arg)
{
	pthread_detach(pthread_self());
	
	int ID = (int)arg;
	//printf("ID = %hu\n", ID);
	
	struct list_head *pos, *n;
	client_list p;
	int readn;
	char buf[128];
	
	list_for_each_safe(pos, n ,&head->list)
	{
		p = list_entry(pos, client_node, list);
		if(p->ID == ID)
		{
			printf("ID = %hu\n", ID);
			printf("fd = %d\n", p->fd);
			while(1)
			{
				bzero(buf, sizeof(buf));
				while( (readn = read(p->fd, buf, sizeof(buf))) == -1 && errno == EINTR );
				if(readn == 0)
					break;
				if(readn >0 )
				{
					printf("get:%s", buf);
					write(p->fd, buf, strlen(buf));
				}
			}
			break;
			
		}
	}
	
}


































