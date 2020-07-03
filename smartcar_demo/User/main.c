/*
********************************************************************************************************
文件名：main.c
功  能：
备  注：
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

/*
********************************************************************************************************
更新日志：

*********************************************************************************************************
*/
#include "stm32f10x.h"
#include "bsp_sys.h"
#include "bsp_GPIO.h"

#include "stdio.h"

#define 	MAINMENU 									0
#define 	TRACT_IO_TEST     				1
#define 	LFT_MOTOR_TEST 						2
#define 	RHT_MOTOR_TEST 						3
#define 	CAR_CTRL     							4
#define 	SPEED_MSR 								5
#define 	BAT_MSR     							6
#define 	TRACK_MODE   							7
#define 	HELP 											8
int menuState;
int LFT_MOTOR_TEST_NUM;

int carStatus;

extern __IO uint16_t ADC_ConvertedValue;
extern int Encoder_Left,Encoder_Right;  //编码器脉冲数

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal; 


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
//***************************设置局部变量***************************//
	u32 ADC_VoltageShow; 
	u32 temp1,temp2,temp3;
//*****************************************************************//
	
//*****************************系统初始*****************************//
	
	STM32_System_Init();//所有系统配置在这个函数里完成
//	OLED_ShowString(0,0, "BAT:      V  OK",12);//显示电池电压：7.4V,正常值6.2-8,否则需要充电
//	OLED_ShowString(0,1, "SYS:      V  OK",12);//显示电池电压：5V
	menuState = TRACK_MODE; 
	LFT_MOTOR_TEST_NUM = 1;
	carStatus = 0;
//*****************************************************************//
	while (1)
	{
		switch(menuState)
		{
			case MAINMENU: {
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{	
					menuState = TRACT_IO_TEST;    //TRACK IO TEST
					OLED_Clear();
					OLED_ShowString(0,0, "  TRACK IO ",16);
				} 					
				break;
			}
			case TRACT_IO_TEST: {
				//刷新循迹IO状态
				temp3 = 1111;
				if(Find_O1 == 0) temp3 += 1000;
				if(Find_O2 == 0) temp3 += 100;
				if(Find_O3 == 0) temp3 += 10;
				if(Find_O4 == 0) temp3 += 1;
				OLED_ShowNum(56,6,temp3,4,16);  
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{
					menuState = LFT_MOTOR_TEST;    //LFT MOTOR TEST
					OLED_Clear();
					OLED_ShowString(0,0, "  LFT MOTOR TEST ",16);
					OLED_ShowString(0,2, "  PWM+ ",16);
					OLED_ShowString(0,4, "  PWM- ",16);
					OLED_ShowString(0,6, "  DIR   + ",16);
					LFT_MOTOR_TEST_NUM = 1;
					OLED_ShowString(8*12,2, "<- ",16);
				}					
				break;
			}
			case LFT_MOTOR_TEST: {
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{
					menuState = RHT_MOTOR_TEST;    //RHT MOTOR TEST
					OLED_Clear();
					OLED_ShowString(0,0, "  RHT MOTOR TEST ",16);
				}
				if( Key_Scan(GPIOC,GPIO_Pin_10,0) == 0)//向下切换按钮
				{
					OLED_ShowString(8*12,LFT_MOTOR_TEST_NUM*2, "   ",16);
					LFT_MOTOR_TEST_NUM++;
					if(LFT_MOTOR_TEST_NUM > 3) 
					{
						LFT_MOTOR_TEST_NUM = 1;
					}
					OLED_ShowString(8*12,LFT_MOTOR_TEST_NUM*2, "<-",16);
				} 
				
				if( Key_Scan(GPIOC,GPIO_Pin_11,0) == 0)//向上切换按钮
				{
					OLED_ShowString(48,0, "RHT",16);  

				}
				if( Key_Scan(GPIOC,GPIO_Pin_12,0) == 0)   //执行按钮
				{
						if(LFT_MOTOR_TEST_NUM == 1)
						{
							TIM3->CCR3 +=100;  //更新pwm
							if(TIM3->CCR3 >= 3000) TIM3->CCR3=3000;
							OLED_ShowNum(48,2,TIM3->CCR3,4,16); 
							//TIM3->CCR4=3000; //更新pwm
						} 
						else if(LFT_MOTOR_TEST_NUM == 2)
						{
							if(TIM3->CCR3 > 100) 
							TIM3->CCR3 -=100;  //更新pwm
							else TIM3->CCR3 =0; 
							OLED_ShowNum(48,4,TIM3->CCR3,4,16); 
							//TIM3->CCR4=3000; //更新pwm
						} 
						MOTO_Left(GO); 
					}
				break;
			}
			case RHT_MOTOR_TEST: {
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{
					menuState = CAR_CTRL;    //MAINMENU
					OLED_Clear();
					OLED_ShowString(0,0, "     CAR_CTRL   ",16);
					OLED_ShowString(0,2, "  PWM+ ",16);
					OLED_ShowString(0,4, "  PWM- ",16);
					//OLED_ShowString(0,6, "  DIR   + ",16);
					//LFT_MOTOR_TEST_NUM = 1;
					OLED_ShowString(8*12,2, "<- ",16);
					TIM3->CCR3 =2400;	
					TIM3->CCR4 =2500;
					Car_Go();
				}
				break;
			}
			case CAR_CTRL: {
				temp1 = TIM2 -> CNT;
				temp2 = TIM4 -> CNT;
				OLED_ShowNum(0,6,temp1,6,16); 
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{
					menuState = BAT_MSR;    //MAINMENU
					OLED_Clear();
					OLED_ShowString(0,0, "     BAT  MSR    ",16);
					OLED_ShowString(0,2,"         mV",16);
					//TIM3->CCR3 =2700;	
					//TIM3->CCR4 =2800;
					//Car_Go();
				}
				break;
			}
			case BAT_MSR: {
				ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
				ADC_VoltageShow = ADC_ConvertedValueLocal*1000;
				OLED_ShowNum(32,2,ADC_VoltageShow,4,16); 
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{
					menuState = TRACK_MODE;    //MAINMENU
					OLED_Clear();
					OLED_ShowString(0,0, "     Track Mode    ",16);
					OLED_ShowString(0,2,"   Smart Car",16);
					OLED_ShowString(0,4,"     fsl   ",16);        
					OLED_ShowString(0,6,"  2020-06-29  ",16);  
				}
				break;
			}
			case TRACK_MODE: {
				TRACK();
				if( Key_Scan(GPIOC,GPIO_Pin_8,0) == 0)//切换显示界面按钮
				{
					menuState = MAINMENU;    //MAINMENU
					OLED_Clear();
					OLED_ShowString(0,0, "     NIT    ",16);
					OLED_ShowString(0,2,"   Smart Car",16);
					OLED_ShowString(0,4,"     fsl   ",16);        
					OLED_ShowString(0,6,"  2020-06-29  ",16);  
				}
				break;
			}
			default :

			break;
		}	
		

			
			//显示左轮和右轮的输出转速 单位RPM 
  /*		temp1 = Encoder_Left*600/2496;
  		OLED_ShowNum(16,2,temp1,3,16);      //左轮实际减速箱输出转速  单位RPM
  		temp2 = Encoder_Right*600/2496;
			OLED_ShowNum(72,2,temp2,3,16);      //右轮实际减速箱输出转速  单位RPM
			
			//显示左轮和右轮的输出转速PWM
  		temp1 = TIM3->CCR3;
  		OLED_ShowNum(16,4,temp1,4,16);      //左轮实际减速箱输出转速  单位RPM
  		temp2 = TIM3->CCR4;
			OLED_ShowNum(64,4,temp2,4,16);      //右轮实际减速箱输出转速  单位RPM
			*/
//			temp3 = 1111;
//			if(Find_O1 == 0) temp3 += 1000;
//			if(Find_O2 == 0) temp3 += 100;
//			if(Find_O3 == 0) temp3 += 10;
//			if(Find_O4 == 0) temp3 += 1;
			/*
			OLED_ShowNum(56,6,temp3,4,16);      //右轮实际减速箱输出转速  单位RPM
			*/
		}
		
 
		
	
	}	



/*********************************************END OF FILE**********************/
