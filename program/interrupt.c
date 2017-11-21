#include"interrupt.h"
#include"pid.h"
#include "PWM.H"
#include"system.h"

unsigned int buf=0,distance=0; 

/********************************************************************************
** 函数名：
** 功能：
** 说明：每0.5 uS进入中
** 修改日期：2017-00-00
** 作者：c.c. 
*********************************************************************************/
void int_external0_init()
{
//	AUXR = 0x00;				 //设置定时器0速度是传统8051单片机速度	     默认
	AUXR = 0x80;				 //设置定时器0速度是传统8051单片机速度的12倍即1T   需要用户另外设置

//	IE0 = 0;
	IE1 = 0;					//清除外部中断0/1中断标志位
//	EX0 = 1;
	EX1 = 1;					//允许外部中断0/1产生中断

//	IT0 = 0;					//设置外部中断0为下降沿与上升沿均可触发
//	IT0 = 1;					//设置外部中断0为下降沿触发

	IT1 = 0;					//设置外部中断1为下降沿与上升沿均可触发
//	IT1 = 1;					//设置外部中断1为下降沿触发

	EA   = 1;					 //启动单片机总中断
	PX1 = 1;
}

void INT1_Int (void) interrupt 2		 //INT0/P3.3/**/4
{ 
	if(P33==1)
	{
	 	TR1 = 1;	
	}//P00端口LED处于亮/灭状态
	else
	{
		TR1 = 0;
		buf=(unsigned int)TH1<<8|TL1;	 //读取定时器计数
		TH1   =0x00; 
	  TL1   =0x00;
	
  	distance=(float)buf/200;//数据转换为距离，定时器计一次时间为12/11.0592（晶振）us，距离=时间(us)/10

	}
	P6=~P6;
	if(distance<100)
	actual_dis=(23-(int)distance);
}

void int_timer0() interrupt 1
{
	pid.Ctime++;		
	flag++;
	System_refresh.set_Distance_fresh++;
	System_refresh.action1_fresh++;
	System_refresh.action2_fresh++;
	System_refresh.action3_fresh++;
}


