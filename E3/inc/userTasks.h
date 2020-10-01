/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/29
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*==================[inclusiones]============================================*/
#include "FreeRTOS.h"
#include "sapi.h"
#include "semphr.h"
#include <string.h>
#include "FreeRTOSConfig.h"
#include "auxs.h"
//#include "FSM.h"
/*==================[definiciones y macros]==================================*/
#define LED_RATE_MS 40
#define MAX_RATE_MS 3000
#define BUTTON_RATE_MS 1

#define LED_RATE pdMS_TO_TICKS(LED_RATE_MS)
#define MAX_RATE pdMS_TO_TICKS(MAX_RATE_MS)
#define BUTTON_RATE pdMS_TO_TICKS(BUTTON_RATE_MS)
/*==================[definiciones de datos]=========================*/
extern gpioMap_t teclas[];
extern gpioMap_t leds[];
extern uint16_t n_teclas;
extern QueueHandle_t queue_tiempo_leds;
/*==================[prototipos de tareas]====================*/
void tarea_led( void* taskParmPtr );
void tarea_tecla( void* taskParmPtr );

#endif /* __USER_TASKS_H__ */
