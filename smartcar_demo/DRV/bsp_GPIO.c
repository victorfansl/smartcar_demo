/*
********************************************************************************************************
�ļ�����bsp_GPIO.c
��  �ܣ�������Ҫ����ͨIO
��  ע����ð����е�IO���������ã��������
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/

/*
********************************************************************************************************
GPIO������־��
1.2017-2-6����дLED��ʼ������

*********************************************************************************************************
*/

#include "bsp_GPIO.h"   
#include "delay.h"

/*
********************************************************************************************************
�������ƣ�void LED_GPIO_Config(void)
�������ܣ���ʼ��LED1��GPIO����
Ӳ�����ӣ�LED1----PC13
��    ע��
��    ��: 2017-2-6
*********************************************************************************************************
*/
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LED1_CLK, ENABLE); 	/*����GPIO������ʱ��*/																   
		GPIO_InitStructure.GPIO_Pin = LED1_Pin;	/*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*��������ģʽΪͨ���������*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*������������Ϊ50MHz */ 
		GPIO_Init(LED1_PORT, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC13*/	
}

//LED��˸
void LED_Flash(int time)
{	
		 static int temp;
		if(++temp==time)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction) (1 - GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)))	;//LED ��ɫɫ״̬��ת
			temp=0;
		}
		
}

/*
********************************************************************************************************
�������ƣ�void KEY_GPIO_Config(void)
�������ܣ���ʼ��KEY��GPIO����
Ӳ�����ӣ�DWN----PC6
					UP----PC7
					RST----PC8
					LFT----PC9
					MID----PC10
					RHT----PC11
					SET----PC12


��    ע��
��    ��: 2017-2-6
*********************************************************************************************************
*/
void KEY_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE); 	/*����GPIO������ʱ��*/																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	/*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   /*��������ģʽΪ*/   
		GPIO_Init(KEY_PORT, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC13*/	

}
/**
  * @brief   ����Ƿ��а�������
  * @param   ����Ķ˿ںͶ˿�λ
  *		@arg GPIOx: x�����ǣ�A...G�� 
  *		@arg GPIO_PIN ������GPIO_PIN_x��x������1...16��
   *  @arg ONSTS ��GPIO_PIN_x��x������1...16����Ӧ��������ʱIO�ڵĵ�ƽ
  * @retval  ������״̬
  *		@arg KEY_ON:��������
  *		@arg KEY_OFF:����û����
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,uint8_t ONSTS)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ONSTS ) 
	{	   
		/*��ʱ����*/
		Delay_us(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ONSTS )  
		{	 
			/*�ȴ������ͷ� */
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ONSTS);   
			return 	0;	 
		}
		else
			return 1;
	}
	else
		return 1;
}

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
//ѭ������ѭ��ģ�� ��������ߵ�ƽ1  ���ߵ͵�ƽ0
//С���������O4----���Ҷ���O1
//ѭ��·�棺��ɫ·���ɫ�����ߣ���Ѱ���ߡ�
//���� ���������1���������0
void Find(void)
{
	//ȫ�ǰ��ߣ�ǰ��
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// ���ߣ�ǰ��
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Go();
	}
	////O2�ں���  �ұ��к��� С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2Ѱ������
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Turn_Right();
	}

	////O2�ں��� O1����  �ұ��к��� С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1Ѱ������
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Turn_Right();
	}
	////O1�ں���  �ұ��к��� С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))// O1Ѱ������
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Turn_Right();
		
	}
	////O3�ں���  ��߱��к��� С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3Ѱ������
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Turn_Left();
	}
	////O3��O4�ں���  ��߱��к��� С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3 O4Ѱ������
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Turn_Left();
	}
	
	////O4�ں���  ��߱��к��� С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4Ѱ������
	{
			MOTO_PWM_Out(80, 80);	//����PWM
			Car_Turn_Left();
			
	}
	
	
	
	//ͣ��
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))// ���Դ��������ں���
	{
			MOTO_PWM_Out(80, 80);	//����PWM ͣ��
		  Car_Stop();
	}
	
	
}
//------------------End of File----------------------------
