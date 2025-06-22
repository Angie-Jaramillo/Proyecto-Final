/**
 * @brief Actualiza el intervalo de pitido basado en el nivel actual.
 * 
 * @param level El nivel actual del test.
 * 
 * 
 */
void update_interval_for_level(int level) {

    test_state.speed_kmh = 8.5 + 0.5 * (level - 1);

    float speed_ms = test_state.speed_kmh * (1000.0 / 3600.0);
    
    // Calcula el intervalo en milisegundos basado en la distancia y la velocidad
    test_state.interval_ms = (uint64_t)((DISTANCE_M / speed_ms) * 1000);
    printf("Nivel %d: Velocidad = %.1f km/h, Intervalo = %llu ms\n", 
           level, test_state.speed_kmh, test_state.interval_ms);
}

// Temporizador para el pitido
int64_t alarm_callback(alarm_id_t id, void *user_data) {
    printf("¡Pitido! (Nivel %d)\n", test_state.level);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN)); // Toggle LED
    return test_state.interval_ms * 1000; // Convierte ms a µs para el próximo pitido
}

// Temporizador para cambiar de nivel cada minuto
int64_t level_up_callback(alarm_id_t id, void *user_data) {
    test_state.level++;
    update_interval_for_level(test_state.level);
    return 60 * 1000 * 1000; // 60 segundos en µs (para repetir cada minuto)
}


// EN EL MAIN

 if (cyw43_arch_init()) {
        printf("Error al iniciar WiFi\n");
        return -1;
    }
    
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0); // LED inicialmente apagado
    
    // Configura el primer nivel
    update_interval_for_level(test_state.level);
    
    // Inicia el temporizador de pitidos
    add_alarm_in_ms(test_state.interval_ms, alarm_callback, NULL, true);
    
    // Inicia el temporizador de cambio de nivel (cada 60 segundos)
    add_alarm_in_ms(60000, level_up_callback, NULL, true);
    
    printf("¡Comenzando Test de Léger!\n");
    printf("¡Pitido! (Nivel %d)\n", test_state.level);