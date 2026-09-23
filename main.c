#include "system_definitions.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "uart_driver.h"
#include "external_memory_driver.h"
#include "sram_test.h"
#include "adc_driver.h"

#define WAVE_PIN PB1
#define ERROR_LED PB0

volatile uint8_t *address = (volatile uint8_t *)0x1800;

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
    /*while(1) {
        address[1]=0;
        _delay_ms(1000);
        address_ADC[2]=1;
        _delay_ms(1000);

        for (int i=0; i<=10000; i++){
        address[i]=1+i;
        _delay_ms(1000);
       }
    }*/

    init_adc();
    while(1){
        address_ADC[0]=1;
        _delay_us(15);
        read_ADC(0);
        read_ADC(1);
        read_ADC(2);
        uint8_t digital_signal = read_ADC(3);
        int angle_x = master_conversion_x(digital_signal);

        printf("Angle x: %i\n", angle_x);

        _delay_ms(1000);
    }

    return 0;
}