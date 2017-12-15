#ifndef __INTERFACE_H
#define __INTERFACE_H

#include <curses.h>
#include <string.h>
#include "List.h"

void Initial();                         //初始化界面
int Draw(pList list,int Y,int X);         //绘制内容
pList Search_Stu(pList list,int type);   //搜索学生数据   0：学号 1：名字 2,3,4：单项成绩区间（语数外）
                                         //              5：总分 6：平均分 7：排名区间






#endif  /* __INTERFACE_H */



