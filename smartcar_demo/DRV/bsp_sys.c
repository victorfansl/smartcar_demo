/*
********************************************************************************************************
�ļ�����bsp_sys.c
��  �ܣ���ʼ����������
��  ע��
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/

#include "bsp_sys.h"

void STM32_System_Init(void)
{	
	//STM32�ڲ���ʼ��
	
	Delay_Init(72);        //�δ�ʱ�ӳ�ʼ��
	NVIC_Config();         //�ж��������ó�ʼ��
	LED_GPIO_Config();     //LED��ʼ��
	KEY_GPIO_Config();     //KEY��ʼ��
	TRACK_IO_Init();       //ѭ��IO��ʼ��
	USART1_Init(115200);   //���ڳ�ʼ��
	IIC_Init();            //IICģ���ʼ��
	
	MOTO_GPIO_Init();       //�������IO����
	MOTO_PWM_Init(3599,0);  //�����PWMƵ�ʳ�ʼ��20KHz
		
	ADCx_Init();		// ADC ��ʼ��
	

	OLED_Init();
  OLED_Clear();
	/*
	OLED_ShowString(0,0, "BAT:      mV  OK",16);//��ʾ��ص�ѹ�� V,����ֵ6.2-8,������Ҫ���
	OLED_ShowString(0,2,"L:    R:     RPM",16);          //��ʾ����ת  R��λRPM ��ʾÿ���ӳ��ֵ�Ȧ��
	OLED_ShowString(0,4,"L:    R:     PWM",16);         //��ʾ����ת  R��λRPM ��ʾÿ���ӳ��ֵ�Ȧ��
	OLED_ShowString(0,6,"track:    ",16);         //��ʾ�ĸ����⴫������״̬
	*/
	/*
	OLED_ShowNum(0,0,1234,4,16); 
	OLED_ShowNum(1,2,1234,4,16); 
	OLED_ShowNum(2,4,1234,4,16); 
	OLED_ShowNum(3,6,1234,4,16); 
	*/
	OLED_ShowString(0,0, "     NIT",16);
	OLED_ShowString(0,2,"Smart Car",16);
	OLED_ShowString(0,4,"fsl",16);        
	OLED_ShowString(0,6,"2020-06-29",16);    
	
	/*
	OLED_ShowCHinese(0,0,2);  //��ʾ���� ��
	OLED_ShowCHinese(16,0,3); //��ʾ���� ��
	OLED_ShowString(88,0,"m/min",16);          //OLED��һ����ʾ���峵�� ��λm/min
	OLED_ShowString(0,2,"Left :    RPM",12);          //��ʾ����ת  R��λRPM ��ʾÿ���ӳ��ֵ�Ȧ��
	OLED_ShowString(0,3,"Right:    RPM",12);         //��ʾ����ת  R��λRPM ��ʾÿ���ӳ��ֵ�Ȧ��
	OLED_ShowString(0,4,"P:   I:   D:   ",16); //��ʾPID����
	OLED_ShowString(0,6,"Set_C:    RPM",12);      //�����õĳ���ת�ٵ�λRPM
	OLED_ShowString(0,7,"Set_P:     m/min",12);      //�����õĳ���ת�ٵ�λRPM
	*/
	Encoder_Init_TIM2();
	TIM2 -> CNT=30000;
	Encoder_Init_TIM4();
	TIM4 -> CNT=30000;
	
  Timer6_Init();//���������ʱ��6
	TIM_Cmd(TIM6, DISABLE);//������ʱ�� 
	Delay_ms(100);          //�ȴ���ʼ�����
}


