#ifndef __FIND_H
#define __FIND_H

#include "stm32f10x.h"

//Ѱ�����������ҵ����Դ�O1 O2 O3 O4 
#define Find_O1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)	   //����ѭ��ģ�������ӿ�
#define Find_O2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define Find_O3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define Find_O4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)

void TRACK_IO_Init(void);
void TRACK(void);

#endif /* __LED_H */