// pilote_IO.c
// IDIR BERG OULD-SAADA & GIDO VAN WIJK
// 4AE_SE_TP3

#include <stm32f10x.h>
#include "pilote_IO.h"

// Configurer une broche en output push-pull

void Port_IO_Init_Clock (GPIO_TypeDef * Port) {
	if (Port == GPIOA) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPAEN;
	}
	else if (Port == GPIOB) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPBEN;
	}
	else if (Port == GPIOC) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPCEN;
	}
	else if (Port == GPIOD) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPDEN;
	}
	else if (Port == GPIOE) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPEEN;
	}
	else if (Port == GPIOF) {
		// à configurer
	}
	else if (Port == GPIOG) {
		// à configurer
	}
}
		
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche) {
	
	Port_IO_Init_Clock(Port);
		
	if ((Broche <= 7) && (Broche >= 0)) {
		Port->CRL = Port->CRL & ~(0xF << (Broche*4));  // mise à zero du champ
		Port->CRL = Port->CRL | (0x1 << (Broche*4));   // output push-pull = 0001
	} else if ((Broche >= 8) && (Broche <= 15)) {
		Port->CRH = Port->CRH & ~(0xF << ((Broche-8)*4));  // mise à zero du champ
		Port->CRH = Port->CRH | (0x1 << ((Broche-8)*4));   // output push-pull = 0001
	} else return -1;
	
	return 0;
}

// Configurer une broche en floating input
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche) {
	
	Port_IO_Init_Clock(Port);
		
	if ((Broche <= 7) && (Broche >= 0)) {
		Port->CRL = Port->CRL & ~(0xF << (Broche*4));  // mise à zero du champ
		Port->CRL = Port->CRL | (0x4 << (Broche*4));   // floating input = 0100
	} else if ((Broche >= 8) && (Broche <= 15)) {
		Port->CRH = Port->CRH & ~(0xF << ((Broche-8)*4));  // mise à zero du champ
		Port->CRH = Port->CRH | (0x4 << ((Broche-8)*4));   // floating input = 0100
	} else return -1;
	
	return 0;
}

// Mettre la broche à 1
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche) { 
	
	if (Broche_Valide(Broche)) {
		Port->ODR = Port->ODR | (0x01 << Broche); 
	}
	
}

// Mettre la broche à 0
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche) { 
	
	if (Broche_Valide(Broche)) {
		Port->ODR = Port->ODR & ~(0x01 << Broche); 
	}
	
}

// Inverser l'état d'une broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche) {
	
	if (Broche_Valide(Broche)) {
		Port->ODR = Port->ODR ^ (0x01 << Broche); 
	}
}

// Lire l'état d'une broche
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) {
		if ((Port->IDR & 1<<Broche) == 0) return 0;
		return 1;
}

char Broche_Valide (u8 Broche) {
	return ((Broche <= 15) && (Broche >= 0));
}
