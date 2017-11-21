#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include "head.h"

 

typedef enum//系统状态枚举
{
 	init,
	set_distance,
	action1,
	action2,
	action3
}State;

typedef struct//屏幕刷新时间结构体
{
	uchar T;
	uchar set_Distance_fresh;
	uchar action1_fresh;
	uchar action2_fresh;
	uchar action3_fresh;
}Refresh;

extern State System_State;
extern Refresh System_refresh;
extern char set_buff;
extern int actual_dis;


void System();
void Set_Distance();
void Action1();
void Action2();
void Action3();
extern int flag;
#endif



