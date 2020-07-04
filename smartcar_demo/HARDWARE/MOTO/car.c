#include "car.h"
#include "pid.h"

int Encoder_Left,Encoder_Right;  //������������
int leftEncoderOvfTimes,rightEncoderOvfTimes;
int Moto_Left,Moto_Right; 
int para_L,para_R;//����

//������ú���Ҫ
int SetPoint=70;//����Ŀ��ֵ��λRPM�����ת�������ٶ�  = setopint*�����ܳ� = setpoint*3.14*0.065(����ֱ��65mm) ��λ����m/min  һ��Ҫ���������ת�ٺ����ٵĹ�ϵ


//ʹ�ü��ٱ���1��120�ļ����䡣����ʵ�ʵ���ļ��ٱȵ������޸����²���
//6240=13*4*120������������13�ߣ�STM32������ģʽ 4��Ƶ��������1��120
//2496=13*4*48������������13�ߣ�STM32������ģʽ 4��Ƶ��������1��48
#define SetPointL SetPoint*2496/600                 //����ɱ���������������Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointR SetPoint*2496/600                 //����ɱ���������������Ϊ����pid���Ƶ��Ǳ���������������

//���ֱ���
u32 temp1,temp2;
float temp3,temp4;
char set_speed[5];//������ʾС��
char speed[5];//������ʾС��
//Time1��ʱ��1�жϷ�����
//100ms��ʱ
void TIM6_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET) //ʱ�䵽��
	{
		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);     //���ж�
			LED_Flash(5);                                   //500ms��˸һ��
			Encoder_Left=Read_Encoder(2)-30000;                   //��ȡ������ 
			Encoder_Right=Read_Encoder(4)-30000;                  //��ȡ������
		
			//С�����ƶ��ٶȣ����������ٶ�
			temp3 = (Encoder_Right+Encoder_Left)/2*600/2496 * 0.065*3.1415;//���㳵�٣����ֺ������ٶȺͳ���2 ��λ m/min
			sprintf(speed,"%2.2f",temp3);
		 // OLED_ShowString(48,0, speed,16);  //OLED��ʾ����
		
			if(Encoder_Left<0)//��������ת��
			{
				Encoder_Left = -Encoder_Left;
			}
				if(Encoder_Right<0)
			{
				Encoder_Right = -Encoder_Right;
			}
			para_L=PID_Calc_Left(Encoder_Left,SetPointL);	  //�����������õ�����ʽPID��������ֵ 
		  para_R=PID_Calc_Right(Encoder_Right,SetPointR);	//�ҵ���������õ�����ʽPID��������ֵ 
			if((para_L<-3)||(para_L>3))                     //���� PID ��������������СʱƵ�����������𵴡�
			{
				Moto_Left +=para_L;  
			}   
			if((para_R<-3)||(para_R>3))                     //���� PID ��������������СʱƵ�����������𵴡�
			{
				Moto_Right +=para_R;  
			}			
  		if(Moto_Left>3500)Moto_Left=3000;    //�޷� ��ֹ�ջٵ��
			if(Moto_Right>3500)Moto_Right=3000;  //�޷�
			
			TIM3->CCR3=Moto_Left;  //����pwm
			TIM3->CCR4=Moto_Right; //����pwm
			//��ʾpid����
			showPID();
			//��ʾ���ֺ����ֵ����ת�� ��λRPM 
  		temp1 = Encoder_Left*600/2496;
//  		OLED_ShowNum(16,2,temp1,3,16);      //����ʵ�ʼ��������ת��  ��λRPM
  		temp2 = Encoder_Right*600/2496;
//			OLED_ShowNum(16,4,temp2,3,16);      //����ʵ�ʼ��������ת��  ��λRPM
			


			//�趨ֵ��ʾ
			//OLED_ShowNum(48,6,SetPoint,3,12);    //��ʾ�趨�ĳ���ת�� ��λRPM
//			temp4 = SetPoint*3.1415*0.065;       //�����趨�����ٶ�
//			sprintf(set_speed,"%2.2f",temp4);
//		  OLED_ShowString(48,7, set_speed,12);  //�趨�����ٶ� ��λm/min

			
		}
	
		
}



