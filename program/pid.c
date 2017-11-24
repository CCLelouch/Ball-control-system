//#include"head.h"
#include"pid.h"
#include "PWM.H"

#define OUT0 1000

PID pid;

void PID_init()//���pid
{
	pid.Sv = 0;
	pid.Pv = 0;
	pid.Kp = 0;
	pid.Ki = 0;
	pid.Kd = 0;

	pid.Ek   = 0;
	pid.Ek_1 = 0;
	pid.Ek_2 = 0;

	pid.Pout = 0;
	pid.Iout = 0;				
	pid.Dout = 0;

	pid.OUT   = 50;
	pid.Ctime = 0;
	pid.pwm   = CYCLE;
	
	pid.T = 20;
}

void PID_setpara(float kp,float ki,float kd)
{
 	pid.Kp = kp;
	pid.Ki = ki;
	pid.Kd = kd;
}

uint PID_Calculate(unsigned int sv,float pv)
{
	unsigned int out;

//	if(pid.Ctime<pid.T)
//		{
//			return 0;
//		}

	P22 = 0;
	P22 = 1;

	pid.Sv = sv;
	pid.Pv = pv;

	pid.Ek = pid.Sv-pid.Pv;//��ǰ���ֵ

///*P*/
//	pid.Pout = pid.Kp*(pid.Ek-pid.Ek_1);//�������
///*I*/
//	pid.Iout = pid.Ki*pid.Ek;//�������
///*D*/
//	pid.Dout = pid.Kd*(pid.Ek-pid.Ek_1<<1+pid.Ek_2);//΢�����
//
//	out=(uint)(pid.Pout + pid.Iout + pid.Dout);

 	pid.Pout = pid.Kp*pid.Ek;

	if(out>pid.pwm)
	{
		pid.OUT = pid.pwm-1;
	}
	else if(out<=0)
	{
		pid.OUT = OUT0;
	}
	else 
		pid.OUT = out;//���pid

	pid.Ek_1 = pid.Ek;
	pid.Ek_2 = pid.Ek_1;

	pid.Ctime = 0;//����ۼ�ֵ
	return pid.OUT;//pid.OUT;
}











