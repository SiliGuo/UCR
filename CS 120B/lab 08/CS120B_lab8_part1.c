/*
 * CS120B_lab8_part1.c
 *
 * Created: 8/16/2018 12:41:08 PM
 * Author : GSL
 */ 

#include <avr/io.h>

unsigned short x = 0;
unsigned char tmpB = 0;
unsigned char tmpD = 0;

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
		x = ~ADC;
		tmpB = (char) x;
		tmpD = (char) (x >> 8);
		
		PORTB = tmpB;
		PORTD = tmpD;
	}
}
