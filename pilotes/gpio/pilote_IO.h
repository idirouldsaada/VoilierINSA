// Configurer une broche en output push-pull
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche);	

// Configurer une broche en floating input
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche);

// Mettre la broche � 1
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche);

// Mettre la broche � 0
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche);

// Inverser l'�tat d'une broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche);

// Lire l'�tat d'une broche
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche);

char Broche_Valide (u8 Broche);