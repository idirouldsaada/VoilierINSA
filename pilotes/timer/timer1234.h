
#ifndef TIMER1234_H
#define TIMER1234_H

void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) );
float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us );

#endif