/*
 * AllumerLEDPB13.c
 *
 *  Created on: May 30, 2026
 *      Author: audou
 */
#include "../Inc/main.h"
#include "../Pilote/PilotePB13.h"
#include "Interface_LEDROUGE.h"

void interface_LED_Rouge_Allume(void)
{
	pilotePB13_metLaSortie1(INTERFACE_LED_ROUGE_VALEUR_POUR_ALLUMER);
}

void interface_LED_Rouge_Eteint(void)
{
	pilotePB13_metLaSortie1(INTERFACE_LED_ROUGE_VALEUR_POUR_ETEINDRE);
}

void interface_LED_Rouge_Initialise(void)
{
	pilotePB13_metLaSortie1(INTERFACE_LED_ROUGE_VALEUR_POUR_ETEINDRE);
}

