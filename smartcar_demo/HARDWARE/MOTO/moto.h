#ifndef __MOTO_H
#define __MOTO_H

#include "stm32f10x.h"
//四驱底盘及四轮麦克纳姆轮底盘
//硬件连接说明：
#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车



//左电机
void MOTO_Left(char state);
//右电机
void MOTO_Right(char state);

void MOTO_GPIO_Init(void);
					
void Car_Go(void);
void Car_Back(void);									
void Car_Turn_Right(void);
void Car_Turn_Left(void);
void Car_Stop(void);
#endif
