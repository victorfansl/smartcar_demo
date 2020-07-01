/*
********************************************************************************************************
文件名：bsp_GPIO.c
功  能：配置需要的普通IO
备  注：最好把所有的IO在这里配置，方便管理
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

/*
********************************************************************************************************
GPIO更新日志：
1.2017-2-6，编写LED初始化程序

*********************************************************************************************************
*/

#include "bsp_GPIO.h"   
#include "delay.h"

/*
********************************************************************************************************
函数名称：void LED_GPIO_Config(void)
函数功能：初始化LED1的GPIO功能
硬件连接：LED1----PC13
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LED1_CLK, ENABLE); 	/*开启GPIO的外设时钟*/																   
		GPIO_InitStructure.GPIO_Pin = LED1_Pin;	/*选择要控制的GPIO引脚*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*设置引脚模式为通用推挽输出*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*设置引脚速率为50MHz */ 
		GPIO_Init(LED1_PORT, &GPIO_InitStructure);/*调用库函数，初始化GPIOC13*/	
}

//LED闪烁
void LED_Flash(int time)
{	
		 static int temp;
		if(++temp==time)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction) (1 - GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)))	;//LED 蓝色色状态翻转
			temp=0;
		}
		
}

/*
********************************************************************************************************
函数名称：void KEY_GPIO_Config(void)
函数功能：初始化KEY的GPIO功能
硬件连接：DWN----PC6
					UP----PC7
					RST----PC8
					LFT----PC9
					MID----PC10
					RHT----PC11
					SET----PC12


备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void KEY_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE); 	/*开启GPIO的外设时钟*/																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	/*选择要控制的GPIO引脚*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   /*设置引脚模式为*/   
		GPIO_Init(KEY_PORT, &GPIO_InitStructure);/*调用库函数，初始化GPIOC13*/	

}
/**
  * @brief   检测是否有按键按下
  * @param   具体的端口和端口位
  *		@arg GPIOx: x可以是（A...G） 
  *		@arg GPIO_PIN 可以是GPIO_PIN_x（x可以是1...16）
   *  @arg ONSTS 是GPIO_PIN_x（x可以是1...16）对应按键按下时IO口的电平
  * @retval  按键的状态
  *		@arg KEY_ON:按键按下
  *		@arg KEY_OFF:按键没按下
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,uint8_t ONSTS)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ONSTS ) 
	{	   
		/*延时消抖*/
		Delay_us(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ONSTS )  
		{	 
			/*等待按键释放 */
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ONSTS);   
			return 	0;	 
		}
		else
			return 1;
	}
	else
		return 1;
}

//循迹IO初始化
//寻迹传感器从右到左以此O1 O2 O3 O4 
//硬件连接 O1-PA3，O2-PA4，O3-PA5，O4-PA6，
//要初始化为输入模式
void TRACK_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6;//选择IO端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//配置为上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//根据GPIO_InitStructure中指定的参数初始化外设GPIOD寄存器

} 
//循迹、、循迹模块 黑线输出高电平1  白线低电平0
//小车最左端是O4----最右端是O1
//循迹路面：白色路面黑色引导线，即寻黑线。
//黑线 传感器输出1，白线输出0
void Find(void)
{
	//全是白线，前进
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// 白线，前进
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Go();
	}
	////O2在黑线  右边有黑线 小车偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2寻到黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Turn_Right();
	}

	////O2在黑线 O1黑线  右边有黑线 小车偏偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1寻到黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Turn_Right();
	}
	////O1在黑线  右边有黑线 小车偏偏偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))// O1寻到黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Turn_Right();
		
	}
	////O3在黑线  左边边有黑线 小车偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3寻到黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Turn_Left();
	}
	////O3，O4在黑线  左边边有黑线 小车偏偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3 O4寻到黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Turn_Left();
	}
	
	////O4在黑线  左边边有黑线 小车偏偏偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4寻到黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM
			Car_Turn_Left();
			
	}
	
	
	
	//停车
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))// 所以传感器都在黑线
	{
			MOTO_PWM_Out(80, 80);	//调整PWM 停车
		  Car_Stop();
	}
	
	
}
//------------------End of File----------------------------
