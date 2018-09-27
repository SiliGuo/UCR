/*
 * CS120B_lab8_part4.c
 *
 * Created: 8/16/2018 1:36:57 PM
 * Author : GSL
 */ 

#include <avr/io.h>

#define LEVEL 96

unsigned short x = 0;
unsigned char LED = 0;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
	
	while (1)
	{
		x = ADC;
		LED = 0xFF;
		if (x >= LEVEL) { LED &= 0x7F; } 
		if (x >= 2 * LEVEL) { LED &= 0xBF; }
		if (x >= 3 * LEVEL) { LED &= 0xDF; }
		if (x >= 4 * LEVEL) { LED &= 0xEF; }
		if (x >= 5 * LEVEL) { LED &= 0xF7; }
		if (x >= 6 * LEVEL) { LED &= 0xFB; }
		if (x >= 7 * LEVEL) { LED &= 0xFD; }
		if (x >= 8 * LEVEL) { LED &= 0xFE; }
		
		PORTB = LED;
	}
}