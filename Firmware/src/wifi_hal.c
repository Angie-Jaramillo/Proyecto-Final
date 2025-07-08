/**
 * @file wifi_hal.h
 *
 * This header file contains the declaration of the `wifi_hal` function.
 * It is designed to provide a simple interface for WiFi operations
 *
 * @author Angie Jaramillo
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

void static inline set_static_ip(int is_ap)
{
    ip4_addr_t ipaddr, netmask, gw;

    if (is_ap)
    {
        IP4_ADDR(&ipaddr, 192, 168, 4, 1);
        IP4_ADDR(&gw, 192, 168, 4, 1);
    }
    else
    {
        IP4_ADDR(&ipaddr, 192, 168, 4, 2);
        IP4_ADDR(&gw, 192, 168, 4, 1);
    }

    IP4_ADDR(&netmask, 255, 255, 255, 0);
    netif_set_addr(netif_default, &ipaddr, &netmask, &gw);
    printf("IP estática configurada: %s\n", ip4addr_ntoa(&ipaddr));
}


int wifi_connect(udp_recv_fn udp_callback)
{
    if (cyw43_arch_init())
    {
        return -1;
    }

    printf("WiFi hardware initialized successfully.\n");

#if IS_AP
    // Este codigo solo se compila y se ejecuta si IS_AP es 1
    printf("Configurando Wi-Fi en modo AP...\n");
    cyw43_arch_enable_ap_mode(SSID, PASSWORD, CYW43_AUTH_WPA2_AES_PSK);
    set_static_ip(1); // Establecer IP fija del AP

    printf("Modo AP activado con SSID: %s\n", SSID);
    printf("IP del AP: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
#else
    // Este codigo solo se compila y se ejecuta si IS_AP es 0
    printf("Configurando Wi-Fi en modo STA...\n");
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(SSID, PASSWORD,
                                           CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("No se pudo conectar a %s\n", SSID);
        return -1;
    }
    printf("Conectado al AP con IP: %s\n",
           ip4addr_ntoa(netif_ip4_addr(netif_default)));

    printf("Modo STA activado con SSID: %s\n", SSID);
    set_static_ip(0); // Establecer IP fija del cliente
    printf("IP del cliente: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
#endif

    // Set the default network interface
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    setup_udp_listener(udp_callback);

}

void wifi_get_ip(void)
{
    printf("IP Address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
}



