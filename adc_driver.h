#ifndef ADC
#define ADC

#include <stdlib.h>
#include <avr/io.h>

extern volatile uint8_t *address_ADC;

void init_adc();

uint8_t read_ADC();

double voltage_conversion (uint8_t digital_signal);

int angle_conversion_x (double voltage);

double angle_conversion_y (double voltage);

int master_conversion_x (uint8_t digital_signal);

int master_conversion_y (uint8_t digital_signal);

#endif