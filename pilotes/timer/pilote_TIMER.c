// pilote_TIMER.c
// THOMAS Camille, TLEMSANI Ophélie, OULD-SAADA Idir Berg  & VAN WIJK Gido
// INSA Toulouse 2015 - GEI
// 4AE_SE_TP3

#include "pilote_TIMER.h"

//Variables
int Periode_PWM_us;

void (*PtrFn_TIM2) (void);

//********************Fonctions internes************************************

void brancheClockTimer (TIM_TypeDef *Timer) {
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
	
	brancheClockTimer(Timer);
	
	Timer->CR1|= 0x1; //allumer le compteur
	Timer->DIER|= 0x1; //autoriser l'interruption
	
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

void startTimer (TIM_TypeDef *Timer) {
	Timer->CR1|= 0x1; //allumer le compteur
}

void stopTimer (TIM_TypeDef *Timer) {
	Timer->CR1 &= ~0x1;  //éteindre le compteur
}

//*******************************************************
//PWM OUTPUT
//*******************************************************

 void Set_PWM_DC(TIM_TypeDef *Timer, int Duty_Cycle, int Channel){
     int ARR;
     if ((Duty_Cycle <= 100) && (Duty_Cycle >= 0)) {
			 
       ARR = Timer->ARR;
			 
			 switch (Channel) {
				 case 1:
         Timer->CCR1 = (ARR*Duty_Cycle)/100;
				 break;
				 case 2:
         Timer->CCR2 = (ARR*Duty_Cycle)/100;
				 break;
				 case 3:
         Timer->CCR3 = (ARR*Duty_Cycle)/100;
				 break;
				 case 4:
         Timer->CCR4 = (ARR*Duty_Cycle)/100;
				 break;
			 }
     }
 }

 void Init_PWM_Out (TIM_TypeDef *Timer, float Frequence_PWM_kHz, int Channel){
 	Periode_PWM_us = 1000/(Frequence_PWM_kHz);
 	Timer_1234_Init(Timer, Periode_PWM_us);
	switch (Channel) {
	 case 1:
		//On utilite le PWM en mode 1
    Timer->CCMR1 &= ~(0b110<<4);
    Timer->CCMR1 |= (0b110<<4);
		Timer->CCER &= ~(0<<0);
		Timer->CCER |= (1<<0);
    //On initialise le PWM avec un facteur cyclique de 0%
		Timer->CCR1=0;
		break;
	 
	 case 2:
		 //On utilite le PWM en mode 1
    Timer->CCMR1 &= ~(0b110<<12);
    Timer->CCMR1 |= (0b110<<12);
		Timer->CCER &= ~(0<<4);
		Timer->CCER |= (1<<4);
    //On initialise le PWM avec un facteur cyclique de 0%
		Timer->CCR2=0;
		break;
	 
	 case 3:
		 //On utilite le PWM en mode 1
    Timer->CCMR2 &= ~(0b110<<4);
    Timer->CCMR2 |= (0b110<<4);
		Timer->CCER &= ~(0<<8);
		Timer->CCER |= (1<<8);
    //On initialise le PWM avec un facteur cyclique de 0%
		Timer->CCR3=0;
		break;
	 
	 case 4:
		 //On utilite le PWM en mode 1
    Timer->CCMR2 &= ~(0b110<<12);
    Timer->CCMR2 |= (0b110<<12);
		Timer->CCER &= ~(0<<12);
		Timer->CCER |= (1<<12);
    //On initialise le PWM avec un facteur cyclique de 0%
		Timer->CCR4=0;
		break;
	 
	 default:
		 break;
		 
 }
		
 }
 
//*******************************************************
//PWM INPUT
//*******************************************************
 
 /**Fonction qui configure le mode pwm input du timer 4 
Fonctionne avec 2 signaux: IC1 sur front montant détecte la période fixe
et IC2 sur front descendant mesure la durée de l'impulsion 
Input: Periode_PWM (en ms) choisie légèrement supérieure à la période fixe donnée par le CDC **/

void Pwm_Input_Mode_TIM4(float Periode_PWM){
	
//Init du timer 4: 25 paliers répartis sur un intervalle de 2.5ms
	TIM4->ARR = 24; //25 paliers
	int PSC_val = (0.0025 * 72000000)/24;
	TIM4->PSC = PSC_val;	
	
//Select the active input 
	TIM4->CCMR1	&= ~(TIM_CCMR1_CC1S_1) ;
	TIM4->CCMR1 |= (TIM_CCMR1_CC1S_0) ;
	TIM4->CCMR1	|= (TIM_CCMR1_CC2S_1) ;
	TIM4->CCMR1 &= ~(TIM_CCMR1_CC2S_0) ;
	
//Select the active polarity for TI1FP1
	TIM4->CCR1 &=~ TIM_CCER_CC1P; //IC1: rising edge
	TIM4->CCR1 |= TIM_CCER_CC2P; //IC2: falling edge

//Select the valid trigger input (synchronize the counter)
	TIM4->SMCR &= ~(TIM_SMCR_TS);
	TIM4->SMCR = TIM4->SMCR | TIM_SMCR_TS_0 | TIM_SMCR_TS_2;

//Reset mode for rising edge
	TIM4->SMCR &= ~(TIM_SMCR_SMS);
	TIM4->SMCR = TIM4->SMCR |TIM_SMCR_SMS_2;
	
//Enable the captures 
	TIM4->CCER |= TIM_CCER_CC1E ;
	TIM4->CCER |= TIM_CCER_CC1E ;
}
 
 //*******************************************************
 // Codeur incremental
 //*******************************************************
void (*PtrFn_CodInc) (void);
 
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

	brancheClockTimer(Timer);
	// Bits SMS:
	// 001 : Counts on TI2 edge, depending on state TI1
	// 010 : Counts on TI1 edge, depending on state TI2
	// 011 : Counts on both edges
	Timer->SMCR &= ~(0b111 << 0);
	Timer->SMCR |= 0b011 << 0;
	Timer->PSC = 0;
	Timer->ARR = 1440-1;
}

int Get_Value_CodInc(){
	return TIM3->CNT;
}