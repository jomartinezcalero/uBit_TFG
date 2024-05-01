#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/uart.h"
#include "sdkconfig.h"
#include "linenoise/linenoise.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UART_NUM UART_NUM_0 // Definimos el número de UART que utilizaremos (UART0 en este caso)
#define RX_BUF_SIZE 1024   // Tamaño del búfer de recepción

void init_uart(void) {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // Configuración de parámetros de UART
    uart_param_config(UART_NUM, &uart_config);

    // Configuración de pines de UART
    uart_set_pin(UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // Instalación del driver de UART
    uart_driver_install(UART_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

void uart_print_test(int num_input, char *frase) {
    // Asignar memoria para el buffer de entrada
    uint8_t *input = (uint8_t *) malloc(RX_BUF_SIZE + 1);
    if (input == NULL) {
        // Manejo de error: no se pudo asignar memoria
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }

    // Leer datos de la UART
    int len = uart_read_bytes(UART_NUM, input, RX_BUF_SIZE, 20 / pdMS_TO_TICKS(20)); // Espera 20 ms por datos
    if (len > 0) {
        // Agregar terminador nulo al final de los datos recibidos
        input[len] = '\0';

        // Verificar si el primer byte coincide con num_input
        if (input[0] == (uint8_t)(num_input + '0')) { // Convertir num_input a un carácter y luego comparar
            // Limpia la pantalla
            linenoiseClearScreen();
            // Imprime la frase
            printf("%s", frase);
        }
    }
    // Liberar la memoria asignada dinámicamente
    free(input);
}
