/*
 * CS120B_lab3_part2.c
 *
 * Created: 8/2/2018 1:30:40 AM
 * Author : GSL
 */ 

#include <avr/io.h>

enum States {Start, Wait, Increment, WaitInc, Decrement, WaitDec, Reset, WaitRes} state;

void Tick() {
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = (PINA >> 1) & 0x01;
	unsigned char tmpC = PORTC;
	
	switch(state) { // Transitions
		case Start:
			tmpC = 0x07;
			state = Wait;
			break;
		case Wait:
			if (!A0 && !A1) {
				state = Wait;
			} else if (A0 && !A1){
				state = Increment;
			} else if (!A0 && A1) {
				state = Decrement;
			} else {
				state = Reset;
			}
			break;
		case Increment:
			state = WaitInc;
			break;
		case WaitInc:
			state = A0 ? WaitInc : Wait;
			break;
		case Decrement:
			state = WaitDec;
			break;
		case WaitDec:
			state = A1 ? WaitDec : Wait;
			break;
		case Reset:
			state = WaitRes;
			break;
		case WaitRes:
			state = (A0 || A1) ? WaitRes : Wait;
			break;
		default:
			state = Start;
	} // Transitions
	
	switch(state) { // Actions
		case Start:
			break;
		case Wait:
			break;
		case Increment:
			tmpC = (tmpC < 9) ? (tmpC + 1) : tmpC;
			break;
		case WaitInc:
			break;
		case Decrement:
			tmpC = (tmpC > 0) ? (tmpC - 1) : tmpC;
			break;
		case WaitDec:
			break;
		case Reset:
			tmpC = 0;
			break;
		case WaitRes:
			break;
		default:
			break;
	} // Actions
	PORTC = tmpC;
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	state = Start;
	 
    while (1) 
    {
		Tick();
    }
	return 0;
}

