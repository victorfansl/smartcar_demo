#ifndef __MOTO_H
#define __MOTO_H

#include "stm32f10x.h"
//�������̼����������ķ�ֵ���
//Ӳ������˵����
#define GO    0//������״̬ ǰ��
#define BACK  1//����
#define STOP  2//ͣ��



//����
void MOTO_Left(char state);
//�ҵ��
void MOTO_Right(char state);

void MOTO_GPIO_Init(void);
					
void Car_Go(void);
void Car_Back(void);									
void Car_Turn_Right(void);
void Car_Turn_Left(void);
void Car_Stop(void);
#endif
