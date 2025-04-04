#include "uart.h"
#include "gpio.h"
#include <stdio.h>
#include <sys/types.h> 

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
    GPIO->PIN_CNF[15] = (3 << 2);

	
    // turn off all leds
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
        GPIO->OUT |= (1 << i);
	}

}

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }
    return count;
}

int main(){

    button_init();
    uart_init();
    int sleep = 0;
    int led_toggle = 0;
    while(1){
        /* Check if button 1 is pressed;
        * turn on LED matrix if it is. */
        if(!(GPIO->IN & (1 << 13))) {
            GPIO->OUT &= ~(1 << 17);
            uart_send('A');
            GPIO->OUT |= (1 << 17);
        }

        /* Check if button 2 is pressed;
        * turn off LED matrix if it is. */
        if(!(GPIO->IN & (1 << 14))) {
            GPIO->OUT &= ~(1 << 18);
            uart_send('B');
            GPIO->OUT |= (1 << 18);

        }

        if(!(GPIO->IN & (1 << 15))) {
            iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235,2022,'B');
        }

        if (uart_read() != '\0'){
            led_toggle = !led_toggle;
            if (led_toggle){

                GPIO->OUT |= (1 << 19);
                GPIO->OUT |= (1 << 20);
            } else {
                GPIO->OUT &= ~(1 << 19);
                GPIO->OUT &= ~(1 << 20);
            }
        }

        sleep = 10000;
        while(--sleep); // Delay
    }
}