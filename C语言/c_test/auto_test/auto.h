#ifndef __AUTO_H
#define __AUTO_H

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include "list.h"
#include <errno.h>
#include <signal.h>
#include <strings.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>

//-----------------------------------------------------------------------
//图片，音乐链表的数据结构
struct file
{
	char path[100];  //文件所在的路径
	char file_name[50];
	unsigned short file_size;
};
typedef struct file_info
{
	struct file file_group;
	struct list_head list;      //内核链表，记住不要定义为指针类型
}File_info;

//两个表头全局变量
File_info *head_photo;
File_info *head_music;

//自动模式的控制变量
int flag_stop;
int flag_continue;
int flag_exit;
int flag_work;

//路径的最大长度
#define MAX_PATH   200

//信号处理函数
void stop_music_photo(int sig);
void continue_music_photo(int sig);
void exit_auto(int sig);

//进入自动模式
int auto_model(File_info *head_music1, File_info *head_photo1);
//发送信号
int send_signal();
//浏览图片
int  brower_photo(File_info *photo_head2) ;



//提取MP3和JPG图片,并建立两条链表
void tree_find_file(char *dir ,File_info *head_photo, File_info *head_music);
//创建表头
File_info * create_file_head(void);
//创建图片信息链表
int creat_file_list_photo(File_info *head, char *name, int size, char *path);
//------------------------------------------------------------------------
//遍历链表,使用回调函数，多次使用
void travel_list(File_info *head);


#endif