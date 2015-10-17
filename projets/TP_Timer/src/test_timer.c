// test_timer.c
// IDIR BERG OULD-SAADA & GIDO VAN WIJK
// 4AE_SE_TP3

#include "stm32f10x.h" 
#include "pilote_IO.h"
#include "clock.h"
#include "timer1234.h"

void TIM2_IT_blink (void);


int main() {
	
	//config clock (passage de 8MHz à 72MHz)
	CLOCK_Configure();
	
	// config du timer 2 à 500ms
	Timer_1234_Init(TIM2,50000);
	
	Port_IO_Init_Output(GPIOB,9);
	
	Timer_Active_IT(TIM2, 1, TIM2_IT_blink);
	
	while(1) {
		// 
	}
	return 0;
}

void TIM2_IT_blink (void) {

	Port_IO_Blink(GPIOB, 9);
}

