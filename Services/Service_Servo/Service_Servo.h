#ifndef SERVO_H
#define SERVO_H

#include "pilote_TIMER.h"
#include "pilote_IO.h"

//Initialise le servo avec le timer 4 channel 3 sur la sortie B8 avec une fréquence de 50Hz
void Init_Servo (); 

//Regle l'angle du servo
void Set_Angle_Servo(int Angle);

#endif