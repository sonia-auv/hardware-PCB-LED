/*
 * Interface_LectureSwitch.c
 *
 *  Created on: Jun 14, 2026
 *      Author: audou
 */
#include "../Inc/main.h"
#include "../Pilote/PiloteSwitch1.h"
#include "Interface_LectureSwitch.h"

void Lecture_Switch(void){
	if(PiloteSwitch1_LitEntree()==1){
	Bouton1_Val =1;
	return;
	}
    if(PiloteSwitch1_LitEntree()==0){
    Bouton1_Val =0;
    return;
    }
}
