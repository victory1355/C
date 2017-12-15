#ifndef __LIST_
#define __LIST_

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Node_Stu           //学生数据结构体
{
	char Name[16];
	int  Score[4];                //0：语文 1：数学 2：英语 3：总成绩
	float avg;
	int  Number;
	int  rank;
}Node_Stu,*pNode_Stu;

typedef struct List
{
	pNode_Stu Data;
	struct List *next;
}List,*pList;

pList Creat_List();
pList Insert_List(pList p,int Chi,int Math,int Eng,int num,char *name);
pList Del_List(pList p,pList Del);
int Change_List(pList list,int type,char *str,int num,int i);
void Sort_List(pList Head,pList End,int type,int Dir);
pList Search_StuList(pList list,int type,int Max,int Min,char *str);


#endif    /* __LIST_ */

