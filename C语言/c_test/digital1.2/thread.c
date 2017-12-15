#include "digital.h"

//负责不断检测U盘和挂载U盘
void *found_usb_thread(void *arg)
{
	//检测U盘并挂载
	signal(SIGALRM, found_usb);
	while(1)
	{
		//挂载成功后退出程序
		if(flag_usb == 10)
			raise(SIGALRM);
		//定时检测
		sleep(5);	
		if(flag_usb == 11)
		{
			break;
		}
	}	
	//唤醒另外两个进程
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}

//负责用户交互
void *user_control_thread(void *arg)
{
	//进入睡眠直到被唤醒
	pthread_cond_wait(&cond, &mutex);
	
	//进入用户交互
	key_control(head_music ,head_photo);
	
	pthread_exit(NULL);
	
}
//负责数据的打印和刷新
void *print_list_thread(void *arg)
{
	//如果没有检测到U盘则睡眠
	pthread_cond_wait(&cond, &mutex);
	
	//刷新终端
	print();
	print_node_content_music(head_music);
	print_node_content_photo(head_photo);	
	
	//退出
	pthread_exit(NULL);
}
