#include "system_definitions.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "uart_driver.h"
#include "external_memory_driver.h"
#include "sram_test.h"

#define WAVE_PIN PB1
#define ERROR_LED PB0

volatile uint8_t *address = (volatile uint8_t *)0x1800;
volatile uint8_t *address_ADC = (volatile uint8_t *)0x1000;

static FILE uartstdout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

int main(void) {    
    set_bit(DDRB, ERROR_LED);
    /*
    set_bit(DDRB, WAVE_PIN);


    //Day 1 initial test
    while(1) {
        set_bit(PORTB, WAVE_PIN);
        _delay_ms(500);
        clear_bit(PORTB, WAVE_PIN);
        _delay_ms(500);
    }*/
    uart_init();
    stdout = stdin = &uartstdout; // Replace the defualt stdout/in stream with the custom uart one


    //Day 1 test
    /*while(1) { 
        

        //char c[32] = getchar(); // Waits until it gets a character on the stdin stream
        char c[32];
        fgets(c, sizeof(c), stdin);
        printf("Hello, PC! You've sent me this: %s\n", c); 
    }
        */

        
    external_memory_init();
    //SRAM_test(); //Day 2 SRAM test

    //Day 2 final test
    while(1) {
        //address[1]=0;
        //_delay_ms(1000);
        //address_ADC[2]=1;
        //nal_delay_ms(1000);

        //for (int i=0; i<=10000; i++){
        //address[i]=1+i;
        //_delay_ms(1000);
       //}
    }



    

    return 0;
}