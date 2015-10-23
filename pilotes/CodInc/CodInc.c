// CodInc.c
// IDIR BERG OULD-SAADA & GIDO VAN WIJK
// 4AE_SE_TP3

#include <stm32f10x.h>
#include "CodInc.h"

// Initier interruption IO
void (*PtrFn_CodInc) (void);

void brancheClockTimer_CodInc (TIM_TypeDef *Timer) {
	if (Timer == TIM1) {
		(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN; //brancher le clock
	}
	else if (Timer == TIM2) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN; //brancher le clock
	}
	else if (Timer == TIM3) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN; //brancher le clock
	}
	else if (Timer == TIM4) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN; //brancher le clock
	}	
	Timer->CR1 = TIM_CR1_CEN;
}

void Init_IT_CodInc(void (*IT_function) (void), u8 Priority) {
	PtrFn_CodInc = IT_function;
	
	EXTI->IMR |= EXTI_IMR_MR5;
	EXTI->RTSR |= EXTI_RTSR_TR5;
	
	NVIC->ISER[0] = (NVIC->ISER[0]) | (NVIC_ISER_SETENA_23);
	NVIC->IP[30] = Priority; //Initialisation de la priorité
}

void EXTI9_5_IRQHandler (void) {
	EXTI->PR |= EXTI_PR_PR5;
	if (PtrFn_CodInc != 0) {
		(*PtrFn_CodInc)();
	}
}

void CodInc_RAZ() {
	TIM3->CNT=0x0000;
}

void CodInc_Init(TIM_TypeDef *Timer) {

	brancheClockTimer_CodInc(Timer);
	// Bits SMS:
	// 001 : Counts on TI2 edge, depending on state TI1
	// 010 : Counts on TI1 edge, depending on state TI2
	// 011 : Counts on both edges
	Timer->SMCR &= ~(0b111 << 0);
	Timer->SMCR |= 0b011 << 0;
	Timer->PSC = 0;
	Timer->ARR = 1440-1;
		
}