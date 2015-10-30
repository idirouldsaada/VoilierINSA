// test_timer.c
// IDIR BERG OULD-SAADA & GIDO VAN WIJK
// 4AE_SE_TP3

#include "stm32f10x.h" 
#include "pilote_IO.h"
#include "clock.h"
#include "timer1234.h"
#include "CodInc.h"

void TIM2_IT_blink (void);
void CodInc_IT_Index (void);

int main() {	
	
	// Configuration du clock (passage de 8MHz à 72MHz)
	CLOCK_Configure();
	
	Port_IO_Init_Input(GPIOA, 5);
	Port_IO_Init_Input(GPIOA, 6);
	Port_IO_Init_Input(GPIOA, 7);
	
	// Codeur incrémental sur TIM3
	CodInc_Init(TIM3);
	
	// Gérer l'IT venant de l'index de la girouette
	Init_IT_CodInc(CodInc_IT_Index, 7);
	
	Init_Timer_PWM(TIM4,10);
	
	while(1) {
		// 
	}
	
	return 0;
}

void CodInc_IT_Index (void) {
	CodInc_RAZ();
}


