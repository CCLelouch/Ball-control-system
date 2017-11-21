#ifndef _PID_H
#define _PID_H
#include "stc15w.h"
//#include"head.h"

typedef struct
{
 	unsigned char Sv;//设定值
	float Pv;//当前值

	float Kp;//比例系数
	float Ki;//积分系数
	float Kd;//微分系数

	unsigned int Ek;//本次偏差值
	unsigned int Ek_1;//上次偏差值
	unsigned int Ek_2;

	unsigned int Pout;
	unsigned int Iout;
	unsigned int Dout;
	
	unsigned int OUT;
	unsigned int pwm;

	unsigned char Ctime;//存放累计值
	unsigned char T;		 //采样周期

}PID;

extern PID pid;

extern uchar ;
extern uint;

/*PID外接函数*/
void PID_init();//清空pid
void PID_setpara(float kp,float ki,float kd);//参数：比例系数，积分系数，微分系数
uint PID_Calculate(unsigned int sv,float pv,unsigned char gain);//参数：设定值，当前值，输入1获取PWM但不运算（缺省或0运算并获取PWM）

#endif















