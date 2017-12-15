#ifndef __DATA_STRUCT_H
#define __DATA_STRUCT_H
//头文件
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

//定义宏
#define SIZE 100

//节点设计,数据类型的原型
typedef struct sqlist
{
	int data[SIZE];	
	int lenght;
}Sqlist;

//创建一个学生表
Sqlist *create_sqlist(void);

//插入数据
bool insert_sqlist(Sqlist *list, int data);
//删除数据
bool delete_sqlist(Sqlist *list, int data);

//显示数据
void show_sqlist(Sqlist *list);

//查找数据
int search_sqlist(Sqlist *list, int data);



#endif
