#define F_CPU 4915200UL // The CPU clock speed in hz. this is 4.9152 MHz for us. Equal to the frequecy of the oscillator we use as a clock
#define BAUD 9600
#define UBRR 31

#define set_bit(reg,bit) (reg |= (1<<bit))
#define clear_bit(reg,bit) (reg &= ~(1<<bit))
#define set_bit(reg,bit) (reg & (1<<bit))