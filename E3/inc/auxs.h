/*=============================================================================
 * Copyright (c) 2020, Martin N. Menendez <menendezmartin81@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/09/03
 * Version: v1.1
 *===========================================================================*/
#ifndef _AUXS_H_
#define _AUXS_H_

/*==================[inclusiones]============================================*/
#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include "semphr.h"

#include <string.h>
#include "FreeRTOSConfig.h"
#include "FSM.h"

/*==================[definiciones y macros]==================================*/
#define LED_ERROR 		LEDR
#define MAX_SEM 3

#define PRIORITY 1
#define SIZE     1
#define STR_AUX  20

#define MSG_ERROR_TASK   "Error al crear las tareas. \n\r"
#define MSG_ERROR_SEM	 "Error al crear los semaforos.\r\n"
#define MSG_ERROR_QUEUE	 "Error al crear las colas.\r\n"

/*==================[prototipos]=========================*/
void tecla_led_init(void);
void tareas_crear(TaskFunction_t tarea,const char * const nombre);
void tarea_crear(TaskFunction_t tarea,const char * const nombre,uint8_t stack,void * const parametros,uint8_t prioridad,TaskHandle_t * const puntero);

#endif /* _AUXS_H_ */
