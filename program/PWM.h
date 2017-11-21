#ifndef _PWM_H_
#define _PWM_H_

#include"stc15w.h"

/*P_SW2*/
#define EAXSFR 0X80

/*PWMCFG*/
#define CBTADC 0X40
#define C7INI  0X20
#define C6INI  0X10
#define C5INI  0X08
#define C4INI  0X04
#define C3INI  0X02
#define C2INI  0X01

/*PWMCR*/
#define ENPWM  0X80
#define ECBI   0X40
#define ENC70  0X20
#define ENC60  0X10
#define ENC50  0X08
#define ENC40  0X04
#define ENC30  0X02
#define ENC20  0X01

/*PWMIF*/
#define CBIF  0X40
#define C7IF  0X20
#define C6IF  0X10
#define C5IF  0X08
#define C4IF  0X04
#define C3IF  0X02
#define C2IF  0X01

/*PWM2CR*/
#define EPWM2_PS  0X08
#define EPWM2I 	  0X04
#define EC2T2SI   0X02
#define EC2T1SI   0X01

#define CYCLE 2000;
void PWM_init();
void PWM2_set(uint duty);

#endif
