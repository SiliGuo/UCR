/*
 * CS120B_lab1_part1.c
 *
 * Created: 7/30/2018 2:39:22 PM
 * Author : GSL
 */ 

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // COnfigure port B's 8 pins as outputs
	
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	
    while (1) 
    {
		// Read input
		tmpA = PINA & 0x03;
		
		// Test for output
		// If PA1PA0 is 01, PB0=1, else=0
		if (tmpA == 0x01) {
			tmpB = (tmpB & 0xFE) | 0x01; // Set tmpB to bbbbbbb1
		}
		else {
			tmpB = (tmpB & 0xFE) | 0x00; // Set tmpB to bbbbbbb0
		}
		
		// Write output
		PORTB = tmpB;
	}
	return 0;
}

