/*
 * RS485_Definition.h
 *
 *  Created on: 19 juin 2026
 *      Author: ilyes
 */

#ifndef INC_RS485_DEFINITION_H_
#define INC_RS485_DEFINITION_H_

/*
 * Slave Ids
 */
#define SLAVE_KILLMISSION       4
#define SLAVE_ESC               5
#define SLAVE_IO                6
#define SLAVE_STATE_SCREEN      7
#define SLAVE_PWR_MANAGEMENT    8
#define SLAVE_LED               9

/*
 * Command Ids
 */
#define CMD_MISSION             0
#define CMD_KILL                1

#define CMD_VOLTAGE             0
#define CMD_CURRENT             1
#define CMD_TEMPERATURE         2

#define CMD_READ_MOTOR          15
#define CMD_ACT_MOTOR           16
#define CMD_PWM                 17

#define CMD_IO_TEMP             0
#define CMD_IO_DROPPER_ACTION   1
#define CMD_IO_TORPEDO_ACTION   2
#define CMD_IO_ARM_ACTION       3
#define CMD_IO_LEAK_SENSOR      4

#define CMD_KEEP_ALIVE          30

#endif /* INC_RS485_DEFINITION_H_ */
