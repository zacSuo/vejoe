#ifndef SENSER_HALL_H
#define SENSER_HALL_H
	
#include <sys.h>	 

#define ENCODER_TIM_PERIOD (u16)(0xffff)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);


#endif