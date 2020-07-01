#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include "bsp_sys.h"
int PID_Calc_Left(int NextPoint,int Setpoint);
int PID_Calc_Right(int NextPoint,int Setpoint);
void showPID(void);
#endif

