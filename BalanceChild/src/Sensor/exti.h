#ifndef __EXTI_H
#define __EXTI_H	
#include "Sensor/Hall.h"

#define INT PBin(2)   //连接到MPU6050的中断引脚

void MiniBalance_EXTI_Init(void);	//外部中断初始化	

#endif


