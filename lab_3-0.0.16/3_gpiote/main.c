#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void init_led(){
    // turn off all leds
	for(int i = 17; i < 21; i++){
		GPIO->DIRSET = (1 << i);
        GPIO->PIN_CNF[i] = (3 << 2); 
        GPIO->OUT |= (1 << i);
	}
}

int main() {

    // config button as input
    GPIO->PIN_CNF[13] &= ~(1 << 0);
    // config button as pullup
    GPIO->PIN_CNF[13] = (3 << 2);

    init_led();
    config_gpiote();
    config_ppi();
    while (1){}
    
    return 0;
}