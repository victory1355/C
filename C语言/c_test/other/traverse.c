#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <curses.h>
#include "list.h"

#define MAX_PATH 200

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

//创建音乐信息链表
int creat_file_list_music(File_info *head, char *name, int size, char *path);
//提取MP3和JPG图片,并建立一条链表
int tree_find_file(char *dir ,  File_info *head_photo, File_info *head_music);
int travel_list(File_info *head);


//创建图片信息链表
int creat_file_list_photo(File_info *head, char *name, int size, char *path);

//创建表头
File_info * create_file_head();

//创建音乐信息链表
int creat_file_list_music(File_info *head, char *name, int size, char *path);






//提取MP3和JPG图片,并建立一条链表
int tree_find_file(char *dir ,  File_info *head_photo, File_info *head_music)
{ 
	if(dir == NULL)
		return -1;
	if(head_photo == NULL)
		return -1;
	if(head_music == NULL)
		return -1;
    //打开目录指针 
    DIR *Dp; 
    //文件目录结构体 
    struct dirent *enty; 
    //详细文件信息结构体 
  //  struct stat statbuf; 
    //打开指定的目录，获得目录指针 
    if(NULL == (Dp = opendir(dir))) 
    { 
        perror(" open dir fail"); 
        return -1; 
    } 
    //遍历这个目录下的所有文件 
	while(NULL != (enty = readdir(Dp)))
	{
		//printf("hello1\n");
		//bzero(&statbuf, sizeof(statbuf));
			//通过文件名，得到详细文件信息 
		//stat(enty->d_name,&statbuf); 
				//判断是不是目录 
		if(GH->d_type == DT_DIR) 
		{    			
			if(0 == strcmp(".",enty->d_name) || 0 == strcmp("..",enty->d_name)) //当前目录和上一目录过滤掉 
			{ 
				continue; 
			} 
			char path_buf[MAX_PATH];
			char ch = '/';
			char *p = strrchr(dir,ch);
			int flag = strcasecmp(p, "/");
			if(flag ==0)
			{
				bzero(path_buf, sizeof(path_buf));
				sprintf(path_buf, "%s%s", dir, enty->d_name);
				printf("path_buf = %s\n", path_buf);
			}
			else 
			{
				bzero(path_buf, sizeof(path_buf));
				sprintf(path_buf, "%s/%s", dir, enty->d_name);
			}
			printf("%s\n", path_buf);
				
			//继续递归调用        
			tree_find_file(path_buf, head_photo, head_music); 
		} 
		else
		{     
			//判断是不是mp3或者jpg
			char *name = enty->d_name;
			char *p = strrchr(name, '.');
			if(p != NULL)
			{
				if(strcasecmp(p , ".jpg")==0)
				{					
					//创建图片链表
					char path_photo[MAX_PATH];
					char ch_p = '/';
					char *p_p = strrchr(dir,ch_p);
					int flag_p = strcasecmp(p_p, "/");
					if(flag_p == 0)
					{
						bzero(path_photo, sizeof(path_photo));
						sprintf(path_photo, "%s%s", dir, enty->d_name); 
						
					}
					else 
					{
						bzero(path_photo, sizeof(path_photo));
						sprintf(path_photo, "%s/%s", dir, enty->d_name);
					}
								
					creat_file_list_photo(head_photo, enty->d_name, enty->d_reclen, path_photo);//出现段错误				
				}
				if(strcasecmp(p , ".mp3")==0)
				{					
					//创建MP3链表
					char path_music[MAX_PATH];
					//判断是否为当前目录或者根目录
					char ch_m = '/';
					char *p_m = strrchr(dir,ch_m);
					int flag_m = strcasecmp(p_m, "/");
					if(flag_m == 0)
					{
						bzero(path_music , sizeof(path_music));
						sprintf(path_music, "%s%s", dir, enty->d_name); 
						printf("path_music = %s\n", path_music);
					}
					else 
					{
						bzero(path_music, sizeof(path_music));
						sprintf(path_music, "%s/%s", dir, enty->d_name);
						printf("path_music = %s\n", path_music);						
						
					}
					
					creat_file_list_music(head_music, enty->d_name, enty->d_reclen, path_music);		
				}	
			}
		}
	}  
	perror("readdir fail");
	printf("hello\n");
    //closedir(Dp); 
	return 0;
} 
int travel_list(File_info *head)
{
	//printf("flag4\n");
	struct list_head *pos=NULL;
	if(head == NULL)
		return -1;
	list_for_each(pos, &head->list)
	{
		//printf("flag5\n");
		File_info *file = list_entry(pos, File_info, list);
		printf("name:%s size:%d path:%s\n", file->file_group.file_name, file->file_group.file_size, file->file_group.path);
	}
	//printf("flag6\n");//段错误的地方
	
}

//创建表头
File_info * create_file_head()
{
	
		File_info *head =(File_info *) malloc(sizeof(File_info));
		if(head == NULL)
			return NULL;
		INIT_LIST_HEAD(&head->list);
		return head;
}
//创建图片信息链表
int creat_file_list_photo(File_info *head, char *name, int size, char *path)
{
	if(head == NULL)
		return -1;
	if(name == NULL)
		return -1;
	if(path == NULL)
		return -1;
	File_info * node = (File_info *)malloc(sizeof(File_info));
	if(node == NULL)
		return -1;
	INIT_LIST_HEAD(&node->list);	
	node->file_group.file_size = size;
	strcpy(node->file_group.file_name, name);
	strcpy(node->file_group.path, path);
	//插入表头	
	list_add(&node->list, &head->list);
	return 0;
}
//创建音乐信息链表
int creat_file_list_music(File_info *head, char *name, int size, char *path)
{
	if(head == NULL)
		return -1;
	if(name == NULL)
		return -1;
	if(path == NULL)
		return -1;
		
	File_info * node = (File_info *)malloc(sizeof(File_info));
	if(node == NULL)
		return -1;
	INIT_LIST_HEAD(&node->list);
	
	node->file_group.file_size = size;
	strcpy(node->file_group.file_name, name);	
	strcpy(node->file_group.path, path);
	//插入表头	
	list_add(&node->list, &head->list);    //出现段错误	
	return 0;
}

int main(int argc, char *argv[])
{
	File_info *music_head, *photo_head;
	music_head = create_file_head();
	if(music_head == NULL)
	{
		perror("create_file_head fail");
		return -1;
	}
	photo_head = create_file_head();
	if(photo_head == NULL)
	{
		perror("create_file_head fail");
		return -1;
	}
	//
	tree_find_file(argv[1], photo_head, music_head);
	printf("flag\n");
	travel_list(photo_head);
	travel_list(music_head);
	
	return 0;
}




















