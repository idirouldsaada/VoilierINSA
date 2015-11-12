// pilote_ADC.c
// THOMAS Camille, TLEMSANI Ophélie, OULD-SAADA Idir Berg  & VAN WIJK Gido
// INSA Toulouse 2015 - GEI
// 4AE_SE_TP3

#include "pilote_ADC.h"

float Init_ADC_Single_Conv(ADC_TypeDef * ADC, u16 Duree_Acq_us, int Chaine) {
	
		//Activation du clock de l'ADC
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	} else {
		return -1; //A configurer correctement
	}
	
	
	ADC->CR2 |= ADC_CR2_ADON; //Activation du ADC (single conversion)
	
	ADC->CR2 &= ~(ADC_CR2_ADON);
	
	//Choix d'une chaine de conversion
	ADC->SQR1 = ADC->SQR1 &~(ADC_SQR1_L); //L=0 veut dire une seule chaine de conversion
	
	//Choix de chaine
	ADC->SQR3 = ADC->SQR3&~(ADC_SQR3_SQ1);
	ADC->SQR3 |= Chaine << 0x00;
	
	//Enable IT
	ADC->CR1 |= ADC_CR1_EOCIE;
	
	ADC->CR2 |= ADC_CR2_ADON; //Debut de la conversion (single conversion)
	
	return 1.0;
}