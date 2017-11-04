#include"system.h"
#include"lcd12864.h"
#include"Delay.H"
#include"key.h"
#include"buzzer.h"

/**************************显示页面*****************************/
uchar xdata Display[5][4][17]={
	{																					
		{"init"},{"  小球控制系统"},{"  "},{" "}							  //第一页
	},
	{
		{"  Set_distance"},{"Expect:00"},{"Distance:"},{"            next"}						//第二页
	},
	{
		{"  Action1"},{"32"},{"33"},{"back        next"}			  //第三页
	},
	{
		{"  Action2"},{"42"},{"43"},{"back        next"}				 	  //第四页
	},
	{
		{"  Action3"},{"52"},{"53"},{"back        next"}			  //第三页
	},
};
uchar key_value[5]={0};
uchar set_buff,actual_dis;
/**************************************************************/

State System_State=0;

void Set_Distance()
{
	int i=0,key_flag=0;
	key_value[0]=KEY4_scan();//将键值读入输入流

	switch(key_value[0])
	{
	 	case 1:
			{
				System_State = init;
				Write_comordata(0,0x01);
				key_value[1]=0;
			}break;
	 	case 2:
			{
				if(set_buff==0)										//0-16
						set_buff=16;
				set_buff--;
				Display[1][1][8]='0'+set_buff%10;	//0
				Display[1][1][7]='0'+set_buff/10;	//10

			}break;
	 	case 3:
			{
				set_buff++;
				if(set_buff==16)									//16-0
					set_buff=0;
				Display[1][1][8]='0'+set_buff%10;	//0
				Display[1][1][7]='0'+set_buff/10;	//10
			}break;
	 	case 4:
			{
				while(1)																//在此循环中添加控制函数
				{
				 	actual_dis=15;												//赋值给次变量修改显示的实际距离值
					Display[1][2][10]='0'+actual_dis%10;	//0
					Display[1][2][9]='0'+actual_dis/10;	//10
					LCD12864_Display(3,&Display[1][2][0]);
					if(KEY4_scan()==4)
						break;
				}
				 	System_State = action1;
					Write_comordata(0,0x01);
					key_value[0]=0;
			}break;
		default:break;
	}
}

void Action1()
{
 	key_value[0]=KEY4_scan();//将键值读入输入流
	switch(key_value[0])
	{
	 	case 1:
			{
				System_State = set_distance;
				Write_comordata(0,0x01);
				key_value[1]=0;
			}break;
	 	case 2:
			{
				;
			}break;
	 	case 3:
			{
				;
			}break;
	 	case 4:
			{
				 	System_State = action2;
					Write_comordata(0,0x01);
			}break;
		default:break;
	}
}

void Action2()
{
 	key_value[0]=KEY4_scan();//将键值读入输入流
	switch(key_value[0])
	{
	 	case 1:
			{
				System_State = action1;
				Write_comordata(0,0x01);
				key_value[1]=0;
			}break;
	 	case 2:
			{
				;
			}break;
	 	case 3:
			{
				;
			}break;
	 	case 4:
			{
				 	System_State = action3;
					Write_comordata(0,0x01);
			}break;
		default:break;
	}
}

void Action3()
{
 	key_value[0]=KEY4_scan();//将键值读入输入流
	switch(key_value[0])
	{
	 	case 1:
			{
				System_State = action2;
				Write_comordata(0,0x01);
				key_value[1]=0;
			}break;
	 	case 2:
			{
				;
			}break;
	 	case 3:
			{
				;
			}break;
	 	case 4:
			{
			 	System_State = init;
				Write_comordata(0,0x01);
			}break;
		default:break;
	}
}

void System()
{
	switch(System_State)
	{
	 	case init:
			{
				Write_comordata(0,0x01);						 		//清屏
				Delay(5);
				LCD12864_Display(1,&Display[0][1][0]);	//开机页面
				Delay(500);
				Write_comordata(0,0x01);								//清屏
				Delay(5);
				System_State=set_distance;
			}break;
		case set_distance:
			{
				LCD12864_Display(1,&Display[1][0][0]);
				LCD12864_Display(2,&Display[1][1][0]);
				LCD12864_Display(3,&Display[1][2][0]);
			 	LCD12864_Display(4,&Display[1][3][0]);
				Set_Distance();
			}break;
		case action1:
			{
				LCD12864_Display(1,&Display[2][0][0]);
				LCD12864_Display(2,&Display[2][1][0]);
				LCD12864_Display(3,&Display[2][2][0]);
			 	LCD12864_Display(4,&Display[2][3][0]);
				Action1();
			}break;
		case action2:
			{
				LCD12864_Display(1,&Display[3][0][0]);
				LCD12864_Display(2,&Display[3][1][0]);
				LCD12864_Display(3,&Display[3][2][0]);
			 	LCD12864_Display(4,&Display[3][3][0]);
				Action2();
			}break;
		case action3:
			{
				LCD12864_Display(1,&Display[4][0][0]);
				LCD12864_Display(2,&Display[4][1][0]);
				LCD12864_Display(3,&Display[4][2][0]);
			 	LCD12864_Display(4,&Display[4][3][0]);
				Action3();
			}break;
		default :break;
	}
}

