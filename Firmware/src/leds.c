/**
 * @file leds.c
 * 
 * Este archivo contiene las funciones para controlar los LEDs.
 * Proporciona funciones para inicializar los LEDs, alternar su estado y apagarlos.
 * 
 * @author Angie Jaramillo
 *        Juan Manuel Rivera
 * 
 * @date 21-06-2025
 * 
 */


#include "leds.h"


void init_leds() {
    // Initialize the GPIO pins for the LEDs
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_put(LED_GREEN_PIN, 0); // Start with green LED off

    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_put(LED_RED_PIN, 1); // Start with red LED on
}

void toggle_leds() {
    // Toggle the state of the LEDs
    gpio_put(LED_GREEN_PIN, !gpio_get(LED_GREEN_PIN)); // Turn on green LED if it was off, and vice versa
    gpio_put(LED_RED_PIN, !gpio_get(LED_RED_PIN));     // Turn off red LED if it was on, and vice versa
}


void turn_off_leds(){
    // Turn on the red LED and turn off the green LED
    gpio_put(LED_GREEN_PIN, 0); // Green LED off
    gpio_put(LED_RED_PIN, 0);   // Red LED on
}