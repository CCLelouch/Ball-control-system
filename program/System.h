#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include "head.h"

#endif 

typedef enum
{
 	init,
	set_distance,
	action1,
	action2,
	action3
}State;

extern State System_State;

void System();
void Set_Distance();
void Action1();
void Action2();
void Action3();





