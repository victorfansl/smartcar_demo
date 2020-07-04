#include "car.h"
#include "pid.h"

int Encoder_Left,Encoder_Right;  //编码器脉冲数
int leftEncoderOvfTimes,rightEncoderOvfTimes;
int Moto_Left,Moto_Right; 
int para_L,para_R;//增量

//这个设置很重要
int SetPoint=70;//设置目标值单位RPM，如果转换成线速度  = setopint*轮子周长 = setpoint*3.14*0.065(轮子直径65mm) 单位就是m/min  一定要搞清楚车轮转速和线速的关系


//使用减速比是1：120的减速箱。根据实际电机的减速比的配置修改以下参数
//6240=13*4*120：霍尔编码器13线，STM32编码器模式 4倍频，减速箱1：120
//2496=13*4*48：霍尔编码器13线，STM32编码器模式 4倍频，减速箱1：48
#define SetPointL SetPoint*2496/600                 //换算成编码器脉冲数，因为最终pid控制的是编码器的脉冲数量
#define SetPointR SetPoint*2496/600                 //换算成编码器脉冲数，因为最终pid控制的是编码器的脉冲数量

//各种变量
u32 temp1,temp2;
float temp3,temp4;
char set_speed[5];//车速显示小数
char speed[5];//车速显示小数
//Time1定时器1中断服务函数
//100ms定时
void TIM6_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET) //时间到了
	{
		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);     //清中断
			LED_Flash(5);                                   //500ms闪烁一次
			Encoder_Left=Read_Encoder(2)-30000;                   //读取编码器 
			Encoder_Right=Read_Encoder(4)-30000;                  //读取编码器
		
			//小车的移动速度，即轮子线速度
			temp3 = (Encoder_Right+Encoder_Left)/2*600/2496 * 0.065*3.1415;//计算车速，左轮和右轮速度和除以2 单位 m/min
			sprintf(speed,"%2.2f",temp3);
		 // OLED_ShowString(48,0, speed,16);  //OLED显示车速
		
			if(Encoder_Left<0)//如果电机反转了
			{
				Encoder_Left = -Encoder_Left;
			}
				if(Encoder_Right<0)
			{
				Encoder_Right = -Encoder_Right;
			}
			para_L=PID_Calc_Left(Encoder_Left,SetPointL);	  //左电机，计数得到增量式PID的增量数值 
		  para_R=PID_Calc_Right(Encoder_Right,SetPointR);	//右电机，计数得到增量式PID的增量数值 
			if((para_L<-3)||(para_L>3))                     //不做 PID 调整，避免误差较小时频繁调节引起震荡。
			{
				Moto_Left +=para_L;  
			}   
			if((para_R<-3)||(para_R>3))                     //不做 PID 调整，避免误差较小时频繁调节引起震荡。
			{
				Moto_Right +=para_R;  
			}			
  		if(Moto_Left>3500)Moto_Left=3000;    //限幅 防止烧毁电机
			if(Moto_Right>3500)Moto_Right=3000;  //限幅
			
			TIM3->CCR3=Moto_Left;  //更新pwm
			TIM3->CCR4=Moto_Right; //更新pwm
			//显示pid参数
			showPID();
			//显示左轮和右轮的输出转速 单位RPM 
  		temp1 = Encoder_Left*600/2496;
//  		OLED_ShowNum(16,2,temp1,3,16);      //左轮实际减速箱输出转速  单位RPM
  		temp2 = Encoder_Right*600/2496;
//			OLED_ShowNum(16,4,temp2,3,16);      //右轮实际减速箱输出转速  单位RPM
			


			//设定值显示
			//OLED_ShowNum(48,6,SetPoint,3,12);    //显示设定的车轮转速 单位RPM
//			temp4 = SetPoint*3.1415*0.065;       //计算设定的线速度
//			sprintf(set_speed,"%2.2f",temp4);
//		  OLED_ShowString(48,7, set_speed,12);  //设定的线速度 单位m/min

			
		}
	
		
}



