#ifndef __Uart2_H
#define __Uart2_H 
#include<STC15W.H>	
	


extern bit Sensor_Data_Flag;
extern uint  Sensor_Data[5];

extern void Uart2_Init(void);					//串口1使用定时器T1产生波特率初始化函数
extern void Uart2_SendData(uchar dat);			//串口1发送数据函数
extern void Uart2_SendString(uchar *s);		//串口1发送字符串函数

#endif













