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


static char ip_str[16] = {0};



int wifi_init(void) {
    if (cyw43_arch_init()) {
        return -1;                  // Error initializing WiFi hardware
    }
    printf("WiFi hardware initialized successfully.\n");
    return 0;                       // Success
}

int wifi_connect(const char *ssid, const char *password) {
   
    if (ssid == NULL || password == NULL) {
        printf("SSID or password is NULL.\n");
        return -1;                  // Return error code for null parameters
    }

    cyw43_arch_enable_sta_mode();  // Enable station mode (client mode)

    printf("Connecting to WiFi SSID: %s\n", ssid);
    int ret = cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 10000); // 10s timeout
    if (ret != 0) {
        printf("Failed to connect to WiFi: %d\n", ret);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

        return ret;                // Return error code
    }

    printf("Connected to WiFi SSID: %s\n", ssid);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

} 


void wifi_get_ip(void) {
    printf("IP Address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));

}

/**
 * Configura una dirección IP estática para la conexión WiFi
 * 
 * @param ip La dirección IP estática a asignar (ej. "192.168.1.100")
 * @param netmask La máscara de red (ej. "255.255.255.0")
 * @param gateway La puerta de enlace (ej. "192.168.1.1")
 * @return 0 si éxito, -1 si error en formato de IP, -2 si interfaz no disponible
 */
int set_wifi_static_ip(const char *ip, const char *netmask, const char *gateway) {
    // Verificar que la interfaz de red esté disponible
    if (netif_default == NULL) {
        printf("Error: No hay interfaz de red disponible\n");
        return -2;
    }

    sleep_ms(100); // Esperar breve momento para estabilizar conexión
    
    ip4_addr_t ip_addr, mask_addr, gw_addr;

    // Convertir strings a estructuras ip4_addr_t
    if (!ip4addr_aton(ip, &ip_addr) || 
        !ip4addr_aton(netmask, &mask_addr) || 
        !ip4addr_aton(gateway, &gw_addr)) {
        printf("Error: Formato de dirección IP inválido\n");
        printf("Debe usar formato como: 192.168.1.100\n");
        return -1;
    }

    // Configurar la dirección IP estática
    netif_set_addr(netif_default, &ip_addr, &mask_addr, &gw_addr);
    sleep_ms(100); // Esperar a que se apliquen los cambios

    // Verificar y mostrar la configuración aplicada
    printf("\nConfiguración IP estática aplicada:\n");
    printf("IP Address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
    printf("Netmask: %s\n", ip4addr_ntoa(netif_ip4_netmask(netif_default)));
    printf("Gateway: %s\n", ip4addr_ntoa(netif_ip4_gw(netif_default)));
    
    return 0; // Éxito
}