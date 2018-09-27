/*
 * CS120B_lab2_part1.c
 *
 * Created: 7/31/2018 4:34:32 PM
 * Author : GSL
 */ 

#include <avr/io.h>

// Bit-access function
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
    // Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	// Intermediate variable
	 unsigned char count = 0x00;
	 unsigned char tmpA = 0x00;
	 unsigned char tmpB = 0x00;
	 
    while (1) 
    {
		tmpA = PINA;
		tmpB = PINB;
		count = 0x00;
		for (char i = 0; i < 8; i++) {
			if (GetBit(tmpA, i) == 1) { count++; }
			if (GetBit(tmpB, i) == 1) { count++; }
		}
		PORTC = count;
    }
	return 0;
}

