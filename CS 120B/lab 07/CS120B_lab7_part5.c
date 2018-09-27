/*
 * CS120B_lab7_part5.c
 *
 * Created: 8/15/2018 12:55:56 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include "timer1.h"
#include "scheduler.h"

#define A0 (~PINA & 0x01)
#define A1 ((~PINA >> 1) & 0x01)

enum States {Start, Wait, Inc, IncFast, Dec, DecFast, Reset} state;

unsigned long TimePeriod = 5;
unsigned long elapsedTime = 5;
unsigned char tmpB = 0x00;
unsigned char cnt = 0;

void tick();

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(200);
	TimerOn();
	
	state = Start;
	
    while (1) 
    {
		if (elapsedTime >= TimePeriod) {
			tick();
			elapsedTime = 0;
		}
		while(!TimerFlag);
		TimerFlag = 0;
		
		elapsedTime++;
    }
}

void tick() {
	switch(state) { // Transitions
		case Start:
			tmpB = 0x00;
			state = Wait;
			break;
		case Wait:
			if (A0 && !A1) {
				state = Inc;
			} else if (!A0 && A1) {
				state = Dec;
			} else if (A0 && A1) {
				state = Reset;
			} else {
				state = Wait;
			}
			break;
		case Inc:
			if (!A0) {
				cnt = 0;
				state = Wait;
			} else if (A0 && !A1 && cnt < 3) {
				state = Inc;
			} else if (A0 && !A1 && !(cnt < 3)) {
				cnt = 0;
				state = IncFast;
			} else if (A0 && A1) {
				cnt = 0;
				state = Reset;
			}
			break;
		case IncFast:
			if (!A0) {
				TimePeriod = 5;
				state = Wait;
			} else if (A0 && !A1) {
				state = IncFast;
			} else if (A0 && A1) {
				TimePeriod = 5;
				state = Reset;
			}
			break;
		case Dec:
			if (!A1) {
				cnt = 0;
				state = Wait;
			} else if (!A0 && A1 && cnt < 3) {
				state = Dec;
			} else if (!A0 && A1 && !(cnt < 3)) {
				cnt = 0;
				state = DecFast;
			} else if (A0 && A1) {
				cnt = 0;
				state = Reset;
			}
			break;
		case DecFast:
			if (!A1) {
				TimePeriod = 5;
				state = Wait;
			} else if (!A0 && A1) {
				state = DecFast;
			} else if (A0 && A1) {
				TimePeriod = 5;
				state = Reset;
			}
			break;
		case Reset:
			state = Wait;
			break;
		default:
			state = Start;
	} // Transitions
	
	switch(state) { // Actions
		case Start:
			break;
		case Wait:
			break;
		case Inc:
			cnt++;
			tmpB += tmpB < 9 ? 1 : 0;
			if (cnt == 3) {
				TimePeriod = 2;
			}
			break;
		case IncFast:
			tmpB += tmpB < 9 ? 1: 0;
			break;
		case Dec:
			cnt++;
			tmpB -= tmpB > 0 ? 1 : 0;
			if (cnt == 3) {
				TimePeriod = 2;
			}
			break;
		case DecFast:
			tmpB -= tmpB > 0 ? 1 : 0;
			break;
		case Reset:
			tmpB = 0x00;
			break;
		default:
			break;
	} // Actions
	PORTB = tmpB;
}