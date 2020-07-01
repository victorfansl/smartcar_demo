/*
********************************************************************************************************
文件名：moto.c
功  能：直流减速电机控制
备  注：	
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "moto.h"



//***************************配置电机驱动IO口***************************//
//电机驱动TB6612模块
//硬件连接说明：
//PB0----PWMA   右电机PWM
//PB12----AIN2  控制右电机正反
//PB13----AIN1  控制右电机正反
//PB14----BIN1  控制左电机正反
//PB15----BIN2  控制左电机正反
//PB1----PWMB    左电机PWM

//电机驱动L298N模块
//硬件连接说明：
//PB0----ENA   左电机PWM
//PB12----IN1  控制左电机正反
//PB13----IN2  控制左电机正反
//PB14----IN3  控制右电机正反
//PB15----IN4  控制右电机正反
//PB1----ENB    右电机PWM

//PWM在timer3里配置
void MOTO_GPIO_Init(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                	  /*开启GPIO的外设时钟*/																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	    /*选择要控制的GPIO引脚*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              /*设置引脚模式为通用推挽输出*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             /*设置引脚速率为50MHz */ 
		GPIO_Init(GPIOB, &GPIO_InitStructure);                                	/*调用库函数，初始化GPIO*/			
	
}

//左电机
void MOTO_Left(char state)
{
	if(state == GO)//左前电机前进
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	if(state == BACK)//左前电机后退
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		
	}
	if(state == STOP)//停转
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	}
			
}

//右电机
void MOTO_Right(char state)
{
	if(state == GO)//左前电机前进
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
	if(state == BACK)//左前电机后退
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		
	}
	if(state == STOP)//停转
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
			
}



//***************************前进***************************//
//只要配置()的状态就可以改变电机转动方向
void Car_Go(void)
{
	//左电机 前    //右电机 前
	MOTO_Left(GO);  MOTO_Right(GO);
}

void Car_Back(void)
{
  //左电机 后       //右电机 后
	MOTO_Left(BACK);  MOTO_Right(BACK);
}

//***************************向左转圈***************************//
void Car_Turn_Left(void)
{
	
	//左电机 后       //右电机 前
	MOTO_Left(BACK);  MOTO_Right(GO);
	
}


//***************************向右转圈***************************//
void Car_Turn_Right(void)
{
	//左电机 前    //右电机 后
	MOTO_Left(GO);  MOTO_Right(BACK);
}

//***************************停车***************************//
void Car_Stop(void)
{
	//左电机 停    //右电机 停
	MOTO_Left(STOP);  MOTO_Right(STOP);
}



