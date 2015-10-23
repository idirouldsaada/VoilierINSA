#ifndef PILOTE_IO_H
#define PILOTE_IO_H

// Configurer une broche en output push-pull
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche);	

// Configurer une broche en floating input
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche);

// Mettre la broche à 1
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche);

// Mettre la broche à 0
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche);

// Inverser l'état d'une broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche);

// Lire l'état d'une broche
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche);

// Vérifie si l'on a bien demandé une broche entre 0 et 15
char Broche_Valide (u8 Broche);

#endif