/*
 * CS120B_lab3_part1.c
 *
 * Created: 8/1/2018 1:49:04 PM
 * Author : GSL
 */ 

#include <avr/io.h>

enum States {Start,	LedB0, PressB1, ReleaseB1, LedB1, PressB0, ReleaseB0} state;

// Bitwise manipulation
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void Tick() {
	unsigned char A0 = GetBit(PINA, 0);
	unsigned char tmpB = PORTB;
	
	switch(state) { // Transitions
		case Start:
			tmpB = 0x01;
			state = LedB0;
			break;
		case LedB0:
			state = A0 ? PressB1 : LedB0;
			break;
		case PressB1:
			state = ReleaseB1;
			break;
		case ReleaseB1:
			state = A0 ? ReleaseB1 : LedB1;
			break;
		case LedB1:
			state = A0? PressB0: LedB1;
			break;
		case PressB0:
			state = ReleaseB0;
			break;
		case ReleaseB0:
			state = A0 ?  ReleaseB0 : LedB0;
			break;
		default:
			state = Start;
	} // Transitions
	
	switch(state) {
		case Start:
			break;
		case LedB0:
			break;
		case PressB1:
			tmpB = 0x02;
			break;
		case ReleaseB1:
			break;
		case LedB1:
			break;
		case PressB0:
			tmpB = 0x01;
			break;
		case ReleaseB0:
			break;
		default:
			break;
	}
	PORTB = tmpB;
}

int main(void)
{
    // Initialization
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
    while (1) 
    {
		Tick();
    }
	return 0;
}

