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

#include <dirent.h>



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
		//fprintf(stderr, "%s\n", msg);
		printf("\nRX:%s\n", msg);
	}
	free(msg);
	
}



int main(void)
{
	char *device1 = "/dev/ttySAC1";
	//char *device2 = "/dev/ttySAC2";

	// 1，打开指定的串口设备节点，并初始化
	int fd1 = open(device1, O_RDWR|O_NOCTTY);
	if(fd1 == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				device1, strerror(errno));
		exit(0);
	}
/*	int fd2 = open(device2, O_RDWR|O_NOCTTY);
	if(fd2 == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				device2, strerror(errno));
		exit(0);
	}
*/	//2，配置串口
	init_tty(fd1);
//	init_tty(fd2);
	
	
	// ============ 独立线程读取串口信息 ============== //
	pthread_t tid1;
//	pthread_t tid2;
	pthread_create(&tid1, NULL, routine, (void*)fd1);
	//pthread_create(&tid2, NULL, routine, (void*)fd2);


	// ============ 主线程发送信息给串口 ============ //
	int n;
	char buf[100];
	bzero(buf, sizeof buf);
	
	while(1)
	{
		printf("input the data:");
		fgets(buf, sizeof buf, stdin);
		if( write(fd1, buf, strlen(buf)) == -1)
		{
			perror("write ");
			return -1;
		}
	}

	return 0;
}
