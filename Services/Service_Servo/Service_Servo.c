// Service_Servo.c
// THOMAS Camille, TLEMSANI Ophélie, OULD-SAADA Idir Berg  & VAN WIJK Gido
// INSA Toulouse 2015 - GEI
// 4AE_SE_TP3

#include "Service_Servo.h"

void Init_Servo () {
	Init_PWM_Out(TIM4,0.05,3);
	Port_IO_Init_Output_AF(GPIOB,8);
}

void Set_Angle_Servo (int AngleServo) {
// Duty		Degrees
// 2.5					0	
// 5					45
// 7.5				90	
// 10					135
// 12.5				180	
	int DC;
	
	DC=(2.5/45)*AngleServo+2.5;
	Set_PWM_DC(TIM4,DC,3);
}