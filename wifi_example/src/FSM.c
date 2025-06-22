/**
 * @file FSM.c
 * 
 * This source file contains the implementation of the `FSM` function.
 * 
 */


#include "FSM.h"

// Definición de un tipo para la función de estado
typedef void (*state_function_t)(void);

static void state_waiting_for_start(void);
static void state_running_test(void);
static void state_finished_test(void);


