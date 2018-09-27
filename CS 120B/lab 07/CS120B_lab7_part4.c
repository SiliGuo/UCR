/*
 * CS120B_Lab07_part4.c
 *
 * Created: 2018/8/15 1:04:19
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned char tempB1 = 0;
unsigned char tempB2 = 0;
unsigned char tempB3 = 0;
unsigned short freq = 0; 

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

enum BLEDs {BL_Start,BL} state2;

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

enum Speaker {SP_Start,WaitA2,ON} state3;

void SP_Tick(){
	
	unsigned char A2 = ~PINA & 0x04;
	
	switch(state3){
		
		case SP_Start:
			state3 = WaitA2;
			break;
		case  WaitA2:
			state3 = A2? ON : WaitA2;
			break;
		case ON:
			state3 = A2? ON : WaitA2;
			break;
		default:
			state3 = SP_Start;
			break;
	}
	
	switch(state3){
		
		case SP_Start:
			break;
		case WaitA2:
			tempB3 = 0;
			break;
		case ON:
			if (tempB3 == 0){tempB3 = 0x10;}
			else if (tempB3 == 0x10){tempB3 = 0;}
			break;
	}
	
}

enum Frequency {FR_Start,WaitA0A1,incre,WaitNotA0,decre,WaitNotA1} state4;
	
void FR_Tick(){
	
	unsigned char A0 = ~PINA & 0x01;
	unsigned char A1 = ~PINA & 0x02;
	
	switch(state4){
		
		case  FR_Start:
			state4 = WaitA0A1;
			break;
		case  WaitA0A1:
			if (A0 && !A1){state4 = incre;}
			else if (!A0 && A1){state4 = decre;}
			else{state4 = WaitA0A1;}
			break;
		case incre:
			state4 = WaitNotA0;
			//state4 = A0? incre : WaitA0A1;
			break;
		case WaitNotA0:
			state4 = A0? WaitNotA0 : WaitA0A1;
			break;
		case decre:
			state4 = WaitNotA1;
			//state4 = A1? decre : WaitA0A1;
			break;
		case WaitNotA1:
			state4 = A1? WaitNotA1 : WaitA0A1;
			break;
		default:
			state4 = FR_Start;
			break;
	}
	
	switch(state4){
		
		case FR_Start:
			break;
		case  WaitA0A1:
			break;
		case incre:
			freq++;
			break;
		case WaitNotA0:
			break; 
		case decre:
			if (freq > 0){freq--;}
			break;
		case WaitNotA1:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned long TL_elapsedTime = 300;
	unsigned long BL_elapsedTime = 1000;
	unsigned long SP_elapsedTime = freq;
	const unsigned long timerPeriod = 1;
	
	TimerSet(timerPeriod);
	TimerOn();

	state1 = TL_Start;
	state2 = BL_Start;
	state3 = SP_Start;
	state4 = FR_Start;
	
	while(1) {
		
		FR_Tick();
		
		if (TL_elapsedTime >= 300)
		{
			TL_Tick();
			TL_elapsedTime = 0;
		}
		if(BL_elapsedTime >= 1000)
		{
			BL_Tick();
			BL_elapsedTime = 0;
		}
		if(SP_elapsedTime >= freq)
		{
			SP_Tick();
			SP_elapsedTime = 0;
		}

		PORTB = tempB1 | tempB2 | tempB3;
		while (!TimerFlag);
		TimerFlag = 0;
		
		TL_elapsedTime += timerPeriod;
		BL_elapsedTime += timerPeriod;
		SP_elapsedTime += timerPeriod;
		
	}
	return 0;
}
