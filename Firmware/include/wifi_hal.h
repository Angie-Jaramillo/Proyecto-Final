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

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include <string.h>
#include <stdio.h>

#define RP 1         // <--- 0 para usar la raspberry 1, 1 para usar la raspberry 2

#define SSID "Raspberry"
#define PASSWORD "1001804091"
#define UDP_PORT 1234




/**
 * @brief Connects to a WiFi network with the specified SSID and password.
 * 

 * @param callback A callback function to be called with the connection state.
 * 
 * @return int Returns 0 on success, or a negative error code on failure.
 * 
 */
int dev_wifi_connect (udp_recv_fn udp_callback);


/**
 * @brief Gets the current IP address of the WiFi connection.
 * 
 * 
 */
void wifi_get_ip(void);




#endif // WIFI_HAL_H