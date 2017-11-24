#ifndef _ADC_H
#define _ADC_H
#include"head.h"

void ADC_init(uchar CHX);
uchar ADC_Read(uchar Write_byte);

extern uchar ;
extern uint;
/*ADC CHX*/
#define CH0  0X80
#define CH1  0X40
#define CH2  0X20
#define CH3  0X10
#define CH4  0X08
#define CH5  0X04
#define CH6  0X02
#define CH7  0X01
#endif

