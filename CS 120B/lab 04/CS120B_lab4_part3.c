/*
 * CS120B_lab4_part3.c
 *
 * Created: 8/6/2018 5:11:18 PM
 * Author : GSL
 */ 

#include <avr/io.h>

#define A0 ~PINA & 0x01
enum States {Start, Off, Press, On} state;
unsigned char tmpC = 0x00;
unsigned char cnt = 0x00;

void Tick() {
	tmpC = PORTC;
	
	switch(state) { // Transition
		case Start:
			tmpC = 0x00;
			state = Off;
			break;
		case Off:
			if (A0) {
				cnt = (cnt < 4) ? cnt + 1 : 1;
				state = Press;
			} else {
				state = Off;
			}
			break;
		case Press:
			state = A0 ? Press : On;
			break;
		case On:
			if (A0) {
				cnt = (cnt < 4) ? cnt + 1 : 1;
				state = Press;
			} else {
				state = On;
			}
			break;
		default:
			state = Start;
	} // Transition
	
	switch(state) { // Actions
		case Start:
			break;
		case Off:
			cnt = 0;
			break;
		case Press:
			if (cnt == 1) {
				tmpC = 0x0C;
			} else if (cnt == 2) {
				tmpC = 0x12;
			} else if (cnt == 3) {
				tmpC = 0x21;
			} else if (cnt == 4) {
				tmpC = 0x12;
			}
			break;
		case On:
			break;
		default:
			break;
	} // Actions
	PORTC = tmpC;
}

int main(void)
{
    //Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	state = Start;
	
    while (1) 
    {
		Tick();	
    }
}

