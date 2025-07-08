#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/platform.h"
#include "pico/sync.h"

#include "wifi_hal.h"
#include "lib.h"

#define WIFI_SSID "ANGIE"
#define WIFI_PASSWORD "1001804091"


#define IP_ADDR "192.168.1.113"
#define NETMASK "255.255.255.0"
#define GATEWAY "192.168.1.254"


int main() {

    stdio_init_all();

    sleep_ms(1000); // Allow time for the system to stabilize


    wifi_init();
    if (wifi_connect(WIFI_SSID, WIFI_PASSWORD, udp_receive_callback) != 0) {
        printf("Failed to connect to WiFi.\n");
        return -1; // Exit if connection fails
    }
    printf("Connected to WiFi SSID: %s\n", WIFI_SSID);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    wifi_get_ip(); // Print the IP address after connection

    // Set a static IP address (optional)
    if (set_wifi_static_ip(IP_ADDR, NETMASK,GATEWAY) != 0) {
        printf("Failed to set static IP address.\n");
        return -1; // Exit if setting static IP fails
    }

   
    printf("¡Comenzando Test de Léger!\n");
    

    while (true) {
        cyw43_arch_poll(); // necesario para que funcione lwIP
        sleep_ms(10);
        // Aqui deberias comparar las banderas para saber que boton se presionó

    }

    cyw43_arch_deinit();
    return 0;
}