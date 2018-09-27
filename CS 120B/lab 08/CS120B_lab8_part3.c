/*
 * CS120_lab8_part3.c
 *
 * Created: 8/16/2018 12:58:14 PM
 * Author : GSL
 */ 

#include <avr/io.h>
//#include "timer1.h"

#define MAX 768

unsigned short x = 0;
unsigned char LED = 0;




int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
		ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	
	
//	TimerSet(200);
//	TimerOn();
	
	while (1)
	{
		x = ADC;
		if (x >= MAX / 2) {
			LED = 0x00;
		} else{
			LED = 0x01;
		}
		
		PORTB = LED;
//		while(!TimerFlag);
//		TimerFlag = 0;
	}
}