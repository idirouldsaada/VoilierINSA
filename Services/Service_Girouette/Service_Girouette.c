// Service_Girouette.c
// THOMAS Camille, TLEMSANI Ophélie, OULD-SAADA Idir Berg  & VAN WIJK Gido
// INSA Toulouse 2015 - GEI
// 4AE_SE_TP3

#include "Service_Girouette.h"

void Init_Girouette () {
	CodInc_Init(TIM3);
	Init_IT_CodInc(CodInc_IT_Index, 7);
}

int Get_Angle_Girouette () {
	return Get_Value_CodInc()/4;
}

void CodInc_IT_Index (void) {
	CodInc_RAZ();
}
