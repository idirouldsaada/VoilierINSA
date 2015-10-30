
#ifndef TIMER1234_H
#define TIMER1234_H

// Active la demande d'interruption du timer, configure l'appel de fonction
void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) );

// Initialise le timer pour une durée déterminée
float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us );

// Initialise un Timer pour un codeur incrémental
void CodInc_Init(TIM_TypeDef *Timer);

void brancheClockTimer (TIM_TypeDef *Timer);

void Init_Timer_PWM (TIM_TypeDef *Timer, float Frequence_PWM_kHz);

#endif