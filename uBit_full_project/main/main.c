#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/uart.h"
#include "sdkconfig.h"
#include "linenoise/linenoise.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "uart_tests.h"


void app_main(void) {
    init_uart(); // Configurar UART
   // uint8_t *input = (uint8_t *) malloc(RX_BUF_SIZE + 1);

    while (1) {
    	//read_uart_function(input);
    	uart_print_test(2,"\n chau \n");
        }
}
