#ifndef __Uart2_H
#define __Uart2_H 
#include<STC15W.H>	
	


extern bit Sensor_Data_Flag;
extern uint  Sensor_Data[5];

extern void Uart2_Init(void);					//����1ʹ�ö�ʱ��T1���������ʳ�ʼ������
extern void Uart2_SendData(uchar dat);			//����1�������ݺ���
extern void Uart2_SendString(uchar *s);		//����1�����ַ�������

#endif












