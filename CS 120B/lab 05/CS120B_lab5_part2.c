/*
 * CS120B_lab5_part2.c
 *
 * Created: 8/7/2018 5:57:42 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define A0 (~PINA & 0x01)

enum States {Start, Blink, Stay} state;
unsigned char tmpC = 0x00;
unsigned char last_input = 0x00;

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void Tick() {
	tmpC = PORTC;
	tmpC = tmpC & 0x07;
	switch(state) { // Transitions
		case Start:
			state = Blink;
			break;
		case Blink:
			if ((A0 != last_input) && A0) {
				last_input = 1;
				state = Stay;
			} else {
				state = Blink;
			}
			break;
		case Stay:
			if ((A0 != last_input) && A0) {
				last_input = 1;
				state = Blink;
			} else {
				state = Stay;
			}
			break;
		default:
			state = Start;
	} // Transitions
	switch(state) { // Actions
		case Start:
			break;
		case Blink:
			if (tmpC == 0x00) {
				tmpC = 0x01;
			} else if (tmpC == 0x01) {
				tmpC = 0x02;
			} else if (tmpC == 0x02) {
				tmpC = 0x04;
			} else if (tmpC == 0x04) {
				tmpC = 0x01;
			}
			if (!A0 && (last_input == 1)) {
				last_input = 0;
			}
			break;
		case Stay:
			if (!A0 && (last_input == 1)) {
				last_input = 0;
			}
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
	TimerSet(300);
	TimerOn();
	state = Start;
    while (1) 
    {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
    }
	return 0;
}

