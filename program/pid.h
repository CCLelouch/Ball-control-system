#ifndef _PID_H
#define _PID_H
#include "stc15w.h"
//#include"head.h"

typedef struct
{
 	unsigned char Sv;//�趨ֵ
	float Pv;//��ǰֵ

	float Kp;//����ϵ��
	float Ki;//����ϵ��
	float Kd;//΢��ϵ��

	unsigned int Ek;//����ƫ��ֵ
	unsigned int Ek_1;//�ϴ�ƫ��ֵ
	unsigned int Ek_2;

	unsigned int Pout;
	unsigned int Iout;
	unsigned int Dout;
	
	unsigned int OUT;
	unsigned int pwm;

	unsigned char Ctime;//����ۼ�ֵ
	unsigned char T;		 //��������

}PID;

extern PID pid;

extern uchar ;
extern uint;

/*PID��Ӻ���*/
void PID_init();//���pid
void PID_setpara(float kp,float ki,float kd);//����������ϵ��������ϵ����΢��ϵ��
uint PID_Calculate(unsigned int sv,float pv,unsigned char gain);//�������趨ֵ����ǰֵ������1��ȡPWM�������㣨ȱʡ��0���㲢��ȡPWM��

#endif















