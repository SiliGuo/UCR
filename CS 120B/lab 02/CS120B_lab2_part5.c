/*
 * CS120B_lab2_part5.c
 *
 * Created: 8/1/2018 4:18:24 AM
 * Author : GSL
 */ 

#include <avr/io.h>


int main(void)
{
    // Initialization
	DDRB = 0xFE; PORTB = 0x01;
	DDRD = 0x00; PORTD = 0xFF;
	
	// Intermediate variables
	unsigned short weight = 0x00;
	unsigned char tmpB = 0x00;
	
    while (1) 
    {
		weight = (PIND << 1) | (PINB & 0x01);
		tmpB = tmpB & 0xF9;
		
		if (weight >= 70) {
			tmpB = tmpB | 0x02;	
		} else if (weight > 5 && weight < 70) {
			tmpB = tmpB | 0x04;	
		}
		PORTB = tmpB;
    }
	return 0;
}

