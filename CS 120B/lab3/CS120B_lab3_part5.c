/*
 * CS120B_lab3_part5.c
 *
 * Created: 8/2/2018 2:21:14 PM
 * Author : GSL
 */ 

#include <avr/io.h>

enum States {Start, Wait, PressS, WaitS, Press0, Wait0, Press7, Wait7} state;
unsigned char sequence[3] = {0x04, 0x01, 0x02};
unsigned char cnt = 0;

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
			if (!A7 && tmpA == sequence[cnt]) {
				cnt++;
				state = PressS;
			} else if (A7) {
				state = Press7;
			} else {
				state = Wait;
			}
			break;
		case PressS: 
			if (tmpA != 0x00) {
				state = PressS;
			} else {
				state = WaitS;
			}
			break;
		case WaitS:
			if (tmpA == 0x00) {
				state = WaitS;
			} else if (tmpA == sequence[cnt]) {
				cnt++;
				state = PressS;
			} else if (cnt == 3 && tmpA == 0x01) {
				state = Press0;
			} else {
				state = Wait;
			}
			break;
		case Press0:
			state = Wait0;
			break;
		case Wait0:
			if (tmpA != 0x00) {
				state = Wait0;
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
			cnt = 0;
			break;
		case PressS:
			break;
		case WaitS:
			break;
		case Press0:
			tmpB = (tmpB == 0x00) ? 0x01 : 0x00;
			break;
		case Wait0:
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
