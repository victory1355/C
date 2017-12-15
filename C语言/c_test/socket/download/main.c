#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void usage(int argc)
{
	if(argc != 2)
	{
		printf("Usage: ./main www.boa.org/boa-0.94.14rc21.tar.gz\n");
		exit(1);
	}
}

void right_addr(char *argv)
{
	char *p;
	if(p = strstr(argv, "http:"))
	{
		 if( strncasecmp(argv, "http://www.", 11) != 0)
		 {
			 printf("bad address format\n");
		     exit(1);
		 }
		 if(strcasecmp(p, "http://www.com") ==0 )
		 {
			 printf("bad address format\n");
		     exit(1);
		 }
	}
	/*
	else if( strncasecmp(argv, "www.", 4) != 0 || strcasecmp(argv, "www.com") == 0)
	{
		printf("bad address format\n");
		exit(1);
	}

	if(p = strstr(argv, ".com"))
	{
		if( strncasecmp(p, ".com", 4) != 0)
		{
			printf("bad address format\n");
			exit(1);
		}
	}
	else{
		printf("bad address format\n");
		exit(1);
	}*/

}
int main(int argc, char **argv)
{
	usage(argc);
	//判断输入地址的合法性
	right_addr(argv[1]);
	
	//char *p_addr = strstargv[1];
	struct hostent *p = gethostbyname("www.boa.org");
	if(p == NULL)
	{
		perror("gethostbyname");
		return -1;
	}
	//printf("main\n");
	int fd;
	if( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser_addr;
	bzero(&ser_addr, sizeof ser_addr);
	
	
	//printf("[%d]\n", __LINE__);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(80);
	ser_addr.sin_addr = *((struct in_addr *)(p->h_addr_list[0]));
	
	printf("IP:%s\n", inet_ntoa(ser_addr.sin_addr));
	//while(1);
	
	if( connect(fd, (struct sockaddr *)&ser_addr, sizeof ser_addr) == -1)
	{
		perror("connect");
		return -1;
	}

	char *p1 = NULL;
	char ch = 'm';
	char buf[1000], host_buf[100];
	bzero(buf, sizeof buf);
	bzero(host_buf, sizeof host_buf);

	p1 = strstr(argv[1], ".org");
   //printf("[%d]\n", __LINE__);
	//=====================================================================
	char file_buf[100];
	bzero(file_buf, sizeof file_buf);
	struct stat file_stat;                     //定义变量不可以放在判断语句里面,不然出现未申明错误
	bzero(&file_stat, sizeof file_stat);
	if(p1 != NULL)
	{
		snprintf(file_buf, sizeof file_buf, "/home%s", p1+4);
	}
	else{
		perror("strstr");
		return -1;
	}
	
	printf("download file = %s\n", file_buf);
	
	FILE *fp = fopen(file_buf, "a");
	if(fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	else{
		
		if(stat(file_buf, &file_stat) == -1)
		{
			perror("stat ");
			return -1;
		}
	}
	printf("\n==================================================\n");
	if(strstr(argv[1], "http"))
	{
		//http//:
	//	printf("[%d]\n", __LINE__);
		//printf("p1 = %s\n", p1);
		strncpy(host_buf, argv[1]+7, ((p1+3) - (argv[1]+7)+1));
		snprintf(buf, sizeof(buf),"GET %s HTTP/1.1\r\n"
								  "Host: %s\r\n"
								  "Range: 0-\r\n\r\n",
								  ((p1+3)+1), host_buf);
		printf("request = %s\n", buf);
	}
	else{
		//printf("[%d]\n", __LINE__);
		strncpy(host_buf, argv[1], ( (p1+3) - argv[1])+1);
		snprintf(buf, sizeof(buf),"GET %s HTTP/1.1\r\n"
								  "Host: %s\r\n"
								  "Range: 0-\r\n\r\n",
								  ((p1+3)+1), host_buf);
		printf("request = %s\n", buf);
	}
	
	//=======================================================================
	if( write(fd, buf, strlen(buf)) ==-1)           //调用该函数出错会直接退出程序
	{
		perror("write");
		return -1;
	}
	//printf("[%d]\n", __LINE__);
	char read_head[500];
	char read_content[100];
	char *p_content_length = NULL;
	bzero(read_head, sizeof read_head);
	int readn;
	
	//printf("[%d]\n", __LINE__);
	//获取报头信息,只读一次
	int count = 0;
	printf("\n===========================================================\n");
	//printf("[%d]\n", __LINE__);
	while(1)
	{
		while( (readn = read(fd, read_head+count, sizeof (char))) ==-1  && errno == EINTR);
		
		if(readn == -1)
		{
			perror("read");
			//break;
			return -1;
		}
		count++;
		if(strstr(read_head, "\r\n\r\n"))
		{	
			break;	
		}
		
	}
	
//	printf("[%d]\n", __LINE__);
	//打印响应报头
	printf("%s\n", read_head);
	printf("==========================================================\n");
	int content_length;
	p_content_length = strstr(read_head, "Content-Length");		
	if(p_content_length != NULL)
	{
		p_content_length = p_content_length+strlen("Content-Length")+2;
		content_length = atoi(p_content_length);
		
		//printf("content_length = %d\n", content_length);
		//printf("file size = %lu\n", file_stat.st_size);
		
		if(file_stat.st_size == content_length)
		{
			printf("the file has existed\n");
			//close(fd1);
			close(fd);
			fclose(fp);
			return 0;
		}
		printf("content_length = %d\n", content_length);
		//printf("[%d]\n", __LINE__);
	}
	else
	{
		printf("not found\n");
	}
	
	//获取实体内容     
	printf("=================================================\n");
	int fd1 = fileno(fp);
	if(fd1 < 0)
	{
		perror("fileno");
		return -1;
	}
	struct stat stat_file;
	bzero(&stat_file, sizeof stat_file);
	printf("%s\n", file_buf);
	while(1)
	{

		bzero(read_content, sizeof read_content);
		while( (readn = read(fd, read_content, sizeof (read_content))) ==-1  && errno == EINTR);
		if(readn == -1)
		{
			perror("read");
			return -1;
		}
		
		//===========================================
		write(fd1, read_content, readn);
		
		stat(file_buf, &stat_file);
		if((int)stat_file.st_size == content_length)
		{
			printf("close file\n");
			close(fd1);
			close(fd);
			fclose(fp);
			break;
		}
		
	}
	//printf("content_length = %d\n", content_length);
	//printf("file size = %lu\n", stat_file.st_size);
	
	return 0;
}




























