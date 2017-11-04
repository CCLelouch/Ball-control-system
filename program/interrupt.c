#include"interrupt.h"

uchar i=0,j=0,k=0;

bit b=0;

void int_timer2() interrupt 12
{				
	i++;
	if(i==60)
	{
		i=0;
	 	j++;

		if(b==0)
			l = 16;
		if(b==1)
			l = 17;
		b = !b;

		if(j==60)
		{
			j = 0;
			k++;
			if(k==60)
			k=0;
		}
	}
}
