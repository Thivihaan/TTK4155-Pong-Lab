#include "external_memory_driver.h" 

void external_memory_init(){

    MCUCR |= (1<<SRE);

}