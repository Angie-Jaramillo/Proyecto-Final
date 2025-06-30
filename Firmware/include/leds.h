#ifndef _LEDS_H
#define _LEDS_H


#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Define GPIO pins for LEDs
#define LED_GREEN_PIN 16    // Pin for green LED
#define LED_RED_PIN 17      // Pin for red LED


/**
 * @brief Initializes the LEDs by setting the GPIO pins to output mode.
 * 
 */
void init_leds();

/**
 * @brief Toggle the leds between red and green.
 * 
 */
void toggle_leds();

/**
 * @brief Turns on the red LED and turns off the green LED.
 * 
 */
void turn_off_leds();



#endif // _LEDS_H