#include "Pilote_Attente.h"

#include "../Inc/main.h"
#include "cmsis_os.h"

void Pilote_Attente(unsigned char Valeur)
{
	HAL_Delay(Valeur);
}



void piloteDelai_attendreMs(uint32_t delaiMs)
{
    osDelay(delaiMs);
}
