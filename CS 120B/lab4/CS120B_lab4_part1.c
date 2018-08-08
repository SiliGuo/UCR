/*
 * CS120B_lab4_part1.c
 *
 * Created: 8/6/2018 1:00:09 PM
 * Author : GSL
 */ 

#include <avr/io.h>


int main(void)
{
	// Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	// Intermediate variable
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	
	while (1)
	{
		tmpA = ~PINA & 0x0F;
		tmpC = tmpC & 0x80;
		if (tmpA > 0) { tmpC = tmpC | 0x20; }
		if (tmpA > 2) { tmpC = tmpC | 0x10; }
		if (tmpA > 4) { tmpC = tmpC | 0x08; }
		if (tmpA > 6) { tmpC = tmpC | 0x04; }
		if (tmpA > 9) { tmpC = tmpC | 0x02; }
		if (tmpA > 12) { tmpC = tmpC | 0x01; }
		if (tmpA <= 4) { tmpC = tmpC | 0x40; }
		PORTC = tmpC;
		
		//PORTC = PINA;
	}
	return 0;
}
