#ifndef PILOTE_ADC_H
#define PILOTE_ADC_H

#include <stm32f10x.h>
float Init_ADC_Single_Conv(ADC_TypeDef * ADC, u16 Duree_Acq_us, int Chaine);



#endif