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

#include "FSM.h"

#ifndef LIB_H
#define LIB_H




struct 
{
    int level;                  // Nivel actual del test
    float speed_kmh;            // Velocidad en km/h
    uint64_t interval_ms;       // Intervalo en milisegundos para el pitido
} test_state = {1, 8.5, 8470};  // Estado inicial del test

void update_interval_for_level(int level);
int64_t alarm_callback(alarm_id_t id, void *user_data);
int64_t level_up_callback(alarm_id_t id, void *user_data);

void init_test_state();
void calculate_results();
void start_test();
void stop_test();
void reset_test_state();







#endif // LIB_H