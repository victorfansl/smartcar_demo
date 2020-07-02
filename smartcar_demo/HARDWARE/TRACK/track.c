
#include "bsp_GPIO.h"   
#include "delay.h"
#include "track.h"


#define LEFT_BASE  2400
#define RIGHT_BASE  2500

extern int carStatus;
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

void  BLACK_LINE_DETECT(void)
{
		
}
//循迹、、循迹模块 黑线输出高电平1  白线低电平0
//小车最左端是O4----最右端是O1
//循迹路面：白色路面黑色引导线，即寻黑线。
//黑线 传感器输出1，白线输出0
void TRACK(void)
{
	
	//全是白线，前进
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// 白线，前进
	{	
		if(carStatus <= -3 ) 
			carStatus	=	-4;
		else if(carStatus >= 3 ) 
			carStatus		=	4;
		else
			carStatus	=	0;
	}
	////O2在黑线  右边有黑线 小车偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2寻到黑线
	{
			carStatus = -1;
	}

	////O2在黑线 O1黑线  右边有黑线 小车偏偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1寻到黑线
	{
			carStatus = -2;
	}
	////O1在黑线  右边有黑线 小车偏偏偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))// O1寻到黑线
	{
			carStatus = -3;
		
	}
	////O3在黑线  左边边有黑线 小车偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3寻到黑线
	{
			carStatus = 1;
	}
	////O3，O4在黑线  左边边有黑线 小车偏偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3 O4寻到黑线
	{
		carStatus = 2;
	}
	
	////O4在黑线  左边边有黑线 小车偏偏偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4寻到黑线
	{
			carStatus = 3;
	}
		//停车
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))// 所以传感器都在黑线
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