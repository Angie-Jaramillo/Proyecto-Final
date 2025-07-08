/**
 * @file wifi_hal.h
 * 
 * This header file contains the declaration of the WiFi Hardware Abstraction Layer (HAL).
 * It provides functions to initialize the WiFi hardware, connect to a network, and manage the connection state.
 * 
 * @author Angie Jaramillo
 * @date 21-06-2025
 * 
 * 
 */

#ifndef WIFI_HAL_H
#define WIFI_HAL_H


#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include <string.h>
#include <stdio.h>
#include "lwip/netif.h"


#define UDP_PORT 1234                   // UDP Port for communication
#define WIFI_SSID "ANGIE"               // Wifi SSID 
#define WIFI_PASSWORD "1001804091"      // Wifi Password

/**
 * @brief Initializes the WiFi hardware and prepares it for use.
 * 
 * @return int Returns 0 on success, or a negative error code on failure.
 * 
 */
int wifi_init(void);

/**
 * @brief Connects to a WiFi network with the specified SSID and password.
 * 
 * @param ssid The SSID of the WiFi network to connect to.
 * @param password The password for the WiFi network.
 * @param callback A callback function to be called with the connection state.
 * 
 * @return int Returns 0 on success, or a negative error code on failure.
 * 
 */
int wifi_connect(const char *ssid, const char *password, udp_recv_fn udp_callback); 



/**
 * @brief Sets a static IP address for the WiFi connection.
 * 
 * @param ip The static IP address to set (in string format).
 * @param netmask The netmask for the static IP address (in string format).
 * @param gateway The gateway for the static IP address (in string format).
 * 
 * @return int Returns 0 on success, or a negative error code on failure.
 * 
 */
int set_wifi_static_ip(const char *ip, const char *netmask, const char *gateway);

/**
 * @brief Gets the current IP address of the WiFi connection.
 * 
 * 
 */
void wifi_get_ip(void);




#endif // WIFI_HAL_H