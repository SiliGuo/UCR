/*
 * CS120B_lab3_part3.c
 *
 * Created: 8/2/2018 1:06:11 PM
 * Author : GSL
 */ 

#include <avr/io.h>

enum States {Start, Wait, Press2, Wait2, Press1, Wait1, Press7, Wait7} state;

void Tick() {
//	unsigned char A0 = PINA & 0x01;
//	unsigned char A1 = (PINA >> 1) & 0x01;
//	unsigned char A2 = (PINA >> 2) & 0x01;
	unsigned char tmpA = PINA & 0x07;
	unsigned char A7 = (PINA >> 7) & 0x01;
	unsigned char tmpB = PORTB;
	
	switch(state) { // Transitions
		case Start:
			tmpB = 0x00;
			state = Wait;
			break;
		case Wait:
			if (!A7 && tmpA == 0x04) {
				state = Press2;
			} else if (A7) {
				state = Press7;
			} else {
				state = Wait;
			}
			break;
		case Press2:
			if (tmpA != 0x00) {
				state = Press2;
			} else {
				state = Wait2;
			}
			break;
		case Wait2:
			if (tmpA == 0x00) {
				state = Wait2;
			} else if (tmpA == 0x02) {
				state = Press1;
			} else {
				state = Wait;
			}
			break;
		case Press1:
			state = Wait1;
			break;
		case Wait1:
			if (tmpA != 0x00) {
				state = Wait1;
			} else {
				state = Wait;
			}
			break;
		case Press7:
			state = Wait7;
			break;
		case Wait7:
			if (A7) {
				state = Wait7;
			} else {
				state = Wait;
			}
			break;
		default:
			state = Start;
	} // Transitions
	
	switch(state) { // Actions
		case Start:
			break;
		case Wait:
			break;
		case Press2:
			break;
		case Wait2:
			break;
		case Press1:
			tmpB = 0x01;
			break;
		case Wait1:
			break;
		case Press7:
			tmpB = 0x00;
			break;
		case Wait7:
			break;
		default:
			break;
	} // Actions
	PORTB = tmpB;
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	
    while (1) 
    {
		Tick();
    }
}

