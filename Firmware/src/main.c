#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/platform.h"
#include "pico/sync.h"

#include "wifi_hal.h"
#include "lib.h"

int main() {

    stdio_init_all();

    sleep_ms(3000); // Allow time for the system to stabilize

    dev_wifi_connect(udp_receive_callback);

    printf("¡Esperando el boton!\n");
    printf("¡Comenzando Test de Léger!\n");
    
    while (true) {
        cyw43_arch_poll(); // necesario para que funcione lwIP
        sleep_ms(10);

    }

    cyw43_arch_deinit();
    return 0;
}