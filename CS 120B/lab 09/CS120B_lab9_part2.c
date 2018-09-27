/*
 * CS120B_lab9_part2.c
 *
 * Created: 8/20/2018 12:44:13 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include "pwm.h"

#define A0 (~PINA & 0x01)
#define A1 ((~PINA >> 1) & 0x01)
#define A2 ((~PINA >> 2) & 0x01)

enum States {Start, Off, WaitOff, On, WaitOn, Up, Down} state;
double frequency[9] = {0, 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char cnt = 0;
unsigned char last_input = 0;

void tick();

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	
	PWM_on();
	
    while (1) 
    {
		tick();
    }
}

void tick() {
	switch(state) { // Transitions
		case Start:
			state = Off;
			break;
		case Off:
			state = A2 ? WaitOff : Off;
			break;
		case WaitOff:
			state = A2 ? WaitOff : On;
			break;
		case On:
			if (A2) {
				state = WaitOn;
			} else if (!A2 && A0 && !A1) {
				if (cnt < 8) { cnt++; }
				state = Up;
			} else if (!A2 && !A0 && A1) {
				if (cnt > 1) { cnt--; }
				state = Down;
			} else {
				state = On;
			}
			break;
		case WaitOn:
			state = A2 ? WaitOn : Off;
			break;
		case Up:
			state = A0 ? Up : On;
			break;
		case Down:
			state = A1 ? Down : On; 
			break;
		default:
			state = Start;
	} // Transitions
	
	switch(state) { // Actions
		case Start:
			break;
		case Off:
			cnt = 0;
			break;
		case WaitOff:
			cnt = 1;
			break;
		case On:
			break;
		case Up:
			break;
		case Down:
			break;
		default:
			break;
	} // Actions
	set_PWM(frequency[cnt]);
}