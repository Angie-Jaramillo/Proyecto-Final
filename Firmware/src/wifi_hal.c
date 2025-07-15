/**
 * @file wifi_hal.h
 *
 * Este archivo de encabezado contiene la declaración de las funciones de `wifi_hal`.
 * Está diseñado para proporcionar una interfaz simple para operaciones WiFi
 *
 * @authors Angie Jaramillo
 *         Juan Manuel Rivera
 * @date 21-06-2025
 */

#include "wifi_hal.h"


void static inline setup_udp_listener(udp_recv_fn udp_receive_callback) {
    struct udp_pcb *pcb = udp_new();
    if (!pcb) {
        printf("Error al crear socket UDP\n");
        return;
    }
    udp_bind(pcb, IP_ADDR_ANY, UDP_PORT);
    udp_recv(pcb, udp_receive_callback, NULL);
    printf("UDP listener activo en el puerto %d\n", UDP_PORT);
}

void static inline set_static_ip(int rp)
{
    ip4_addr_t ipaddr, netmask, gw;

    if (rp)
    {
        IP4_ADDR(&ipaddr, 10, 42, 0, 2);
        IP4_ADDR(&gw, 10, 42, 0, 1);
    }
    else
    {
         IP4_ADDR(&ipaddr, 10, 42, 0, 3);
        IP4_ADDR(&gw, 10, 42, 0, 1);
    }

    IP4_ADDR(&netmask, 255, 255, 255, 0);
    netif_set_addr(netif_default, &ipaddr, &netmask, &gw);
    printf("IP estática configurada: %s\n", ip4addr_ntoa(&ipaddr));
}

int dev_wifi_connect (udp_recv_fn udp_callback) {
    
    if (cyw43_arch_init())
    {
        return -1;
    }

    if (SSID == NULL || PASSWORD == NULL) {
        printf("SSID o contraseña no configurados.\n");
        return -1;
    }

    printf("Conectando a la red Wi-Fi: %s\n", SSID);

    cyw43_arch_enable_sta_mode();

    set_static_ip(RP);

    int ret = cyw43_arch_wifi_connect_timeout_ms(SSID, PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 5000);
    
    if (ret) {
        printf("Error al conectar a la red Wi-Fi: %s\n", SSID);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

        return -1;
    }

    printf("Conectado a la red Wi-Fi: %s\n", SSID);
    printf("IP del cliente: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));

    setup_udp_listener(udp_callback);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    return 0;
}



void wifi_get_ip(void)
{
    printf("IP Address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
}



