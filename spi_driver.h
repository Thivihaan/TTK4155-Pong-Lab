#ifndef SPI
#define SPI

#include <stdlib.h>
#include <avr/io.h>

#define SPI_SS1 PB4
#define SPI_SS2 PB3
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK PB7

void SPI_init(void);

uint8_t SPI_Transfer(uint8_t byte);

uint8_t read_byte(uint8_t pin);

void write_byte(uint8_t byte, uint8_t pin);

void select_slave(uint8_t pin);

void unselect_slave(uint8_t);


#endif