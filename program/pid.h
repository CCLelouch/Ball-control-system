#ifndef _PID_H
#define _PID_H
#include "stc15w.h"
//#include"head.h"

typedef struct
{
 	char Sv;//�趨ֵ
	char Pv;//��ǰֵ

	float Kp;//����ϵ��
	float Ki;//����ϵ��
	float Kd;//΢��ϵ��

	unsigned int Ek;//����ƫ��ֵ
	unsigned int Ek_1;//�ϴ�ƫ��ֵ
	unsigned int Ek_2;

	float Pout;
	float Iout;
	float Dout;
	
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
uint PID_Calculate(unsigned int sv,float pv);//�������趨ֵ����ǰֵ������1��ȡPWM�������㣨ȱʡ��0���㲢��ȡPWM��

#endif















