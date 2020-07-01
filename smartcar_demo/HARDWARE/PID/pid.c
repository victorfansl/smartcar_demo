#include "pid.h"
//1.����ʽpid
//����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
/*************************************/
float   Proportion=0.6;                               //�������� Proportional Const
float   Integral=0.1;                                 //���ֳ��� Integral Const
float   Derivative=0;                                 //΢�ֳ��� Derivative Const

//��ʾpid������OLED��
void showPID(void)
{
	float temp1,temp2,temp3;
	char PID_P[3],PID_I[3],PID_D[3];
	temp1 = Proportion;
	sprintf(PID_P,"%1.1f",temp1);
  //OLED_ShowString(16,4, PID_P,16);  
	
	temp2 = Integral;
	sprintf(PID_I,"%1.1f",temp2);
  //OLED_ShowString(56,4, PID_I,16); 
	
	temp3 = Derivative;
	sprintf(PID_D,"%1.1f",temp3);
  //OLED_ShowString(104,4, PID_D,16); 
}

/********************����ʽPID�������************************************/
//NextPoint��ǰ���ֵ
//SetPoint�趨ֵ

//����PID
int PID_Calc_Left(int NextPoint,int SetPoint) 
{
                             
	static int      LastError;                                //Error[-1]
	static int      PrevError;                                //Error[-2]
  int iError,Outpid;                                        //��ǰ���
	
  iError=SetPoint-NextPoint;                                //��������
  Outpid=(Proportion * iError)                              //E[k]��
              -(Integral * LastError)                       //E[k-1]��
              +(Derivative * PrevError);                    //E[k-2]��
              
  PrevError=LastError;                                      //�洢�������´μ���
  LastError=iError;
  return(Outpid);                                           //��������ֵ
}


//����PID
int PID_Calc_Right(int NextPoint,int SetPoint) 
{                      
	static int      LastError;                                //Error[-1]
	static int      PrevError;                                //Error[-2]
  int iError,Outpid;                                        //��ǰ���
	
  iError=SetPoint-NextPoint;                                //��������
  Outpid=(Proportion * iError)                              //E[k]��
              -(Integral * LastError)                       //E[k-1]��
              +(Derivative * PrevError);                    //E[k-2]��
              
  PrevError=LastError;                                      //�洢�������´μ���
  LastError=iError;
  return(Outpid);                                           //��������ֵ
}

