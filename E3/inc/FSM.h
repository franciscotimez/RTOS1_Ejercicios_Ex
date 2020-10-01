/*=============================================================================
 * Copyright (c) 2020, Martin N. Menendez <menendezmartin81@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/09/03
 * Version: v1.1
 *===========================================================================*/
#ifndef _FSM_H_
#define _FSM_H_

/*==================[inclusiones]============================================*/
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include "semphr.h"
#include "auxs.h"
/*==================[definiciones y macros]==================================*/
#define DEBOUNCE_TIME 40
/*==================[definiciones de datos]=========================*/
extern QueueHandle_t queue_tiempo_leds;

// Tipo de dato FSM
typedef enum
{
    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING
} fsmButtonState_t;

// Estructura principal
typedef struct
{
	gpioMap_t tecla;			//config
	gpioMap_t led;				//config

	TickType_t tiempo_medido;	//variables
	fsmButtonState_t fsmButtonState;//variables
	TickType_t tiempo_down;		//variables

	uint8_t contFalling  ;		//variables
	uint8_t contRising  ;		//variables
} tLedTecla;


/*==================[prototipos de funciones]====================*/
TickType_t get_diff();
void clear_diff();

void fsmButtonError( tLedTecla* config );
void fsmButtonInit( tLedTecla* config , uint16_t N_teclas );
void fsmButtonUpdate( tLedTecla* config , uint16_t N_teclas );
void buttonPressed( tLedTecla* config );
void buttonReleased( tLedTecla* config );

#endif /* _FSM_H_ */
