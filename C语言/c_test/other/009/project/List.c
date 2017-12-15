#include "List.h"

/* 从文件中读取学生数据 */
static int Read(FILE *fp,void *node)
{
	int Ret;
	pNode_Stu p = (pNode_Stu) node;
	Ret = fscanf(fp,"%s%d%d%d%d",p -> Name,&(p -> Score[0]),&(p -> Score[1]),&(p -> Score[2]),&(p -> Number));
	p -> Score[3] = p -> Score[0] + p -> Score[1]+ p -> Score[2];
	p -> avg = p -> Score[3]/3.0;
	p -> rank = 0;
	return Ret;
}

/* 向链表中插入数据 */
pList Insert_List(pList p,int Chi,int Math,int Eng,int num,char *name)
{
	FILE *fp = fopen("student.txt","a+");
	fseek(fp,0,SEEK_END);
	pList New;
	pNode_Stu Stu_Node;
	pList temp = p;
	pList Head = p;
	char Str_Input[100];
	if(p == NULL)
		return NULL;
	
	New  = (pList)malloc(sizeof(List));
	Stu_Node = (pNode_Stu)malloc(sizeof(Node_Stu));
	
	strcpy(Stu_Node -> Name,name);        //填充数据域
	Stu_Node -> Score[0] = Chi;
	Stu_Node -> Score[1] = Math;
	Stu_Node -> Score[2] = Eng;
	Stu_Node -> Number = num;
	Stu_Node -> Score[3] = Stu_Node -> Score[0]+Stu_Node -> Score[1]+Stu_Node -> Score[2];
	Stu_Node -> avg = Stu_Node -> Score[3]/3.0;
	Stu_Node -> rank = 0;	
	
	New -> Data  = Stu_Node;	
	New -> next = Head;	
	
	//在文件中写入新的条目
	sprintf(Str_Input,"%s %d %d %d %d\r\n",New -> Data -> Name,New -> Data -> Score[0],New -> Data -> Score[1],New -> Data -> Score[2],New -> Data -> Number);
	fwrite(Str_Input,strlen(Str_Input),1,fp);
	fclose(fp);
	
	return New;

}

/* 从链表中删除数据 */
pList Del_List(pList list,pList list_del)
{
	FILE *fp = fopen("student.txt","r");
	FILE *temp = fopen("temp.txt","w");
	pList Head = list;
	pList Last = NULL;
	while(list_del != NULL)                                 //从目标链表中删除子链表
	{
		while(list != NULL)
		{
			if(Last == NULL)                                //要删除的是表头
			{
				if(list -> Data == list_del -> Data)
				{
					Last = list -> next;
					free(list);
					Head = Last;
				}
			}
			else                                             //要删除的不是表头
			{
				if(list -> Data == list_del -> Data)
				{
					Last -> next = list -> next;
					free(list);
				}
			}
			Last = list;                                      //Last始终指向上一个节点
			list = list -> next;

		}
		list = Head;
		list_del = list_del -> next;
	}
	
	while(list != NULL)                                     //将新链表的内容存入文件
	{
		char Str_Input[100];
		sprintf(Str_Input,"%s %d %d %d %d\r\n",list -> Data -> Name,list -> Data -> Score[0],list -> Data -> Score[1],list -> Data -> Score[2],list -> Data -> Number);
		fwrite(Str_Input,strlen(Str_Input),1,temp);
		list = list -> next;
	}
	fclose(temp);                                             //删除原文件并重命名新文件
	fclose(fp);
	remove("student.txt");
	rename("temp.txt","student.txt");
	
	return Head;
}

int Change_List(pList list,int type,char *str,int num,int i)
{
	int j = 1;
	pList Head = list;
	pList Head1 = list;
	FILE *fp,*temp;
	fp = fopen("student.txt","r");
	temp = fopen("temp.txt","w");
	for(j;j<i;j++)
	{
		list = list -> next;
	}
	
	if(type == 0)                //如果修改了学号，需要判断有没有重复。
	{
		while(Head != NULL)
		{
			if(num == Head -> Data -> Number)
				return -1;
			Head = Head -> next;
		}		
	}
	if(type >1&&type < 5)        //如果修改了单项成绩，需要判断数据合法性
	{
		if(num > 100||num < 0)
		{
			return -1;
		}
	}
	switch(type)
	{
		case 0:
			list -> Data -> Number = num;break;
		case 1:
			memset(list -> Data -> Name,0,16);
			strcpy(list -> Data -> Name,str);break;
		case 2:
			list -> Data -> Score[0] = num;break;
		case 3:
			list -> Data -> Score[1] = num;break;
		case 4:
			list -> Data -> Score[2] = num;break;		
	}
	

	if(type > 1)                //如果修改了单项成绩，需重新计算总分，平均分和排名
	{
		list -> Data -> Score[3] = list -> Data -> Score[0] + list -> Data -> Score[1]+ list -> Data -> Score[2];
		list -> Data -> avg = list -> Data -> Score[3]/3.0;
		Sort_List(list,NULL,3,0);
	}
	
	while(Head1 != NULL)                                     //将新链表的内容存入文件
	{
		char Str_Input[100];
		sprintf(Str_Input,"%s %d %d %d %d\r\n",Head1 -> Data -> Name,Head1 -> Data -> Score[0],Head1 -> Data -> Score[1],Head1 -> Data -> Score[2],Head1 -> Data -> Number);
		fwrite(Str_Input,strlen(Str_Input),1,temp);
		Head1 = Head1 -> next;
	}
	fclose(temp);                                             //删除原文件并重命名新文件
	fclose(fp);
	remove("student.txt");
	rename("temp.txt","student.txt");			
	
	return 1;
	
}

/* 从学生链表中搜索指定数据，并且生成新的链表并返回 */
pList Search_StuList(pList list,int type,int Max,int Min,char *str)
{
	pList Head,New;
	int temp;
	Head = NULL;
	if(type == 1)                                                //搜索字符串(名字)
	{
		while(list != NULL)
		{
			//getch();
			
			if(strcmp(str,list -> Data -> Name) == 0)
			{
				New = (pList)malloc(sizeof(List));
				New -> Data = list -> Data;
				New -> next = Head;
				Head = New;
			}
			list = list -> next;
		}
	}
	else if((type >= 2&&type < 8) || type == 0)                  //搜索数字
	{
		if(Max == -1)                                             //只输入了一个数字
		{
			Max = Min;
		}
		while(list != NULL)
		{
			
			switch(type)                                             //选择搜索的内容
			{
				case 0:
					temp = list -> Data -> Number;break;
				case 2:
					temp = list -> Data -> Score[0];break;
				case 3:
					temp = list -> Data -> Score[1];break;
				case 4:
					temp = list -> Data -> Score[2];break;
				case 5:
					temp = list -> Data -> Score[3];break;
				case 6:
					temp = (int)list -> Data -> avg;break;
				case 7:
					temp = list -> Data -> rank;break;
			}
			
			if(temp >= Min&&temp <= Max)
			{
				//printf("%d\n",temp);
				New = (pList)malloc(sizeof(List));
				New -> Data = list -> Data;
				New -> next = Head;
				Head = New;								
			}
			list = list -> next;
			
		}
	}
	else
	{
		return NULL;
	}
	return Head;
	
	
}

/* 将已有的数据生成链表 */
pList Creat_List()
{
	FILE *fp = fopen("student.txt","r+");
	if(fp == NULL)
	{
		printf("File open failed\n");
		return NULL;
	}
	
	pList Stu_Head,New;
	Stu_Head = NULL;
	
	pNode_Stu Stu_Node   = malloc(sizeof(Node_Stu));
	
	while(Read(fp,Stu_Node) != EOF)                 //头插法
	{
		New  = (pList)malloc(sizeof(List));
		New -> Data = Stu_Node;
		New -> next = Stu_Head;
        Stu_Head = New;
		Stu_Node   = malloc(sizeof(Node_Stu));	
	}		

	fclose(fp);
	
	return Stu_Head;
}


/* 交换两个结构体中的数据 */
static void Swap(Node_Stu **a,Node_Stu **b)
{
	Node_Stu *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
/* 将链表排序 */
void Sort_List(pList Head,pList End,int type,int Dir)         // type  0：语文 1：数学 2：英语 3：总分
{                                                             //  Dir   0: 升序 1：降序
	if(Head == NULL)
		return;
	if(Head == End)
		return;
	if(type<0 || type > 3)
		return;
	
	pList Next,Last;
	Last = Head;
	Next = Head -> next;
	while(Next != End)
	{
		if(Dir == 0)
		{
			if(Next -> Data -> Score[type] > Head -> Data -> Score[type])
		    {
			    Last = Last -> next;
			    Swap(&(Last -> Data),&(Next -> Data));
		    }
		}
		else
		{
			if(Next -> Data -> Score[type] < Head -> Data -> Score[type])
		    {
			    Last = Last -> next;
			    Swap(&(Last -> Data),&(Next -> Data));
		    }
		}
		Next = Next -> next;
	}
	Swap(&(Last -> Data),&(Head -> Data));
	Sort_List(Head,Last,type,Dir);
	Sort_List(Last -> next,NULL,type,Dir);
	
	if(Dir == 0&&type == 3)
	{
		int i = 1;
		while(Head != NULL)
		{
			Head -> Data -> rank = i;
			i++;
			Head = Head -> next;
		}
	}
}

