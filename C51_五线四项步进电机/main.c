#include "reg52.h"

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;


//定义ULN2003控制步进电机管脚
sbit IN1_A=P1^0;
sbit IN2_B=P1^1;
sbit IN3_C=P1^2;
sbit IN4_D=P1^3;

void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}


void step_motor_28BYJ48_send_pulse(u16 Direction ,u16 Angle ,u16 Speed)//Direction方向,Angle角度，Speed速度，
{
	u16 temp=(Angle/0.7);
	u16 i=0,j=0,c=0;
	
	for(j=0;j<temp;j++)
	{
		for(i=0;i<8;i++)
		{
			c=i;
			if(Direction==0)	//如果为逆时针旋转
				c=7-i;//调换节拍信号
			switch(c)//8个节拍控制：A->AB->B->BC->C->CD->D->DA
			{
				case 0: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=0;break;
				case 1: IN1_A=1;IN2_B=1;IN3_C=0;IN4_D=0;break;
				case 2: IN1_A=0;IN2_B=1;IN3_C=0;IN4_D=0;break;
				case 3: IN1_A=0;IN2_B=1;IN3_C=1;IN4_D=0;break;
				case 4: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=0;break;
				case 5: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=1;break;
				case 6: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=1;break;
				case 7: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=1;break;
				default: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=0;break;//停止相序	
			}
			delay_ms(Speed);
		}
	}
	
	IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=0;//自动停止
}

void main()
{	
	//while(1)
	//{
		step_motor_28BYJ48_send_pulse(1,360,1);
	//}		
	while(1){;}
}
