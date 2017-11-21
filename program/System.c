#include"system.h"
#include"lcd12864.h"
#include"Delay.H"
#include"key.h"
#include"buzzer.h"
#include"pid.h"
#include"pwm.h"

int flag=0,diatance_buf;
/**************************��ʾҳ��*****************************/
uchar xdata Display[5][4][17]={
	{																					
		{"init"},{"  С�����ϵͳ"},{"  "},{" "}							  //��һҳ
	},
	{
		{"  Set_distance"},{"Expect:00"},{"Distance:   cm"},{"            next"}						//�ڶ�ҳ
	},
	{
		{"  Action1"},{"32"},{"33"},{"back        next"}			  //����ҳ
	},
	{
		{"  Action2"},{"42"},{"43  "},{"back        next"}				 	  //����ҳ
	},
	{
		{"  Action3"},{"52"},{"53"},{"back        next"}			  //����ҳ
	},
};
uchar key_value[5]={0};//��ż�ֵ
char set_buff;//������õľ���ֵ
int actual_dis,dis;//ʵ�ʾ����ʵ�ʾ���ĸ�������
/**************************************************************/

State System_State=0;//ϵͳ״̬��ö�ٱ���
Refresh System_refresh ={20,0,5,10,15};//ϵͳ��ˢ��ʱ��ṹ���ʼ��T = 20ms
/****************************************************************
/*��������void Set_Distance()			
/*���ܣ�	ʵ�־����趨�Ϳ���
/*˵����
/*�޸����ڣ�2017-11-12
/*���ߣ�c.c. 
/***************************************************************/
void Set_Distance()
{
	int i=0,key_flag=0;
	key_value[0]=KEY4_scan();//����ֵ����������

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
															//�ڴ�ѭ������ӿ��ƺ���
			actual_dis = 15;
/**/		PID_setpara(1,0,0);//����������ϵ��������ϵ����΢��ϵ��
			while(1)
			{
				if(actual_dis != diatance_buf)//����ı�ʱ���ı�PWM
				{
//					PID_Calculate(actual_dis,set_buff,0);
					PWM2_set(PID_Calculate(actual_dis,set_buff,0));
					diatance_buf=actual_dis;//ͬ�� 
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
/*��������void Action1()			
/*���ܣ�
/*˵����
/*�޸����ڣ�2017-11-12
/*���ߣ�c.c. 
/***************************************************************/
void Action1()
{
 	key_value[0]=KEY4_scan();//����ֵ����������
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
/*��������void Action2()		
/*���ܣ�
/*˵����
/*�޸����ڣ�2017-11-12
/*���ߣ�c.c. 
/***************************************************************/
void Action2()
{
 	key_value[0]=KEY4_scan();//����ֵ����������
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
/*��������void Action3()			
/*���ܣ�
/*˵����
/*�޸����ڣ�2017-11-12
/*���ߣ�c.c. 
/***************************************************************/
void Action3()
{
 	key_value[0]=KEY4_scan();//����ֵ����������
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
/*��������void System()			
/*���ܣ�	ϵͳ����
/*˵����
/*�޸����ڣ�2017-11-12
/*���ߣ�c.c. 
/***************************************************************/
void System()
{
	switch(System_State)
	{
	 	case init:
		{
			Write_comordata(0,0x01);						 		//����
			Delay(5);
			LCD12864_Display(1,&Display[0][1][0]);	//����ҳ��
			Delay(1000);
			Write_comordata(0,0x01);								//����
			Delay(5);
			System_State=set_distance;
		}break;
		case set_distance:
		{
			if(System_refresh.set_Distance_fresh>System_refresh.T)//ÿ20msɨ��һ��
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
			if(System_refresh.action1_fresh>System_refresh.T)//ÿ20msɨ��һ��
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
			if(System_refresh.action2_fresh>System_refresh.T)//ÿ20msɨ��һ��
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
			if(System_refresh.action3_fresh>System_refresh.T)//ÿ20msɨ��һ��
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

