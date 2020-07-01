#ifndef __BSP_GPIO_H
#define	__BSP_GPIO_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

//����LED1
#define LED1_CLK  RCC_APB2Periph_GPIOC
#define LED1_PORT GPIOC
#define LED1_Pin  GPIO_Pin_13

//����KEY1
#define KEY_CLK  RCC_APB2Periph_GPIOC
#define KEY_PORT GPIOC

//Ѱ�����������ҵ����Դ�O1 O2 O3 O4 
#define Find_O1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)	   //����ѭ��ģ�������ӿ�
#define Find_O2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define Find_O3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define Find_O4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)


/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_PORT,LED1_Pin);\
					else		\
					GPIO_ResetBits(LED1_PORT,LED1_Pin)




///* ֱ�Ӳ����Ĵ����ķ�������IO */
//#define	digitalHi(p,i)			{p->BSRR=i;}			//����Ϊ�ߵ�ƽ		
//#define digitalLo(p,i)			{p->BRR=i;}				//����͵�ƽ
//#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬
//
//
///* �������IO�ĺ� */
//#define LED1_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_0)
//#define LED1_OFF		digitalHi(GPIOB,GPIO_Pin_0)
//#define LED1_ON			digitalLo(GPIOB,GPIO_Pin_0)
//
//#define LED2_TOGGLE		digitalToggle(GPIOF,GPIO_Pin_7)
//#define LED2_OFF		digitalHi(GPIOF,GPIO_Pin_7)
//#define LED2_ON			digitalLo(GPIOF,GPIO_Pin_7)
//
//#define LED3_TOGGLE		digitalToggle(GPIOF,GPIO_Pin_8)
//#define LED3_OFF		digitalHi(GPIOF,GPIO_Pin_8)
//#define LED3_ON			digitalLo(GPIOF,GPIO_Pin_8)

void LED_GPIO_Config(void);
void LED_Flash(int timer);

void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,uint8_t ONSTS);

void TRACK_IO_Init(void);

#endif /* __LED_H */
