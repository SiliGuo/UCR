/*
 * CS120B_Lab07_part1.c
 *
 * Created: 2018/8/14 12:48:23
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned char tempB1 = 0;
unsigned char tempB2 = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;

	OCR1A = 125;
	TIMSK1 = 0x02;

	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {

	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum TLEDs {TL_Start,TL} state1;
enum BLEDs {BL_Start,BL} state2;

void TL_Tick(){
	
	switch(state1){
		case TL_Start:
			tempB1 = 0x01;
			state1 = TL;
			break;
		case TL:
			break;
		default:
			state1 = TL_Start;
			break;
	}
	
	switch(state1){
		case TL_Start:
			break;
		case TL:
			if(tempB1 == 0x01){tempB1 = 0x02;}
			else if (tempB1 == 0x02){tempB1 = 0x04;}
			else if (tempB1 == 0x04){tempB1 = 0x01;}
			else{tempB1 = 0x01;}
			break;
		default:
			break;
	}
			}
	
void BL_Tick(){
		
	switch(state2){
		case BL_Start:
			tempB2 = 0x00;
			state2 = BL;
			break;
		case BL:
			break;
		default:
			state2 = BL_Start;
			break;
	}
		
	switch(state2){
		case BL_Start:
			break;
		case BL:
			if (tempB2 == 0x00){tempB2 = 0x08;}
			else if(tempB2 == 0x08){tempB2 = 0x00;}
			break;
		default:
			break;
		}
	}
	
int main(void)
	{
		DDRB = 0xFF; PORTB = 0x00;
		
		TimerSet(1000);
		TimerOn();

		state1 = TL_Start;
		state2 = BL_Start;
		
		while(1) {
			TL_Tick();
			BL_Tick();
			PORTB = tempB1 | tempB2;
			while (!TimerFlag);
			TimerFlag = 0;
			
		}
		return 0;
	}