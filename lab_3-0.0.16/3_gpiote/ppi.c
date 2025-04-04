#include "ppi.h"
#include "gpiote.h"

void config_ppi(){
    for (int i=0; i<4; i++){
        PPI->CHEN |= (1 << i);  // enable ppi channel i
        PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[4]);  // button event
        PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[i]);  // led i task
    }
}