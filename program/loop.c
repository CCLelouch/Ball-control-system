/********************************************************************************
** �ļ�����С�����ϵͳ
** ���ܣ�
** ˵��������ӿ�P33
** �޸����ڣ�2017-00-00
** ���ߣ�c.c. 
*********************************************************************************/
#include"head.h"
#include"lcd12864.h"
#include"Delay.H"
#include"Uart2.H"
#include"system.h"	
#include"buzzer.h"
#include"PWM.H"
#include"pid.h"
#include"interrupt.h"
#include"timer.h"
					
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
	P0 = 0XFF;	P1 = 0XFF;	P2 = 0XFF; 
	P3 = 0XFF;	P4 = 0XFF;	P5 = 0XFF; 
	P6 = 0XFF;	P7 = 0XFF;
}

void main()
{ 
	STC15W_IOinit();
	PWM_init();
	LCD12864_init();
	PID_init();//���pid
	timer0_init();
	int_timer0_init();
	timer1_init();
	int_external0_init();
	while(1)
	{
		System();		
	}	
}



