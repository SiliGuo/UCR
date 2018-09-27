/*
 * CS120B_lab2_part4.c
 *
 * Created: 7/31/2018 5:49:57 PM
 * Author : GSL
 */ 

#include <avr/io.h>


int main(void)
{
    // Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	// Intermediate variables
	unsigned char tmpA1 = 0x00;
	unsigned char tmpA2 = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	
    while (1) 
    {
		tmpA1 = PINA >> 4;
		tmpA2 = PINA & 0x0F;
		
		tmpB = (tmpB & 0xF0) | tmpA1;
		tmpC = (tmpC & 0x0F) | (tmpA2 << 4);
		
		PORTB = tmpB;
		PORTC = tmpC;
    }
	return 0;
}

