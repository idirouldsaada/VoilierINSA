#ifndef CODINC_H
#define CODINC_H

// ATTENTION:
// Le codeur incrémental compte jusqu'à 1440
// 90° = 360
// 180° = 720
// etc...
// => diviser le résultat de TIM3_CNT par 4


// Permet de mettre à zéro le codeur lors du passage à 0
void CodInc_RAZ();

void CodInc_Init(TIM_TypeDef *Timer);

void EXTI9_5_IRQHandler (void);

void Init_IT_CodInc(void (*IT_function) (void), u8 Priority);

#endif