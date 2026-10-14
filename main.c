#include "system_definitions.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "uart_driver.h"
#include "external_memory_driver.h"
#include "sram_test.h"
#include "adc_driver.h"
#include "spi_driver.h"
#include "oled_driver.h"
#include "io_interface_driver.h"
#include "menu.h"
#include "interrupts.h"
#include "can_driver.h"
#include "MCP2515_driver.h"

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
    //Day 3 test 
    /*while(1){
        address_ADC[0]=1;
        _delay_us(15);
        uint8_t digital_signal_slider_x =read_ADC(0);
        uint8_t digital_signal_slider_y =read_ADC(1);
        uint8_t digital_signal_y =read_ADC(2);
        uint8_t digital_signal_x = read_ADC(3);

        int pos_x = master_conversion_x(digital_signal_x);
        int pos_y = master_conversion_y(digital_signal_y);
        int pos_slider_x = voltage_conversion_slider(digital_signal_slider_x);
        int pos_slider_y  = voltage_conversion_slider(digital_signal_slider_y);

        direction joystick = joystick_position(pos_x, pos_y);

        printf("x: %i\n", pos_x);
        printf("y: %i\n", pos_y);
        printf( " direction : %d\n", joystick);

        //printf("x slider: %i\n", pos_slider_x);
        //printf("y slider: %i\n", pos_slider_y);

        _delay_ms(1000);
    }*/ 
    SPI_init();
    oled_init();

    /*io_set_led(0, 1);
    io_set_led(1, 1);
    io_set_led(2, 1);
    io_set_led(3, 1);
    io_set_led(4, 1);
    io_set_led(5, 1);

    while (1)
    {
         Buttons btns = io_read_buttons();
        printf("Bouton up : %d\n", btns.L2);
        _delay_ms(500);
    }*/
    
   
    //oled_run_simple_menu();
    /*while (1)
    {
        io_update_led_from_buttons();
        _delay_ms(150);
    }*/
    CAN_init();
    init_interruptions();

    // 1. Écrire une valeur de test (ex: 0xAA ou 10101010) dans CNF1
    MCP_write(REG_CNF1, 0xAA); 

    // 2. Relire ce même registre
    uint8_t test_spi = MCP_read(REG_CNF1);

    // 3. Vérifier la lecture
    if (test_spi == 0xAA) {
        // Le SPI fonctionne ! MISO, MOSI, SCK et CS communiquent bien.
        PORTB |= (1 << PB1); // Allumer une LED pour confirmer
    } else {
        // Le SPI est défaillant. La valeur lue est probablement 0x00 ou 0xFF.
    }

    DDRB |= (1 << PB1);
    PORTB &= ~(1 << PB1);   // LED éteinte au départ


    // 2. Préparation du message test
    Can_message msg_tx;
    msg_tx.id = 0x001;
    msg_tx.length = 2;
    msg_tx.data[0] = 0xAA; // 10101010 en binaire
    msg_tx.data[1] = 0x55; // 01010101 en binaire

    // 3. Envoi du message
    while(1) {
        CAN_send_message(msg_tx);
    }

    Can_message msg_rx;

    _delay_ms(20);

    CAN_receive_message(&msg_rx);

    if (msg_rx.id == 0x001) {
        PORTB |= (1 << PB1);
        printf("success") ;
    }else{
        printf("rate") ;
    }

    // 4. Boucle principale
    /*while(1) {
        // On attend que l'interruption lève le drapeau
        if (flag_can_message == 1) {
            flag_can_message= 0; // On baisse le drapeau
            
            // On récupère le message
            CAN_receive_message(&msg_rx);
            
            // 5. Vérification
            if (msg_rx.id == 0x123 && msg_rx.length == 2 && msg_rx.data[0] == 0xAA) {
                PORTB |= (1 << PB1);
                printf("success") ;
            }else{
                printf("rate") ;
            }
        }
    }*/

    return 0;
}