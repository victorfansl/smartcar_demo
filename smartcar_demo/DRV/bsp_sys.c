/*
********************************************************************************************************
文件名：bsp_sys.c
功  能：初始化所有外设
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "bsp_sys.h"

void STM32_System_Init(void)
{	
	//STM32内部初始化
	
	Delay_Init(72);        //滴答时钟初始化
	NVIC_Config();         //中断配置配置初始化
	LED_GPIO_Config();     //LED初始化
	KEY_GPIO_Config();     //KEY初始化
	TRACK_IO_Init();       //循迹IO初始化
	USART1_Init(115200);   //串口初始化
	IIC_Init();            //IIC模拟初始化
	
	MOTO_GPIO_Init();       //电机驱动IO配置
	MOTO_PWM_Init(3599,0);  //电机的PWM频率初始化20KHz
		
	ADCx_Init();		// ADC 初始化
	

	OLED_Init();
  OLED_Clear();
	/*
	OLED_ShowString(0,0, "BAT:      mV  OK",16);//显示电池电压： V,正常值6.2-8,否则需要充电
	OLED_ShowString(0,2,"L:    R:     RPM",16);          //显示左轮转  R单位RPM 表示每分钟车轮的圈数
	OLED_ShowString(0,4,"L:    R:     PWM",16);         //显示右轮转  R单位RPM 表示每分钟车轮的圈数
	OLED_ShowString(0,6,"track:    ",16);         //显示四个红外传感器的状态
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
	OLED_ShowCHinese(0,0,2);  //显示汉字 车
	OLED_ShowCHinese(16,0,3); //显示汉字 速
	OLED_ShowString(88,0,"m/min",16);          //OLED第一行显示整体车速 单位m/min
	OLED_ShowString(0,2,"Left :    RPM",12);          //显示左轮转  R单位RPM 表示每分钟车轮的圈数
	OLED_ShowString(0,3,"Right:    RPM",12);         //显示右轮转  R单位RPM 表示每分钟车轮的圈数
	OLED_ShowString(0,4,"P:   I:   D:   ",16); //显示PID参数
	OLED_ShowString(0,6,"Set_C:    RPM",12);      //显设置的车轮转速单位RPM
	OLED_ShowString(0,7,"Set_P:     m/min",12);      //显设置的车轮转速单位RPM
	*/
	Encoder_Init_TIM2();
	TIM2 -> CNT=30000;
	Encoder_Init_TIM4();
	TIM4 -> CNT=30000;
	
  Timer6_Init();//最后启动定时器6
	TIM_Cmd(TIM6, DISABLE);//启动定时器 
	Delay_ms(100);          //等待初始化完成
}


