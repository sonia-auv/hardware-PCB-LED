//pilotePB13:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "PilotePB13.h"
#include "../Inc/main.h"
void pilotePB13_metLaSortie1(unsigned char Valeur)
{
HAL_GPIO_WritePin(PILOTEPA2_PORT,PILOTEPA2_PIN,(GPIO_PinState)Valeur);
}

void pilotePB13_initialise(void){
	HAL_GPIO_WritePin(PILOTEPA2_PORT,PILOTEPA2_PIN,GPIO_PIN_RESET);
}
