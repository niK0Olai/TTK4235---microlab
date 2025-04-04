#include <stdint.h>

#include "uart.h"
#include "gpio.h"

void uart_init(){
    // Set GPIO pins, p. 535
    GPIO->PIN_CNF[5] = 1;  // rts output
    GPIO->PIN_CNF[6] = 1;  // txd output
    GPIO->PIN_CNF[7] = 0;  // cts input
    GPIO->PIN_CNF[8] = 0;  // rxd input

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->BAUDRATE = 0x00275000;

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->CONFIG = 0;
    UART->ENABLE = 4;

}
void uart_send(char letter){
    UART->TASKS_STARTTX = 1;

    UART->TXD = letter;
    while (!UART->EVENTS_TXDRDY){}
    
    UART->TASKS_STOPTX = 1;
    UART->EVENTS_TXDRDY = 0;

}
char uart_read(){
    UART->TASKS_STARTRX = 1;
    if (UART->EVENTS_RXDRDY){
        UART->EVENTS_RXDRDY = 0;
        return UART->RXD;
    } else {
        return '\0';
    }
    
}