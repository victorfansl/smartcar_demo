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


//------------------End of File----------------------------
