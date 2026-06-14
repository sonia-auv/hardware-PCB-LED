/*
 * led_data.h
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#ifndef LED_DATA_H_
#define LED_DATA_H_
//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques
enum led_command{
    LED_OFF = 0,
    LED_ON = 1,
    LED_BLINK = 2
};
#define SLAVE_LED_ID 0x09

struct led_data{
    uint8_t command;
    uint8_t led_number;
    uint8_t R;
    uint8_t G;
    uint8_t B;
};
extern struct led_data data_led;

//Fonctions publiques:

//Variables publiques:
//pas de variables publiques

#endif /* LED_DATA_H_ */
