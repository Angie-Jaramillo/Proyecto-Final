# Test de Léger Automatizado con Raspberry Pi Pico W
Este proyecto implementa un sistema embebido que automatiza el Test de Léger (también conocido como Beep Test) mediante dos microcontroladores Raspberry Pi Pico W, control de luces LED, comunicación por Wi-Fi usando el protocolo UDP y una interfaz móvil para iniciar o detener el test.

## Descripción General
El sistema está compuesto por dos unidades basadas en la Raspberry Pi Pico W, que actúan como receptores de comandos ("on" / "off") enviados por una app móvil o PC. Cada unidad genera señales luminosas sincronizadas con los pitidos característicos del test y ajusta el ritmo cada 60 segundos conforme a los niveles del test de Léger.

## Arquitectura del Sistema

### Flujo principal del sistema
<img width="395" height="395" alt="image" src="https://github.com/user-attachments/assets/d0118c2d-684f-48c5-9256-ac4c05e3a7e8" />

### Configuración del servidor UDP
<img width="395" height="395" alt="image" src="https://github.com/user-attachments/assets/f3a1701b-ee97-40e4-8a99-7e56cae9d170" />

### Alarmas
<img width="395" height="395" alt="image" src="https://github.com/user-attachments/assets/03d42fe6-34f2-4fba-a984-d68a52b12e48" />

### Diagrama de hardware

<img width="795" height="676" alt="image" src="https://github.com/user-attachments/assets/122dbc33-cdc3-474d-82e0-3e884ea7d97c" />


Conexión Wi-Fi: Cada Pico se conecta a una red Wi-Fi y se le asigna una IP estática.

- **Servidor UDP:** Se implementa un listener UDP que reacciona a los mensajes "on" (inicia test) y "off" (detiene test).

- **Control del Test:** Un sistema de temporizadores ajusta la velocidad de pitidos cada 60 segundos, y alterna LEDs para indicar el ritmo.

- **Lógica de control:** Cuando se detiene el test, se devuelve al cliente el último nivel alcanzado.

## Estructura del Código
- `main.c`: Inicializa la Raspberry Pi Pico W, configura la conexión Wi-Fi y entra en el bucle principal donde se mantienen los servicios de red.

- `lib.c / lib.h`: Contiene la lógica del test de Léger: control de nivel, velocidad, pitidos y respuesta a comandos UDP.

- `leds.c / leds.h`: Controla el encendido, alternancia y apagado de LEDs (representación visual del ritmo del test).

- `wifi_hal.c / wifi_hal.h`: Se encarga de la conexión a Wi-Fi, configuración de IP estática y del listener UDP.

## Comandos UDP disponibles
Comando	Acción
- "on"	Inicia el test, reinicia nivel, velocidad y temporizadores.
- "off"	Detiene el test y responde con el último nivel alcanzado.

## Requisitos de Hardware
2 × Raspberry Pi Pico W
2 × Tiras LED (2 colores: rojo y verde)
4 × Transistores (para controlar LEDs)
2 × Baterías LiPo recargables
2 × Baquelas perforadas
2 × Cajas impresas en 3D

Electrónica variada (resistencias, cables, pines macho/hembra, headers)

## Presupuesto Estimado

| Elemento                  | Cantidad | Precio unitario (COP) | Total (COP)   |
| ------------------------- | -------- | --------------------- | ------------- |
| Raspberry Pi Pico W       | 2        | \$44,625              | \$89,250      |
| Tiras LED bicolor         | 1        | \$45,000              | \$45,000      |
| Transistores (2N2222)     | 4        | \$100                 | \$400         |
| Baquelas perforadas       | 2        | \$1,300               | \$2,600       |
| Baterías LiPo 3S          | 2        | \$138,000             | \$276,000     |
| Caja plástica 15x9x5cm    | 2        | \$8,925               | \$17,850      |
| Electrónica variada       | 1 lote   | \$10,000              | \$10,000      |
| **Total estimado**        | —        | —                     | **\$441,100** |

> Nota: Los valores son aproximados y pueden variar según el proveedor.

## Instrucciones de uso
- Asegúrate de que ambas Raspberry Pi Pico W estén configuradas con la IP estática correcta.
- Conecta ambas a la misma red Wi-Fi (ej. hotspot del celular o router local).
- Usa una app móvil o software de red (como Python o Netcat) para enviar comandos UDP a la IP y puerto correspondiente (53).
- Observa el cambio en las luces LED indicando el ritmo del test.
- Detén el test con el comando "off" y recibe el nivel alcanzado.
