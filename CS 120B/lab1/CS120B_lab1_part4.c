/*
 * CS120B_lab1_part4.c
 *
 * Created: 7/30/2018 11:32:41 PM
 * Author : GSL
 */ 

#include <avr/io.h>


int main(void)
{
	// Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0X00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	// Temporary variable
	unsigned short sum = 0x00;
	short sub = 0x00;
	unsigned tmpD = 0x00;
	
	while (1)
	{
		// Read inputs
		sum = PINA + PINB + PINC;
		sub = PINA - PINC;
		
		// Set PD1PD0
		tmpD = tmpD & 0x00;
		if (sum > 140) {
			tmpD = tmpD | 0x01;
		}
		if (sub >= 80 || sub <= -80) {
			tmpD = tmpD | 0x02;
		}
		
		// Save number in range of 128
		for (char i = 1; i <= 6; i++) {
			if (sum > (i-1) * 128) {
				tmpD = tmpD | (0x02 << i);
			}
			else {
				break;
			}
		}
		
		// Write output
		PORTD = tmpD;
	}
	return 0;
}