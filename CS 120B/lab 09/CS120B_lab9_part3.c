/*
 * CS120B_lab9_part3.c
 *
 * Created: 8/20/2018 1:56:29 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include "pwm.h"
#include "timer1.h"

#define A0 (~PINA & 0x01)

enum States {Start, Off, Press, On} state;
//double unity[7] = {0, 293.66, 261.63, 440.00, 392.00, 440.00, 329.63};
double frequency[9] = {0, 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char down[18] = {0, 3, 3, 0, 0, 3, 4, 5, 0, 0, 3, 4, 5, 0, 0, 4, 3, 4};
unsigned char cnt = 0;

void tick();

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	TimerSet(200);
	TimerOn();
	PWM_on();
	
    while (1) 
    {
		tick();
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

void tick() {
	switch(state) { // Transition
		case Start:
			cnt = 0;
			state = Off;
			break;
		case Off:
			state = A0 ? Press : Off;
			break;
		case Press:
			if (cnt < 17) {
				state = Press;
			} else if (!(cnt < 17) && A0) {
				state = On;
			} else {
				state = Off;
			}
			break;
		case On:
			state = A0 ? On : Off;
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
		case Press:
			cnt += cnt < 17 ? 1 : 0;
			break;
		case On:
			cnt = 0;
			break;
		default:
			break;
	} // Actions
	set_PWM(frequency[down[cnt]]);
}