// test_timer.c
// IDIR BERG OULD-SAADA & GIDO VAN WIJK
// 4AE_SE_TP3

#include <stm32f10x.h>
#include "pilote_IO.h"
#include "clock.h"
#include "pilote_TIMER.h"
#include "Service_Servo.h"
#include "Service_Girouette.h"

void TIM2_IT_blink (void);
void Test_Angle(void);

int Angle;
int Augmente;
int AngleCom;

int main() {	
	
	// Configuration du clock (passage de 8MHz à 72MHz)
	CLOCK_Configure();
	
	//test servo output
	Timer_1234_Init(TIM2, 3000000.0 );
	Timer_Active_IT( TIM2, 10, Test_Angle );
	Init_Servo();
	Angle=0;
	Augmente=1;
	Set_Angle_Servo(Angle);
	
	Init_Girouette();

	
	while(1) {
		// 
		//Set_Angle_Servo(Get_Angle_);
		
	}
	
	return 0;
}

void Test_Angle(void) {
	if ((Angle <= 10) && (Angle >= 0)) {
		Augmente = 1;
	} else if ((Angle <=90) && (Angle >= 80)) {
		Augmente = 0;
	}
		
	if (Angle < 90 && Augmente) {
		Angle = Angle + 10;
		Set_Angle_Servo(Angle);
	} else {
		Angle = Angle - 10;
		Set_Angle_Servo(Angle);
	}
}


