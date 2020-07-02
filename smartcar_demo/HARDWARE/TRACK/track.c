
#include "bsp_GPIO.h"   
#include "delay.h"
#include "track.h"


#define LEFT_BASE  2400
#define RIGHT_BASE  2500

extern int carStatus;
//ѭ��IO��ʼ��
//Ѱ�����������ҵ����Դ�O1 O2 O3 O4 
//Ӳ������ O1-PA3��O2-PA4��O3-PA5��O4-PA6��
//Ҫ��ʼ��Ϊ����ģʽ
void TRACK_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6;//ѡ��IO�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//����Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//����GPIO_InitStructure��ָ���Ĳ�����ʼ������GPIOD�Ĵ���

} 

void  BLACK_LINE_DETECT(void)
{
		
}
//ѭ������ѭ��ģ�� ��������ߵ�ƽ1  ���ߵ͵�ƽ0
//С���������O4----���Ҷ���O1
//ѭ��·�棺��ɫ·���ɫ�����ߣ���Ѱ���ߡ�
//���� ���������1���������0
void TRACK(void)
{
	
	//ȫ�ǰ��ߣ�ǰ��
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// ���ߣ�ǰ��
	{	
		if(carStatus <= -3 ) 
			carStatus	=	-4;
		else if(carStatus >= 3 ) 
			carStatus		=	4;
		else
			carStatus	=	0;
	}
	////O2�ں���  �ұ��к��� С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2Ѱ������
	{
			carStatus = -1;
	}

	////O2�ں��� O1����  �ұ��к��� С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1Ѱ������
	{
			carStatus = -2;
	}
	////O1�ں���  �ұ��к��� С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))// O1Ѱ������
	{
			carStatus = -3;
		
	}
	////O3�ں���  ��߱��к��� С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3Ѱ������
	{
			carStatus = 1;
	}
	////O3��O4�ں���  ��߱��к��� С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3 O4Ѱ������
	{
		carStatus = 2;
	}
	
	////O4�ں���  ��߱��к��� С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4Ѱ������
	{
			carStatus = 3;
	}
		//ͣ��
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))// ���Դ��������ں���
	{
			carStatus = 5;

	}

	switch(carStatus){
		case -4:{	TIM3->CCR3 =LEFT_BASE;	TIM3->CCR4 =0;	break;}
		case -3:{	TIM3->CCR3 =LEFT_BASE;	TIM3->CCR4 =0;	break;}
		case -2:{	TIM3->CCR3 =LEFT_BASE;	TIM3->CCR4 =RIGHT_BASE-50;	break;}
		case -1:{	TIM3->CCR3 =LEFT_BASE;	TIM3->CCR4 =RIGHT_BASE-25;	break;}
		case 0:{	TIM3->CCR3 =LEFT_BASE;	TIM3->CCR4 =RIGHT_BASE;	break;}
		case 1:{	TIM3->CCR3 =LEFT_BASE-25;	TIM3->CCR4 =RIGHT_BASE;	break;}
		case 2:{	TIM3->CCR3 =LEFT_BASE-50;	TIM3->CCR4 =RIGHT_BASE;	break;}
		case 3:{	TIM3->CCR3 =0;	TIM3->CCR4 =RIGHT_BASE;	break;}
		case 4:{	TIM3->CCR3 =0;	TIM3->CCR4 =RIGHT_BASE;	break;}
		case 5:{	TIM3->CCR3 =0;	TIM3->CCR4 =0;	break;}
		default : break;
	}
	Car_Go();
	
}