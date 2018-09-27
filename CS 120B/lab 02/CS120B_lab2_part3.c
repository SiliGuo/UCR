/*
 * CS120B_lab2_part3.c
 *
 * Created: 7/31/2018 5:25:02 PM
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
	DDRC = 0xFF; PORTC = 0x00;
	
	// Intermediate variable
	unsigned char tmpA1 = 0x00;
	unsigned char tmpA2 = 0x00;
	unsigned char tmpC = 0x00;
	
	while (1)
	{
		tmpA1 = PINA & 0x0F;
		tmpA2 = PINA & 0x70;
		tmpC = tmpC & 0x00;
		if (tmpA1 > 0) { tmpC = tmpC | 0x20; }
		if (tmpA1 > 2) { tmpC = tmpC | 0x10; }
		if (tmpA1 > 4) { tmpC = tmpC | 0x08; }
		if (tmpA1 > 6) { tmpC = tmpC | 0x04; }
		if (tmpA1 > 9) { tmpC = tmpC | 0x02; }
		if (tmpA1 > 12) { tmpC = tmpC | 0x01; }
		if (tmpA1 <= 4) { tmpC = tmpC | 0x40; }
		if (GetBit(tmpA2, 4) & GetBit(tmpA2, 5) & !GetBit(tmpA2, 6)) { tmpC = tmpC | 0x80; }
		PORTC = tmpC;
	}
	return 0;
}