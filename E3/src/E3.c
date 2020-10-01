/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/29
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "E3.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
DEBUG_PRINT_ENABLE;
/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- CONFIGURACIONES ------------------------------

	boardConfig();								// Inicializar y configurar la plataforma

	debugPrintConfigUart( UART, BAUD_RATE );	// UART for debug messages
	printf( MSG_WELCOME );

	tecla_led_init();							// Inicializar estructura de datos

	 // Crear y validar tarea en freeRTOS
	tareas_crear(tarea_tecla,MSG_TECLA);		 // Tareas de teclas
	tareas_crear(tarea_led,MSG_LED);			 // Tareas de leds

    // Iniciar scheduler
    vTaskStartScheduler();				// Enciende tick | Crea idle y pone en ready | Evalua las tareas creadas | Prioridad mas alta pasa a running

    // ---------- REPETIR POR SIEMPRE --------------------------
    while( TRUE )
    {
        // Si cae en este while 1 significa que no pudo iniciar el scheduler
    }

    // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
    // directamenteno sobre un microcontroladore y no es llamado por ningun
    // Sistema Operativo, como en el caso de un programa para PC.
    return TRUE;
}
/*==================[fin del archivo]========================================*/
