#include "adc_driver.h"
#include <stdlib.h>
#include <stdio.h>

volatile uint8_t *address_ADC = (volatile uint8_t *)0x1000;


//Initializig ADC
void init_adc(){
    //Sets PD5 as ouput
    DDRD |= (1<<DDD5);

    //Toggles OC1A to compare match
    TCCR1A |= (1<<COM1A0);

    //No prescaler and sets timer1 in CTC mode
    TCCR1B |= (1<<WGM12) | (1<<CS10);
}

//Reads ADC value
uint8_t read_ADC(int adress){
    volatile uint8_t retreived_value = address_ADC[adress];
    //printf("Adress value of adress, %d, equals to: %02X\n", adress, retreived_value);

    return retreived_value;
}

//Converts digital value to voltage
double voltage_conversion (uint8_t digital_signal){

    double voltage = ((double)digital_signal/256)*5;
    //int test = ((int)digital_signal/256)*5*1000;
    //printf("DV x: %d\n", digital_signal);
    //printf("Voltage x: %i\n", test);
    return voltage;

}

//Converts voltage to angle x in percentage
int angle_conversion_x (double voltage){

    double angle_x = (voltage-2.56)/0.015175;
    int angle_x_int = (int)angle_x;
    return angle_x_int;
}

//Converts voltage to angle y in percentage
double angle_conversion_y (double voltage){

    double angle_y = (voltage-2.5)/ 0.01495;
    return angle_y;
}


int master_conversion_x (uint8_t digital_signal){

    double voltage_x = voltage_conversion(digital_signal);
    int angle_x = (angle_conversion_x(voltage_x)-43);

    return angle_x;
}


int master_conversion_y (uint8_t digital_signal){

    double voltage_y = voltage_conversion(digital_signal);
    int angle_y = angle_conversion_y(voltage_y);

    return angle_y;
}
