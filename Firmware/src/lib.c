/**
 * @brief Actualiza el intervalo de pitido basado en el nivel actual.
 *
 * @param level El nivel actual del test.
 *
 *
 */

#include "lib.h"

test_state_t test_state = {1, 8.5, 8470}; // Estado inicial del test
alarm_id_t alarm_id = 0;
alarm_id_t level_up_id = 0;

void update_interval_for_level(int level)
{

    test_state.speed_kmh = 8.5 + 0.5 * (level - 1);

    float speed_ms = test_state.speed_kmh * (1000.0 / 3600.0);

    // Calcula el intervalo en milisegundos basado en la distancia y la velocidad
    test_state.interval_ms = (uint64_t)((DISTANCE_M / speed_ms) * 1000);
    printf("Nivel %d: Velocidad = %.1f km/h, Intervalo = %llu ms\n",
           level, test_state.speed_kmh, test_state.interval_ms);
}

void udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    if (!p)
        return;
        
    char buffer[256] = {0};
    memcpy(buffer, p->payload, p->len);
    buffer[p->len] = '\0';

    printf("Mensaje UDP recibido: %s\n", buffer);
    printf("De: %s:%d\n", ipaddr_ntoa(addr), port);

    if (strcmp(buffer, "on") == 0)
    {
        start_test(); 
        struct pbuf *response = pbuf_alloc(PBUF_TRANSPORT, 20, PBUF_RAM);
    }
    else if (strcmp(buffer, "off") == 0)
    {
        char estado_buffer[3];
        sprintf(estado_buffer, "%d", test_state.level - 1);
        const char *estado = estado_buffer;

        stop_test();

        struct pbuf *response = pbuf_alloc(PBUF_TRANSPORT, strlen(estado), PBUF_RAM);
        strcpy((char *)response->payload, estado);
        udp_sendto(pcb, response, addr, port);
        pbuf_free(response);
        
    }


    pbuf_free(p); // liberar paquete recibido
}

// Temporizador para el pitido
int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    printf("¡Pitido! (Nivel %d)\n", test_state.level);

    toggle_leds(); // Alterna los LEDs entre rojo y verde

    return test_state.interval_ms * 1000; // Convierte ms a µs para el próximo pitido
}

// Temporizador para cambiar de nivel cada minuto
int64_t level_up_callback(alarm_id_t id, void *user_data)
{
    test_state.level++;
    update_interval_for_level(test_state.level);

    return 60 * 1000 * 1000; // 60 segundos en µs (para repetir cada minuto)
}

void start_test()
{
    if (alarm_id || level_up_id) {
        printf("El test ya está en ejecución. Deténlo primero.\n");
        return;
    }

    update_interval_for_level(test_state.level);

    // Inicia el temporizador de pitidos
    alarm_id = add_alarm_in_ms(test_state.interval_ms, alarm_callback, NULL, true);

    // Inicia el temporizador de cambio de nivel (cada 60 segundos)
    level_up_id = add_alarm_in_ms(60000, level_up_callback, NULL, true);

    init_leds(); // Inicializa los LEDs
    printf("¡Pitido! (Nivel %d)\n", test_state.level);
}


void stop_test()
{
    if(!alarm_id && !level_up_id) {
        printf("El test no está en ejecución.\n");
        return;
    }
    // Detiene el test y los temporizadores
    cancel_alarm(alarm_id);
    cancel_alarm(level_up_id);

    alarm_id = 0;
    level_up_id = 0;
    
    turn_off_leds(); // Apaga los LEDs al detener el test

    printf("Test detenido. Nivel alcanzado: %d, Velocidad: %.1f km/h\n",
           test_state.level -  1, test_state.speed_kmh - 0.5);

    test_state.level = 1; // Resetea el nivel al finalizar el test
    test_state.speed_kmh = 8.5; // Resetea la velocidad al
    test_state.interval_ms = 8470; // Resetea el intervalo al valor inicial
}

// EN EL MAIN
