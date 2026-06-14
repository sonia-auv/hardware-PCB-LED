/*
 * ProcessusAllumage.c
 *
 *  Created on: May 30, 2026
 *      Author: audou
 */
#include "../Inc/main.h"

#include "../Interface/Interface_LEDROUGE.h"
#include "../Interface/Interface_Attente.h"
#include "ProcessusAllumage.h"

void processusClignotant_Initialise(void)
{
interface_LED_Rouge_Initialise();
}
void processusClignotant_Debut(unsigned char Valeur)
{
interface_LED_Rouge_Allume();
interface_attente(Valeur);
interface_LED_Rouge_Eteint();
}
void processusClignotant_Eteint(unsigned char Valeur)
{
interface_LED_Rouge_Eteint();
interface_attente(Valeur);
interface_LED_Rouge_Eteint();
}


