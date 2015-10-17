// timer1234.c
// IDIR BERG OULD-SAADA & GIDO VAN WIJK
// 4AE_SE_TP3

#include <stm32f10x.h>
#include "timer1234.h"
#include "pilote_IO.h"

/** 
* Configure les Timers 1, 2, 3 et 4
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer considéré
* @param Duree_us Intervalle de temps exprimé en µs entre
* deux débordements successifs
* @return Le durée véritable qui a été configurée
**/
void (*PtrFn_TIM2) (void);

void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) ){

	if (Timer==TIM1){
	(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN;
		//à configurer
}

else if (Timer==TIM2){
	PtrFn_TIM2 = IT_function;
	(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN;
	TIM2->CR1= TIM2->CR1|0x1;
	TIM2->DIER = TIM2->DIER | 0x1;
	NVIC->ISER[0] = (NVIC->ISER[0]) | (NVIC_ISER_SETENA_28);
	NVIC->IP[35] = Priority; //Initialisation de la priorité
}

else if (Timer==TIM3){
	(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN;
	TIM3->CR1= TIM3->CR1|0x1;
	TIM3->DIER = TIM3->DIER | 0x1;
	NVIC->ISER[0] = (NVIC->ISER[0]) | (NVIC_ISER_SETENA_29);
	NVIC->IP[36] = Priority; //Initialisation de la priorité
}

else if (Timer==TIM4){
	(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN;
	TIM4->CR1= TIM4->CR1|0x1;
	TIM4->DIER = TIM4->DIER | 0x1;
	NVIC->ISER[0] = (NVIC->ISER[0]) | (NVIC_ISER_SETENA_30);
	NVIC->IP[37] = Priority; //Initialisation de la priorité
}
}
float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us ) {
	//On suppose que le clock est branché au Timer, et que le compteur est allumé.
	int PSC_Value;
	int ARR_Value;
	
	if (Timer == TIM1) {
		(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN; //brancher le clock
	}
	else if (Timer == TIM2) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN; //brancher le clock
		TIM2->CR1|= 0x1; //allumer le compteur	
		TIM2->DIER|= 0x1; //autoriser l'interruption
	}
	else if (Timer == TIM3) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN; //brancher le clock
		TIM3->CR1|= 0x1; //allumer le compteur	
		TIM3->DIER|= 0x1; //autoriser l'interruption
	}
	else if (Timer == TIM4) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN; //brancher le clock
		TIM4->CR1|= 0x1;  //allumer le compteur										
		TIM4->DIER|= 0x1;  //autoriser l'interruption
	}	
	
	int Total_Scale = 72000000*Duree_us/1000000;
	
	PSC_Value = Total_Scale/65535; //valeur pour rentrer sur 16 bit.
	ARR_Value = Total_Scale/(PSC_Value + 1); //ARR ne dépasse jamais 65535 à cause du +1
	
	PSC_Value=PSC_Value+1;
	
	Timer->PSC = PSC_Value-1;
	Timer->ARR = ARR_Value-1;
	
	return PSC_Value * ARR_Value/72000000;  //temps réel après arrondis et troncatures
}


void TIM2_IRQHandler (void) {
	TIM2->SR = TIM2->SR &~(TIM_SR_UIF);
	if (PtrFn_TIM2 != 0) {
		(*PtrFn_TIM2)();
	}
}