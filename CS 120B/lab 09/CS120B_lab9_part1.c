/*
 * CS120B_lab9_part1.c
 *
 * Created: 8/18/2018 8:12:32 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include "pwm.h"

#define A0 (~PINA & 0x01)
#define A1 ((~PINA >> 1) & 0x01)
#define A2 ((~PINA >> 2) & 0x01)

enum States {Start, Wait, Sound} state;
double frequency = 0;

void tick() {
	switch(state) { // Transitions
		case Start:
			frequency = 0;
			state = Wait;
			break;
		case Wait:
			if ((A0 && !A1 && !A2) || (!A0 && A1 && !A2) || (!A0 && !A1 && A2)){
				state = Sound;
			} else {
				state = Wait;
			}
			break;
		case Sound:
			if ((A0 && !A1 && !A2) || (!A0 && A1 && !A2) || (!A0 && !A1 && A2)){
				state = Sound;
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
			frequency = 0;
			break;
		case Sound:
			if (A0 && !A1 && !A2) {
				frequency = 261.63;
			} else if (!A0 && A1 && !A2) {
				frequency = 293.66;
			} else if (!A0 && !A1 && A2) {
				frequency = 329.63;
			} else {
				frequency = 0;
			}
			break;
		default:
			break;
	} // Actions
	set_PWM(frequency);
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x4F; PORTB = 0xB0;
	
	state = Start;
	PWM_on();
	set_PWM(0);
	
    while (1) 
    {
		tick();
    }
}
