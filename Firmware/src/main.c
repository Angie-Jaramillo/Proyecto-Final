/**
 * @file main.c
 * 
 * Este archivo contiene la función principal del programa.
 * Inicializa el sistema, configura la conexión Wi-Fi y espera a recibir mensajes UDP.
 * 
 * @authors Angie Jaramillo
 *          Juan Manuel Rivera
 * @date 21-06-2025
 * 
 * 
 * 
 */

 // bibliotecas de c
#include <stdio.h>

// bibliotecas SDK de Raspberry Pi Pico
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/platform.h"
#include "pico/sync.h"


// bibliotecas personalizadas
#include "wifi_hal.h"
#include "lib.h"


// Definición de la función principal
// Esta función es el punto de entrada del programa y se encarga de inicializar el sistema
int main() {

    stdio_init_all();

    sleep_ms(3000); // Allow time for the system to stabilize

    dev_wifi_connect(udp_receive_callback);     // Conecta al Wi-Fi y configura el listener UDP

    printf("¡Esperando el boton!\n");       
    printf("¡Comenzando Test de Léger!\n");
    
    while (true) {
        cyw43_arch_poll(); // necesario para que funcione lwIP
        sleep_ms(10);
    }

    cyw43_arch_deinit();
    return 0;
}