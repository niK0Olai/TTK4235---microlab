#include "gpiote.h"

void config_gpiote() {
    // config button
    GPIOTE->CONFIG[4] |= (1 << 0);   // Config as event
    GPIOTE->CONFIG[4] |= (13 << 8);  // Config button 1, gpio 13 as pin
    GPIOTE->CONFIG[4] |= (2 << 16);  // event on falling edge, high to low

    // config leds
    for (int i=0; i<4; i++){
        GPIOTE->CONFIG[i] |= (3 << 0);   // Config as task
        GPIOTE->CONFIG[i] |= ((17+i) << 8);  // Config gpio led pin
        GPIOTE->CONFIG[i] |= (3 << 16);  // toggle gpio led pin
        GPIOTE->CONFIG[i] &= ~(1 << 20);  // turn on led on init    
    }
}