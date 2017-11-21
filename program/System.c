#include"system.h"
#include"lcd12864.h"
#include"Delay.H"
#include"key.h"
#include"buzzer.h"
#include"pid.h"
#include"pwm.h"

int flag=0,diatance_buf;
/**************************显示页面*****************************/
uchar xdata Display[5][4][17]={
	{																					
		{"init"},{"  小球控制系统"},{"  "},{" "}							  //第一页
	},
	{
		{"  Set_distance"},{"Expect:00"},{"Distance:   cm"},{"            next"}						//第二页
	},
	{
		{"  Action1"},{"32"},{"33"},{"back        next"}			  //第三页
	},
	{
		{"  Action2"},{"42"},{"43  "},{"back        next"}				 	  //第四页
	},
	{
		{"  Action3"},{"52"},{"53"},{"back        next"}			  //第三页
	},
};
uchar key_value[5]={0};//存放键值
char set_buff;//存放设置的距离值
int actual_dis,dis;//实际距离和实际距离的附属变量
/**************************************************************/

State System_State=0;//系统状态的枚举变量
Refresh System_refresh ={20,0,5,10,15};//系统各刷新时间结构体初始化T = 20ms
/****************************************************************
/*函数名：void Set_Distance()			
/*功能：	实现距离设定和控制
/*说明：
/*修改日期：2017-11-12
/*作者：c.c. 
/***************************************************************/
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
		}break;
	 	case 2:
		{
			if(set_buff==0)										//0-16
					set_buff=41;
			set_buff--;
			Display[1][1][8]='0'+(set_buff)%10;	//0
			Display[1][1][7]='0'+(set_buff)/10;	//10

		}break;
	 	case 3:
		{
			set_buff++;
			if(set_buff==41)									//16-0
				set_buff=0;
			Display[1][1][8]='0'+(set_buff)%10;	//0
			Display[1][1][7]='0'+(set_buff)/10;	//10
		}break;	
	 	case 4:
		{
															//在此循环中添加控制函数
			actual_dis = 15;
/**/		PID_setpara(1,0,0);//参数：比例系数，积分系数，微分系数
			while(1)
			{
				if(actual_dis != diatance_buf)//距离改变时，改变PWM
				{
//					PID_Calculate(actual_dis,set_buff,0);
					PWM2_set(PID_Calculate(actual_dis,set_buff,0));
					diatance_buf=actual_dis;//同步 
				}

				if(actual_dis>0)
				{	
					Display[1][2][9]='+';	//0                                                                                                                                                                                                                                                                                
					Display[1][2][11]='0'+actual_dis%10;	//0
					Display[1][2][10]='0'+actual_dis/10;	//10
				}
				else
				{
					dis = -actual_dis;
					Display[1][2][9]='-';	//0
					Display[1][2][11]='0'+dis%10;	//0
					Display[1][2][10]='0'+dis/10;	//10
				}

				LCD12864_Display(3,&Display[1][2][0]);
				if(KEY4_scan()==4)
					break;
			}
		 	System_State = action1;
			Write_comordata(0,0x01);
		}break;
		default:break;
	}
}

/****************************************************************
/*函数名：void Action1()			
/*功能：
/*说明：
/*修改日期：2017-11-12
/*作者：c.c. 
/***************************************************************/
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
//				Write_comordata(0,0x01);
		}break;
		default:break;
	}
}

/****************************************************************
/*函数名：void Action2()		
/*功能：
/*说明：
/*修改日期：2017-11-12
/*作者：c.c. 
/***************************************************************/
void Action2()
{
 	key_value[0]=KEY4_scan();//将键值读入输入流
	switch(key_value[0])
	{
	 	case 1:
		{
			System_State = action1;
//			Write_comordata(0,0x01);
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
//				Display[4][1][0]='0'+flag/10;
//				Display[4][1][1]='0'+flag%10;
				LCD12864_Display(2,&Display[4][1][0]);
			 	System_State = action3;
//				Write_comordata(0,0x01);
		}break;
		default:break;
	}
}

/****************************************************************
/*函数名：void Action3()			
/*功能：
/*说明：
/*修改日期：2017-11-12
/*作者：c.c. 
/***************************************************************/
void Action3()
{
 	key_value[0]=KEY4_scan();//将键值读入输入流
	switch(key_value[0])
	{
	 	case 1:
		{
			System_State = action2;
//			Write_comordata(0,0x01);
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
//			Write_comordata(0,0x01);
		}break;
		default:break;
	}
}

/****************************************************************
/*函数名：void System()			
/*功能：	系统函数
/*说明：
/*修改日期：2017-11-12
/*作者：c.c. 
/***************************************************************/
void System()
{
	switch(System_State)
	{
	 	case init:
		{
			Write_comordata(0,0x01);						 		//清屏
			Delay(5);
			LCD12864_Display(1,&Display[0][1][0]);	//开机页面
			Delay(1000);
			Write_comordata(0,0x01);								//清屏
			Delay(5);
			System_State=set_distance;
		}break;
		case set_distance:
		{
			if(System_refresh.set_Distance_fresh>System_refresh.T)//每20ms扫描一次
			{
//				EA = 0;
				Delay(100);
				LCD12864_Display(1,&Display[1][0][0]);
				LCD12864_Display(2,&Display[1][1][0]);
				LCD12864_Display(3,&Display[1][2][0]);
			 	LCD12864_Display(4,&Display[1][3][0]);
				System_refresh.set_Distance_fresh=0;
				Delay(100);
//				EA = 1;
			}
				Set_Distance();
		}break;
		case action1:
		{
			if(System_refresh.action1_fresh>System_refresh.T)//每20ms扫描一次
			{
//				EA = 0;
				LCD12864_Display(1,&Display[2][0][0]);
				LCD12864_Display(2,&Display[2][1][0]);
				LCD12864_Display(3,&Display[2][2][0]);
			 	LCD12864_Display(4,&Display[2][3][0]);
				System_refresh.action1_fresh=0;
//				EA = 1;
			}
			Action1();
		}break;
		case action2:
		{
			if(System_refresh.action2_fresh>System_refresh.T)//每20ms扫描一次
			{
//  			EA = 0;
				LCD12864_Display(1,&Display[3][0][0]);
				LCD12864_Display(2,&Display[3][1][0]);
				LCD12864_Display(3,&Display[3][2][0]);
			 	LCD12864_Display(4,&Display[3][3][0]);			
				System_refresh.action2_fresh=0;
//				EA = 1;
			}
			Action2();
		}break;
		case action3:
		{
			if(System_refresh.action3_fresh>System_refresh.T)//每20ms扫描一次
			{
//				EA = 0;
				LCD12864_Display(1,&Display[4][0][0]);
				LCD12864_Display(2,&Display[4][1][0]);
				LCD12864_Display(3,&Display[4][2][0]);
			 	LCD12864_Display(4,&Display[4][3][0]);

				Display[4][1][0]='0'+flag/10;
				Display[4][1][1]='0'+flag%10;

				System_refresh.action3_fresh=0;
//				EA = 1;
				P01=~P01;
			}
			Action3();
		}break;
		default :break;
	}
}

