#ifndef CODINC_H
#define CODINC_H

// ATTENTION:
// Le codeur incr�mental compte jusqu'� 1440
// 90� = 360
// 180� = 720
// etc...
// => diviser le r�sultat de TIM3_CNT par 4


// Permet de mettre � z�ro le codeur lors du passage � 0
void CodInc_RAZ();

void CodInc_Init(TIM_TypeDef *Timer);

void EXTI9_5_IRQHandler (void);

void Init_IT_CodInc(void (*IT_function) (void), u8 Priority);

#endif