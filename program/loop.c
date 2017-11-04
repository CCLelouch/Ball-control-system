/********************************************************************************
** 文件名：
** 功能：
** 说明：
** 修改日期：2017-00-00
** 作者：c.c. 
*********************************************************************************/
#include"head.h"
#include"lcd12864.h"
#include"Delay.H"
#include"system.h"	
#include "buzzer.h"

void STC15W_IOinit(void)
{
	P0M1 = 0;	P0M0 = 0;	
	P1M1 = 0;	P1M0 = 0;	
	P2M1 = 0;	P2M0 = 0;
	P3M1 = 0;	P3M0 = 0;		   
	P4M1 = 0;	P4M0 = 0;	
	P5M1 = 0;	P5M0 = 0;	
	P6M1 = 0;	P6M0 = 0;	
	P7M1 = 0;	P7M0 = 0;	
}

void main()
{ 
	STC15W_IOinit();
	LCD12864_init();
	while(1)
	{
		System_init();
		
	}	
}



