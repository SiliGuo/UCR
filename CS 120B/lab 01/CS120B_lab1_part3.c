/*
 * CS120B_lab1_part3.c
 *
 * Created: 7/30/2018 11:22:14 PM
 * Author : GSL
 */ 

#include <avr/io.h>


int main(void)
{
	// Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	// Temporary variable
	unsigned char tmpA = 0x00;
	unsigned char cntavail = 0x00;
	
	while (1)
	{
		// Read inputs
		tmpA = PINA & 0x0F;
		
		// Calculate for available spaces
		if (tmpA == 0x00) {
			cntavail = 4;
			} else if (tmpA == 0x01 || tmpA == 0x02 || tmpA == 0x04 || tmpA == 0x08) {
			cntavail = 3;
			} else if (tmpA == 0x0E || tmpA == 0x0D || tmpA == 0x0B || tmpA == 0x07) {
			cntavail = 1;
			} else if (tmpA == 0x0F) {
			cntavail = 128;
			} else {
			cntavail = 2;
		}
		// Write output
		PORTC = cntavail;
	}
	return 0;
}