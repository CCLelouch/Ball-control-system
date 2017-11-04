#ifndef _LCD12864_H_
#define _LCD12864_H_

#include"head.h"
#define uint8 unsigned char
#define uint16 unsigned int

void Send_byte(uint8 byte);
void Write_comordata(uchar mode,uint8 dat);
void LCD12864_init();	 
void Write_word(uint8 *P);
void LCD12864_Display(uchar line,uchar *string);

#endif