
#ifndef PILOTE_TIMER_H
#define PILOTE_TIMER_H

#include <stm32f10x.h>
// Active la demande d'interruption du timer, configure l'appel de fonction
void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) );

// Initialise le timer pour une durée déterminée
float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us );


void brancheClockTimer (TIM_TypeDef *Timer);

void startTimer (TIM_TypeDef *Timer);

void stopTimer (TIM_TypeDef *Timer);

//*******************************************************
//PWM 
void Set_PWM_DC(TIM_TypeDef *Timer, int Duty_Cycle, int Channel);

void Init_PWM_Out (TIM_TypeDef *Timer, float Frequence_PWM_kHz, int Channel);

void Pwm_Input_Mode_TIM4(float Periode_PWM);

//*******************************************************
//CODEUR INCREMENTAL
void Init_IT_CodInc(void (*IT_function) (void), u8 Priority);

void CodInc_Init(TIM_TypeDef *Timer);

void CodInc_RAZ();

int Get_Value_CodInc();




#endif