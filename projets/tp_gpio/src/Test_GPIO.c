//__________________________________________________________
// projet/TP_GPIO/      MAIN.C
// Tentative de faire clignoter une diode
// BINOME : BERG OULD-SAADA Idir & VAN WIJK Gido
// ETAT : compilé et testé
// MODIFICATIONS : 
// 08/09/15 : iBOSS&GVW => TODO
// 14/09     : suppression des options de compilation et nettoyage des TODO
// 1/09/2013 : 0xACC0 => Nettoyage des chemins pour windows 7 + question sur le .h
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document"  pour ouvrir le fichier
#include "../../../pilotes/gpio/pilote_IO.h"
//TODO : 
// appréciez la déclaration de GPIOB ligne 1409 :-) la valeur numérique GPIOB_BASE (ligne 1316)
// est castée en pointeur sur une structure de type GPIO_Typedef.
// A quelle adresse pointe ce pointeur (complétez la ligne suivante) ?
// GPIOB_BASE  = APB2PERIPH_BASE + ???? = ????
// APB2PERIPH_BASE = PERIPH_BASE + ????
// PERIPH_BASE = ????
// GPIOB <=> ( ( GPIO_Typedef *) 0x??????? ) 
// On construit ainsi un pointeur à l'adresse désirée. Vérifiez cette adresse
// avec la doc du Reference Manual page 167 et la Table 1 de la page 41. 
// 
// Observez la déclaration de la structure GPIO_Typedef ligne 1000 à 1010
// Sachant que GPIOB->CRH est unbe notation simplifiée de (*GPIOB).CRH, le terme GPIOB->CRH est-il
// 	a) un registre natif
//  b) un pointeur natif
//  c) une macro donnant un registre
//  d) une macro donnant un pointeur
// A quelle adresse agit GPIOB->CRH ? 0x??????

int main (void)
{
	char flipflop = 1;
	
 	// Cette ligne valide les horloges de quelques périphériques, pour le moment ignorez-la 
	// mais CONSERVEZ CETTE LIGNE EN DEBUT DE PROGRAMME !
 	(RCC->APB2ENR)|= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

	
	// On met tous les bits du registre CRH de GPIOB à 1
	// CRH = 1111 1111 : 1111 1111 : 1111 1111 : 1111 1111 
	GPIOB->CRH = 0xFFFFFFFF;
	// TODO : Vérifiez le bon fonctionnement en passant en simulation (debug-> start)
	// Puis ensimu cliquez sur Peripherals->GPIOB et observez le contenu du registre. OK
	
	// La ligne suivante est équivalente mais elle mets des 0
	(*GPIOB).CRH = 0;
	
	//config du PA0 en floating input
	Port_IO_Init_Input(GPIOA, 0);
	
	//__ configuration du port PB.8 en sortie (output push-pull)
	Port_IO_Init_Output(GPIOB, 8);
	
	//__ configuration du port PB.9 en sortie (output push-pull)
	// CRH = xxxx xxxx : xxxx xxxx : xxxx xxxx : 0001 xxxx 
	Port_IO_Init_Output(GPIOB, 9);
	
	// TODO : Qu'est-ce que veut dire (x << y) ?
	// On met le 1 en position 4 
	// TODO : Pour ne pas toucher aux bits autres que ceux de configruation du port 9, il faut faire un masque. Faites le !  OK
	 
	// Faire clignoter la diode sur le port PB.9
	while(1)
	{
		// Check bouton wkup
		if (!Port_IO_Read(GPIOA, 0)) {
			Port_IO_Set(GPIOB, 8);
		} else {
			Port_IO_Reset(GPIOB, 8);
		}
		if (flipflop == 1) {
		// ODR = xxxx xxxx : xxxx xxxx : xxxx xxx1 : xxxx xxxx
			Port_IO_Set(GPIOB, 9);
			
			// TODO : Comment faire pour ne changer que le bit 9 ?
			// on met un masque
			flipflop = 0;
			// TODO : Comment faier pour se passer du flipflop en utilisant directement la valeur de ODR ?
		} else {
		// ODR=xxxx xxxx | xxxx xxxx | xxxx xxx0 |xxxx xxxx
			Port_IO_Reset(GPIOB, 9);
					
			flipflop = 1;
		}
	}

	return 0;
}

