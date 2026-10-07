#include <stdlib.h>
#include <avr/io.h>


#include "io_interface_driver.h"
#include "spi_driver.h"


uint8_t io_write(uint8_t command) {
    return spi_write_byte(command, SPI_SLAVE_IO);
}

Buttons io_read_buttons(void) {
    Buttons btn_state = {0}; 

    io_write(0x04);

    _delay_us(40);
    btn_state.right = io_write(0x00);
    
    _delay_us(5);
    btn_state.left = io_write(0x00);
    
    _delay_us(5);
    btn_state.nav = io_write(0x00);

    return btn_state;
}

Joystick io_read_joystick(void) {
    Joystick joystick_state = {0}; 

    io_write(0x03);

    _delay_us(40);
    joystick_state.x = io_write(0x00);
    
    _delay_us(5);
    joystick_state.y = io_write(0x00);
    
    _delay_us(5);
    joystick_state.btn = io_write(0x00);

    return joystick_state;
}

TouchPad io_read_touchpad(void) {
    TouchPad pad_state = {0}; 

    io_write(0x01);

    _delay_us(40);
    pad_state.x = io_write(0x00);
    
    _delay_us(5);
    pad_state.y = io_write(0x00);
    
    _delay_us(5);
    pad_state.size = io_write(0x00);

    return pad_state;
}

TouchSlider io_read_slider(void) {
    TouchSlider slider_state = {0}; 

    io_write(0x02);

    _delay_us(40);
    slider_state.x = io_write(0x00);
    
    _delay_us(5);
    slider_state.size = io_write(0x00);

    return slider_state;
}