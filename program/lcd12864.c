#include"lcd12864.h"
#include"Delay.H"

sbit CS = P2^5;
sbit SID = P2^6;
sbit SCLK = P2^7;
sbit PSB = P3^3;
sbit RST = P3^7;

/****************************************************************
**函数：Send_byte(uint8 byte)			
**功能：
**说明： 
**修改日期：2017-11-03
**作者：c.c. 
****************************************************************/
void Send_byte(uint8 byte)
{
 	 uint8 i;
	 for(i = 0;i<8;i++)
	 {
	  	if( (byte<<i) &0x80)
				SID =  1;
		  else
				SID = 0;
		  SCLK = 1;
		  SCLK = 0;
	 }
}

/****************************************************************
**函数：void Write_comordata(uchar mode,uint8 cmdcode)			
**功能：
**说明：mode模式选择，0为指令，1为数据 
**修改日期：2017-11-03
**作者：c.c. 
****************************************************************/
void Write_comordata(uchar mode,uint8 dat)
{
	CS = 1;
	if(!mode)
	  Send_byte(0xf8);								 //指令传送
	else
		Send_byte(0xfa);								 //数据传送
	Send_byte(dat &0xf0);					 //先传高四位
	Send_byte((dat<<4) &0xf0);		 //再传第四位
	CS = 0;	 	
}

/****************************************************************
**函数：void Write_word(uint8 *P)			
**功能：
**说明： 
**修改日期：2017-11-03
**作者：c.c. 
****************************************************************/
void Write_word(uint8 *P)
{
	while(*P!='\0')
	{
		Write_comordata(1,*P);
		P++;
	}
}

/****************************************************************
**函数：void LCD12864_init()			
**功能：
**说明： 
**修改日期：2017-11-03
**作者：c.c. 
****************************************************************/
void LCD12864_init()
{
	Delay(50);
	RST = 0;
	RST = 1;
	Write_comordata(0,0x30);		//基本操作指令设定
	Delay(50);
	Write_comordata(0,0x0c);	  //无游标
	Delay(50);
	Write_comordata(0,0x01);	  //清屏
}

/****************************************************************
**函数：void LCD12864_Display(uchar line,uchar *string)			
**功能：二字节字符显示
**说明：输入显示的字符串
**修改日期：2017-11-03
**作者：c.c. 
****************************************************************/
void LCD12864_Display(uchar line,uchar *string)
{
	if(line==1)
		Write_comordata(0,0x80);	 //line1
	else if(line==2)
		Write_comordata(0,0x90);	 //line2				//0x90-8=0x88
	else if(line==3)					
		Write_comordata(0,0x88);	 //line3
	else if(line==4)
		Write_comordata(0,0x98);	 //line4
	Write_word(string);
}



/**
  * 第一字节：串口控制格式 11111ABC
  *         	A为数据传送方向控制：H表示数据从LCD到MCU，L表示从MCU到LCD
  * 			  	B为数据类型选择：H表示数据是显示数据，L表示数据是控制指令
  *						C固定为0
  * 第二字节：（并行）8位数据的高4位
	* 第三字节：（并行）8位数据的低4位
  */


/******************************************COM************************************
						**B7			B6			B5			B4			|B3			B2			B1			B0	  	****
	@显示状态 **L				L				L				L				|L			DSP			Cursor	Blink		****
	@反白选择 **L				L				L				L				|L			H				R1			R0			****
	********************************************************************************/