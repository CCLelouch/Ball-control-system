#include "buzzer.h"
#include"Delay.H"

sbit buzzer = P5^5;

void Buzzer(uchar mode)
{
 	switch(mode)
	{
	 	case 0:buzzer=0;Delay(60);buzzer=1;break;		//��һ
		case 1:																			//����
		{
			buzzer=0;Delay(60);buzzer=1;Delay(60);
			buzzer=0;Delay(60);buzzer=1;Delay(60);
			buzzer=0;Delay(60);buzzer=1;		
		}break;
		case 2:																		 //����
		{
			buzzer=0;Delay(500);buzzer=1;Delay(200);
			buzzer=0;Delay(500);buzzer=1;Delay(200);
			buzzer=0;Delay(500);buzzer=1;
		}break;
//		case 3:break;
//		case 4:break;
//		case 5:break;
		default:break;
	}
}