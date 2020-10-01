/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/29
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __E3_H__
#define __E3_H__

/*=====[Inclusions of public function dependencies]==========================*/

/*==================[inclusiones]============================================*/
#include "FreeRTOSConfig.h"


#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include "auxs.h"

#include "userTasks.h"
#include "FSM.h"

/*==================[definiciones y macros]==================================*/
#define MSG_WELCOME "Ejercicio E_3.\r\n"
#define BAUD_RATE 115200
#define UART UART_USB

#define MSG_TECLA	"tarea_tecla_"
#define MSG_LED     "tarea_led_"

#endif /* __E3_H__ */
