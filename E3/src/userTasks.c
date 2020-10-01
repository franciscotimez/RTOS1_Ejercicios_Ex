/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/29
 *===========================================================================*/

/*==================[inclusiones]============================================*/
#include "userTasks.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[tareas]====================*/

void tarea_tecla( void* taskParmPtr )
{
	tLedTecla* config = (tLedTecla*) taskParmPtr;

	fsmButtonInit( config, n_teclas );

	while( TRUE )
	{
		fsmButtonUpdate( config, n_teclas  );
		vTaskDelay( BUTTON_RATE );
	}
}

void tarea_led( void* taskParmPtr )
{
	// ---------- CONFIGURACIONES ------------------------------
	tLedTecla* config = (tLedTecla*) taskParmPtr;

	TickType_t xPeriodicity =  MAX_RATE;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	// ---------- REPETIR POR SIEMPRE --------------------------
	bool_t ordenar = FALSE;
	tLedTecla* ptrTecla = 0;
	TickType_t dif[n_teclas];
	gpioMap_t ledsTask[n_teclas];
	TickType_t auxTick;
	gpioMap_t auxGpio;

	for(int i = 0 ; i < n_teclas ; i++){
		dif[i] = 0;
		ledsTask[i] = 0;
	}

	while( TRUE )
	{
		while(xQueueReceive( queue_tiempo_leds , &ptrTecla, 1) == pdTRUE){
			for(int i = 0 ; i < n_teclas ; i++){
				if(ledsTask[i] == ptrTecla->led || ledsTask[i] == 0){
					ledsTask[i] = ptrTecla->led;
					dif[i] = ptrTecla->tiempo_medido;
					ordenar = TRUE;
					break;
				}
			}
		}
		if(ordenar){
			bool_t ordenado = FALSE;
			while(!ordenado){
				ordenado = TRUE;
				for(int i = 0 ; i < (n_teclas - 1) ; i++){
					if(dif[i] > dif[i+1]){
						auxTick = dif[i];
						dif[i] = dif[i+1];
						dif[i+1] = auxTick;
						auxGpio = ledsTask[i];
						ledsTask[i] = ledsTask[i+1];
						ledsTask[i+1] = auxGpio;
						ordenado = FALSE;
					}
				}
			}
		}

		for(int i = 0 ; i < n_teclas ; i++)
			if(ledsTask[i] != 0)
				gpioWrite( ledsTask[i]  , ON );
		auxTick = 0;
		for(int i = 0 ; i < n_teclas ; i++){
			if(ledsTask[i] != 0){
				vTaskDelay( dif[i] - auxTick);
				auxTick = dif[i];
				gpioWrite( ledsTask[i]  , OFF );
			}
		}

		vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
	}
}
