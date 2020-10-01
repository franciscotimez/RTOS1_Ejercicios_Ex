/*=============================================================================
 * Copyright (c) 2020, Martin N. Menendez <menendezmartin81@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/09/03
 * Version: v1.1
 *===========================================================================*/

/*==================[inclusiones]============================================*/
#include "FSM.h"
/*==================[prototipos]============================================*/

void fsmButtonError( tLedTecla* config );
void fsmButtonInit( tLedTecla* config , uint16_t N_teclas );
void fsmButtonUpdate( tLedTecla* config , uint16_t N_teclas );
void buttonPressed( tLedTecla* config );
void buttonReleased( tLedTecla* config );

/*==================[funciones]============================================*/

/* accion de el evento de tecla pulsada */
void buttonPressed( tLedTecla* config )
{
	config->tiempo_down = xTaskGetTickCount();
}

/* accion de el evento de tecla liberada */
void buttonReleased( tLedTecla* config )
{
	config->tiempo_medido = xTaskGetTickCount() - config->tiempo_down;

	if (config->tiempo_medido > 0)
		xQueueSend( queue_tiempo_leds ,&config ,  0  );
}

void fsmButtonError( tLedTecla* config )
{
	config->fsmButtonState = BUTTON_UP;
}

void fsmButtonInit( tLedTecla* config , uint16_t N_teclas )
{
	uint16_t i;
	for(i = 0 ; i < N_teclas ; i++ ){
		config[i].contFalling = 0;
		config[i].contRising = 0;
		config[i].fsmButtonState = BUTTON_UP;  // Set initial state
	}
}



// FSM Update Sate Function
void fsmButtonUpdate( tLedTecla* config , uint16_t N_teclas )
{
	uint16_t i;
	for(i = 0 ; i < N_teclas ; i++ ){
		switch( config[i].fsmButtonState )
		{
		case STATE_BUTTON_UP:
			/* CHECK TRANSITION CONDITIONS */
			if( !gpioRead( config[i].tecla ) )
			{
				config[i].fsmButtonState = STATE_BUTTON_FALLING;
			}
			break;

		case STATE_BUTTON_FALLING:
			/* ENTRY */
			//gpioWrite( config[i].led  , OFF );
			/* CHECK TRANSITION CONDITIONS */
			if( config[i].contFalling >= DEBOUNCE_TIME )
			{
				if( !gpioRead( config[i].tecla ) )
				{
					config[i].fsmButtonState = STATE_BUTTON_DOWN;

					/* ACCION DEL EVENTO !*/
					buttonPressed(&config[i]);
				}
				else
				{
					config[i].fsmButtonState = STATE_BUTTON_UP;
				}

				config[i].contFalling = 0;
			}

			config[i].contFalling++;

			/* LEAVE */
			break;

		case STATE_BUTTON_DOWN:
			/* CHECK TRANSITION CONDITIONS */
			if( gpioRead( config[i].tecla ) )
			{
				config[i].fsmButtonState = STATE_BUTTON_RISING;
			}
			break;

		case STATE_BUTTON_RISING:
			/* ENTRY */
			//gpioWrite( config[i].led  , ON );
			/* CHECK TRANSITION CONDITIONS */

			if( config[i].contRising >= DEBOUNCE_TIME )
			{
				if( gpioRead( config[i].tecla ) )
				{
					config[i].fsmButtonState = STATE_BUTTON_UP;

					/* ACCION DEL EVENTO ! */
					buttonReleased(&config[i]);
				}
				else
				{
					config[i].fsmButtonState = STATE_BUTTON_DOWN;
				}
				config[i].contRising = 0;
			}
			config[i].contRising++;

			/* LEAVE */
			break;

		default:
			fsmButtonError(&config[i]);
			break;
		}
	}
}
