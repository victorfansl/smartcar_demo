/*
********************************************************************************************************
�ļ�����moto.c
��  �ܣ�ֱ�����ٵ������
��  ע��	
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/

#include "moto.h"



//***************************���õ������IO��***************************//
//�������TB6612ģ��
//Ӳ������˵����
//PB0----PWMA   �ҵ��PWM
//PB12----AIN2  �����ҵ������
//PB13----AIN1  �����ҵ������
//PB14----BIN1  ������������
//PB15----BIN2  ������������
//PB1----PWMB    ����PWM

//�������L298Nģ��
//Ӳ������˵����
//PB0----ENA   ����PWM
//PB12----IN1  ������������
//PB13----IN2  ������������
//PB14----IN3  �����ҵ������
//PB15----IN4  �����ҵ������
//PB1----ENB    �ҵ��PWM

//PWM��timer3������
void MOTO_GPIO_Init(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                	  /*����GPIO������ʱ��*/																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	    /*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              /*��������ģʽΪͨ���������*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             /*������������Ϊ50MHz */ 
		GPIO_Init(GPIOB, &GPIO_InitStructure);                                	/*���ÿ⺯������ʼ��GPIO*/			
	
}

//����
void MOTO_Left(char state)
{
	if(state == GO)//��ǰ���ǰ��
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	if(state == BACK)//��ǰ�������
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		
	}
	if(state == STOP)//ͣת
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	}
			
}

//�ҵ��
void MOTO_Right(char state)
{
	if(state == GO)//��ǰ���ǰ��
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
	if(state == BACK)//��ǰ�������
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		
	}
	if(state == STOP)//ͣת
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
			
}



//***************************ǰ��***************************//
//ֻҪ����()��״̬�Ϳ��Ըı���ת������
void Car_Go(void)
{
	//���� ǰ    //�ҵ�� ǰ
	MOTO_Left(GO);  MOTO_Right(GO);
}

void Car_Back(void)
{
  //���� ��       //�ҵ�� ��
	MOTO_Left(BACK);  MOTO_Right(BACK);
}

//***************************����תȦ***************************//
void Car_Turn_Left(void)
{
	
	//���� ��       //�ҵ�� ǰ
	MOTO_Left(BACK);  MOTO_Right(GO);
	
}


//***************************����תȦ***************************//
void Car_Turn_Right(void)
{
	//���� ǰ    //�ҵ�� ��
	MOTO_Left(GO);  MOTO_Right(BACK);
}

//***************************ͣ��***************************//
void Car_Stop(void)
{
	//���� ͣ    //�ҵ�� ͣ
	MOTO_Left(STOP);  MOTO_Right(STOP);
}



