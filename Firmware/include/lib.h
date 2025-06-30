/**
 * @file lib.h
 * 
 * This header file contains the declaration of the `lib` function.
 * 
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"
#include "pico/platform.h"
#include "pico/sync.h"

#include "leds.h"

#ifndef LIB_H
#define LIB_H

#define DISTANCE_M 20.0f  // Distancia en metros para el test de Léger

/**
 * @brief Estructura que representa el estado del test de Léger.
 * 
 * Esta estructura contiene información sobre el nivel actual del test,
 * la velocidad en km/h y el intervalo en milisegundos para el pitido.
 * 
 */
typedef struct test_state_t 
{
    int level;                  // Nivel actual del test
    float speed_kmh;            // Velocidad en km/h
    uint64_t interval_ms;       // Intervalo en milisegundos para el pitido
} test_state_t; 




extern test_state_t test_state;  // Declaración del estado del test

/**
 * @brief Actualiza el intervalo de pitido basado en el nivel actual.
 * 
 * @param level El nivel actual del test.
 * 
 * 
 */
void update_interval_for_level(int level);

/**
 * @brief Callback para el temporizador de pitido.
 * 
 * Este callback se llama cuando el temporizador de pitido se activa.
 */
int64_t alarm_callback(alarm_id_t id, void *user_data);

/**
 * @brief Callback para el temporizador de cambio de nivel.
 * 
 * Este callback se llama cuando el temporizador de cambio de nivel se activa.
 */
int64_t level_up_callback(alarm_id_t id, void *user_data);

/**
 * @brief Inicia el test de Léger.
 * 
 * Esta función configura el primer nivel del test y comienza el temporizador
 * para los pitidos y el cambio de nivel.
 */
void start_test();

/**
 * @brief Calcula los resultados del test de Léger.
 * 
 * Esta función calcula y muestra los resultados finales del test.
 */
void calculate_results();

/**
 * @brief Detiene el test de Léger.
 * 
 * Esta función detiene el temporizador y resetea el estado del test.
 */
void stop_test();

/**
 * @brief Resetea el test de Léger.
 * 
 * Esta función resetea el test a su configuración inicial.
 */
void reset_test();







#endif // LIB_H