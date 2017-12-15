#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include <assert.h>

#include <dirent.h>

void menu_mode1(char *choose1, int fd);
void menu_mode2(char *choose1, int fd);

void *tcp_udp_routine(void *arg);

void init_tty(int fd)
{
	struct termios new_cfg, old_cfg;
	if(tcgetattr(fd, &old_cfg) != 0)
	{
		perror("tcgetattr() failed");
		return;
	}

	bzero(&new_cfg, sizeof(new_cfg));

	new_cfg = old_cfg;
	//设置为原始模式
	cfmakeraw(&new_cfg);

	//输入输出速度
	cfsetispeed(&new_cfg, B9600);
	cfsetospeed(&new_cfg, B115200);

	//控制模式标志
	new_cfg.c_cflag |= CLOCAL | CREAD;    /*接收使能*/
	//数据位的掩码
	new_cfg.c_cflag &= ~CSIZE;
	//8个数据位
	new_cfg.c_cflag |= CS8;
	//
	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_cflag &= ~CSTOPB;    
	
	//控制特性
	new_cfg.c_cc[VTIME] = 0;
	new_cfg.c_cc[VMIN]  = 1;
	tcflush(fd, TCIFLUSH);

	tcsetattr(fd, TCSANOW, &new_cfg);
}



void *routine(void *arg)
{
	pthread_detach(pthread_self());
	int fd = (int)arg;

	char *msg = calloc(1, 1024);
	int n;
	while(1)
	{
		bzero(msg, 1024);
		n = read(fd, msg, 1024);
		if(n <= 0)
		{
			perror("read() failed");
			break;
		}
		if(n == 0)
		{
			break;
		}
		printf("%s", msg);
	}
	free(msg);
	
}



int main(void)
{

	//接wifi
	char *device1 = "/dev/ttySAC1";

	// 1，打开指定的串口设备节点，并初始化
	int fd1 = open(device1, O_RDWR|O_NOCTTY);
	if(fd1 == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				device1, strerror(errno));
		exit(0);
	}

	//2，配置串口
	init_tty(fd1);
	
	// ============ 独立线程读取串口信息 ============== //
	pthread_t tid1;

	pthread_create(&tid1, NULL, routine, (void*)fd1);
	
	// ============ 主线程发送信息给串口 ============ //
	int n;
	char buf[100];
	bzero(buf, sizeof buf);
	//=================================================
	int mode;
	int retm;
	pthread_t tid;
	
	printf("==========================\n");
	printf("1，mode1:热点模式\n");
	printf("2，mode2:从端模式\n");
	printf("==========================\n");
	
	while(1)
	{
		printf("choose which mode");
		retm = scanf("%d", &mode);
		if(retm != 1)
		{
			while(getchar() != '\n');
			continue;
		}
		else
			break;
	}
	if(mode == 1)
	{
		printf("==================热点模式=================\n");
		printf("1:com---AT\r\n");
		printf("2:com---AT+RST\r\n");
		printf("3:com---AT+CWMODE=2---热点模式\n");
		printf("4:com---AT+RST\r\n");
		
		printf("5:com---AT+CWSAP=\"ZHAN\",\"12345678\", 11, 0\r\n");
		printf("6:com---AT+CIPMUX=1---多路链接\n");
		printf("7:com---AT+CIPSERVER=1,8080---服务器模式\n");
		printf("8:com---AT+CIFSR---WiFi模块IP\n");
		printf("l:com---AT+CWLIF---查看已链接的设备的IP地址\n");
		
		printf("t:com---AT+CIPSTART=\"TCP\", IP, 8080---发起链接请求\n");
		printf("z:com---AT+CIPSEND=10---设置10字节发送数据长度\n");
		printf("s:com---AT+CIPSEND---发送数据\n");
		printf("c:com---AT+CIPCLOSE---关闭TCP或者UDP\n");
		
		printf("q:com---exit\n");
		printf("===========================================\n");
	}
	
	if(mode == 2)
	{
		printf("==================从端模式=================\n");
		printf("1:com---AT\r\n");
		printf("2:com---AT+RST\r\n");
		printf("3:com---AT+CWMODE=1---从端模式\n");
		printf("4:com---AT+RST\r\n");
		
		printf("5:com---AT+CWLAP---搜索附近热点\n");
		printf("6:com---AT+CWJAP=name, password---链接热点\n");
		printf("7:com---AT+CIFSR---WiFi模块IP\n");
		
		printf("8:com---AT+CIPSTART=\"TCP\", IP, 8080---发起链接请求\n");
		printf("9:com---AT+CIPSEND=10---设置10字节发送数据长度\n");
		printf("s:com---AT+CIPSEND---发送数据\n");
		printf("c:com---AT+CIPCLOSE---关闭TCP或者UDP\n");
		
		printf("0:com---AT+CWQAP---断开WiFi链接\n");
		printf("q:com---exit\n");
		printf("============================================\n");
	}

	while(1)
	{
		if(mode == 1)
		{
			menu_mode1(buf,fd1);
		}
		if(mode == 2)
		{
			menu_mode2(buf, fd1);
		}
	}

	return 0;
}


void menu_mode1(char *choose1, int fd)
{
	//assert(choose);
	char choose[100];
	bzero(choose, sizeof choose);
	int ret = -1;
	int rets;
	char choo;

	while(1)
	{
		//printf("mode1:what do you want?\n");
		ret = scanf("%c", &choo);
		if(ret != 1)
		{
			while(getchar() != '\n');
			continue;
		}
		else
			break;
	}
	char buf[100];
	char tcp_ip[100];
	bzero(tcp_ip, sizeof tcp_ip);
	
	switch(choo)
	{
		
		//测试AT启动
		case '1':strcpy(choose, "AT\r\n");
				write(fd, choose, strlen(choose));
				break;
		
		case '2':strcpy(choose, "AT+RST\r\n");
				write(fd, choose, strlen(choose));
				break;
		//启用热点工作模式
		case '3':strcpy(choose, "AT+CWMODE=2\r\n");
				write(fd, choose, strlen(choose));
				break;
		
		case '4':strcpy(choose, "AT+RST\r\n");
				write(fd, choose, strlen(choose));
				break;
		
		//WiFi名字，密码，通道号，WPA2_PSK
		case '5':strcpy(choose, "AT+CWSAP=\"ZHAN\",\"12345678\",11,3\r\n");
				write(fd, choose, strlen(choose));
				break;
		
		//多路链接
		case '6':strcpy(choose, "AT+CIPMUX=1\r\n");
				write(fd, choose, strlen(choose));
				break;
		//设置为服务器模式，端口为8080
		case '7':strcpy(choose, "AT+CIPSERVER=1,8080\r\n");
				write(fd, choose, strlen(choose));
				break;
		//返回本WiFi模块的IP
		case '8':strcpy(choose, "AT+CIFSR\r\n");
				write(fd, choose, strlen(choose));
				break;
		//查看已链接的设备的IP地址
		case 'l':
				strcpy(choose, "AT+CWLIF\r\n");
				write(fd, choose, strlen(choose));
				break;
		
		//==================================================
		case 't':
				while(1)
				{
					printf("input tcp ip to connect\n");
					rets = scanf("%s", tcp_ip);
					if(rets != 1)
					{
						while(getchar() != '\n');
						continue;
					}
					else
						break;
				}
				char com[100];
				bzero(com, sizeof com);
				sprintf(com, "AT+CIPSTART=\"TCP\",\"%s\",8080\r\n", tcp_ip);
				write(fd, com, strlen(com));
				break;
				
		case 'z':
				strcpy(choose, "AT+CIPSEND=10\r\n");
				write(fd, choose, strlen(choose));
				getchar();
				while(1)
				{
					bzero(buf, sizeof buf);
					scanf("%s", buf);
					if(strncasecmp(buf, "quit", 4) == 0)
						break;
					else
						write(fd, buf, strlen(buf));
				}
				break;
		case 's':
				strcpy(choose, "AT+CIPSEND\r\n");
				write(fd, choose, strlen(choose));
				getchar();
				while(1)
				{
					bzero(buf, sizeof buf);
					scanf("%s", buf);
					if(strncasecmp(buf, "quit", 4) == 0)
						break;
					else
						write(fd, buf, strlen(buf));
				}
				break;
		case 'c':
				strcpy(choose, "AT+CIPCLOSE=5\r\n");
				write(fd, choose, strlen(choose));		
				break;
		case 'q':exit(0);
	}
	
}


void menu_mode2(char *choose1, int fd)
{
	//assert(choose);
	
	char choose[100];
	bzero(choose, sizeof choose);

	int ret = -1;
	char choo;
	
	char buf[100];
	
	while(1)
	{
		//printf("mode2:what do you want?\n");
		scanf("%c", &choo);
		if(ret != 1)
		{
			while(getchar() != '\n');
			continue;
		}
		else
			break;
	}
	
	char name[100];
	bzero(name, sizeof name);
	char password[100];
	bzero(password, sizeof password);
	char tcp_ip[100];
	bzero(tcp_ip, sizeof tcp_ip);
	char com[100];
	bzero(com , sizeof com);
	int rets;
	
	switch(choo)
	{
		
		//测试AT启动
		case '1':strcpy(choose, "AT\r\n");
				write(fd, choose, strlen(choose));
				break;
		case '2':strcpy(choose, "AT+RST\r\n");
				write(fd, choose, strlen(choose));
				break;
		//启用从端工作模式
		case '3':strcpy(choose, "AT+CWMODE=1\r\n");
				write(fd, choose, strlen(choose));
				break;
		case '4':strcpy(choose, "AT+RST\r\n");
				write(fd, choose, strlen(choose));
				break;
		//显示附近WiFi
		case '5':strcpy(choose, "AT+CWLAP\r\n");
				write(fd, choose, strlen(choose));
				break;
		//链接热点
		case '6':
				while(1)
				{
					printf("input wifi name and password\n");
					rets = scanf("%s%s", name, password);
					if(rets != 2)
					{
						while(getchar() != '\n');
						continue;
					}
					else
						break;
				}
				sprintf(com, "AT+CWJAP=\"%s\",\"%s\"\r\n", name, password);
				write(fd, choose, strlen(choose));
				break;
		//返回本WiFi模块的IP
		case '7':
				strcpy(choose, "AT+CIFSR\r\n");
				write(fd, choose, strlen(choose));break;
		//关闭TCP或者UDP
		case 'c':
				strcpy(choose, "AT+CIPCLOSE\r\n");
				write(fd, choose, strlen(choose));
				break;
		//发起单路链接请求
		case '8':
				while(1)
				{
					printf("input tcp ip to connect\n");
					rets = scanf("%s", tcp_ip);
					if(rets != 1)
					{
						while(getchar() != '\n');
						continue;
					}
					else
						break;
				}
				bzero(com, sizeof com);
				sprintf(com, "AT+CIPSTART=\"TCP\",\"%s\",8080\r\n", tcp_ip);
				write(fd, com, strlen(com));break;
		//给对方发送10个字节的数据
		case '9':
				strcpy(choose, "AT+CIPSEND=10\r\n");
				write(fd, choose, strlen(choose));
				getchar();
				while(1)
				{
					bzero(buf, sizeof buf);
					scanf("%s", buf);
					if(strncasecmp(buf, "quit", 4) == 0)
						break;
					else
						write(fd, buf, strlen(buf));
				}
				
				break;
		case '0':
				strcpy(choose, "AT+CWQAP\r\n");
				write(fd, choose, strlen(choose));
				break;
		//发送数据
		case 's':
				strcpy(choose, "AT+CIPSEND\r\n");
				write(fd, choose, strlen(choose));
				getchar();
				while(1)
				{
					bzero(buf, sizeof buf);
					scanf("%s", buf);
					if(strncasecmp(buf, "quit", 4) == 0)
						break;
					else
						write(fd, buf, strlen(buf));
				}
				break;
				
		case 'q':exit(0);
	}
	
}






















