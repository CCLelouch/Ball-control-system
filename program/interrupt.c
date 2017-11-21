#include"interrupt.h"
#include"pid.h"
#include "PWM.H"
#include"system.h"

unsigned int buf=0,distance=0; 

/********************************************************************************
** ��������
** ���ܣ�
** ˵����ÿ0.5 uS������
** �޸����ڣ�2017-00-00
** ���ߣ�c.c. 
*********************************************************************************/
void int_external0_init()
{
//	AUXR = 0x00;				 //���ö�ʱ��0�ٶ��Ǵ�ͳ8051��Ƭ���ٶ�	     Ĭ��
	AUXR = 0x80;				 //���ö�ʱ��0�ٶ��Ǵ�ͳ8051��Ƭ���ٶȵ�12����1T   ��Ҫ�û���������

//	IE0 = 0;
	IE1 = 0;					//����ⲿ�ж�0/1�жϱ�־λ
//	EX0 = 1;
	EX1 = 1;					//�����ⲿ�ж�0/1�����ж�

//	IT0 = 0;					//�����ⲿ�ж�0Ϊ�½����������ؾ��ɴ���
//	IT0 = 1;					//�����ⲿ�ж�0Ϊ�½��ش���

	IT1 = 0;					//�����ⲿ�ж�1Ϊ�½����������ؾ��ɴ���
//	IT1 = 1;					//�����ⲿ�ж�1Ϊ�½��ش���

	EA   = 1;					 //������Ƭ�����ж�
	PX1 = 1;
}

void INT1_Int (void) interrupt 2		 //INT0/P3.3/**/4
{ 
	if(P33==1)
	{
	 	TR1 = 1;	
	}//P00�˿�LED������/��״̬
	else
	{
		TR1 = 0;
		buf=(unsigned int)TH1<<8|TL1;	 //��ȡ��ʱ������
		TH1   =0x00; 
	  TL1   =0x00;
	
  	distance=(float)buf/200;//����ת��Ϊ���룬��ʱ����һ��ʱ��Ϊ12/11.0592������us������=ʱ��(us)/10

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


