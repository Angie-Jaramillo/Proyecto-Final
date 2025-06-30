/**
 * @brief Actualiza el intervalo de pitido basado en el nivel actual.
 * 
 * @param level El nivel actual del test.
 * 
 * 
 */

#include "lib.h"

test_state_t test_state = {1, 8.5, 8470};  // Estado inicial del test


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

    toggle_leds(); // Alterna los LEDs entre rojo y verde
    
    return test_state.interval_ms * 1000; // Convierte ms a µs para el próximo pitido
}

// Temporizador para cambiar de nivel cada minuto
int64_t level_up_callback(alarm_id_t id, void *user_data) {
    test_state.level++;
    update_interval_for_level(test_state.level);
     
    return 60 * 1000 * 1000; // 60 segundos en µs (para repetir cada minuto)
}

void start_test(){

    update_interval_for_level(test_state.level);
    
    // Inicia el temporizador de pitidos
    add_alarm_in_ms(test_state.interval_ms, alarm_callback, NULL, true);
    
    // Inicia el temporizador de cambio de nivel (cada 60 segundos)
    add_alarm_in_ms(60000, level_up_callback, NULL, true);

    init_leds(); // Inicializa los LEDs
    printf("¡Pitido! (Nivel %d)\n", test_state.level);

}

void calculate_results() {
    // Aquí puedes implementar la lógica para calcular los resultados del test de Léger
    // Por ejemplo, podrías calcular el tiempo total, la distancia recorrida, etc.

    turn_off_leds(); // Apaga los LEDs al finalizar el test
    
    printf("Resultados del test: Nivel %d, Velocidad %.1f km/h\n", 
           test_state.level, test_state.speed_kmh);
    
}

void reset_test() {
    // Resetea el estado del test a su configuración inicial
    test_state.level = 1;
    test_state.speed_kmh = 8.5;
    test_state.interval_ms = 8470; // Intervalo inicial en milisegundos

    printf("Test reseteado a nivel %d, velocidad %.1f km/h, intervalo %llu ms\n", 
           test_state.level, test_state.speed_kmh, test_state.interval_ms);
    
    start_test(); // Reinicia el test después de resetear
}




// EN EL MAIN
