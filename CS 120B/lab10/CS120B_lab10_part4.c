/*
 * CS120B_Lab10_part4.c
 *
 * Created: 2018/8/21 22:17:19
 * Author : Vincent
 */ 

#include <avr/io.h>
#include "bit.h"
#include "io.c"
#include <avr/interrupt.h>
#include <stdio.h>


volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
unsigned char index = 1;

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
b = c;
	}
	return 0;
}
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;


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

ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned char GetKeypadKey() {

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1¡¯s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('4'); }
	if (GetBit(PINC,2)==0) { return('7'); }
	if (GetBit(PINC,3)==0) { return('*'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1¡¯s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('2'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('8'); }
	if (GetBit(PINC,3)==0) { return('0'); }
	// ... *****FINISH*****

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1¡¯s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('3'); }
	if (GetBit(PINC,1)==0) { return('6'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('#'); }
	// ... *****FINISH*****

	// Check keys in col 4
	PORTC = 0x7F; // Enable col 6 with 0, disable others with 1¡¯s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }
	// ... *****FINISH*****

	return('\0'); // default value

}

enum Keypad{Wait,Press};

int K_Tick(int state){
	
	unsigned char x = GetKeypadKey();
	
	switch(state){
		case  Wait:
			state = x? Press : Wait;
			break;
		case  Press:
			state = Wait;
			break;
		default:
			state = Wait;
			break;
	}
	
	switch(state){
		case Wait:
			break;
		case Press:
			if (index == 17){index = 1;}
			LCD_Cursor(index);
			switch (x) {
				case '1': LCD_WriteData('1'); break;
				case '2': LCD_WriteData('2'); break;
				case '3': LCD_WriteData('3'); break;
				case '4': LCD_WriteData('4'); break;
				case '5': LCD_WriteData('5'); break;
				case '6': LCD_WriteData('6'); break;
				case '7': LCD_WriteData('7'); break;
				case '8': LCD_WriteData('8'); break;
				case '9': LCD_WriteData('9'); break;
				case 'A': LCD_WriteData('A'); break;
				case 'B': LCD_WriteData('B'); break;
				case 'C': LCD_WriteData('C'); break;
				case 'D': LCD_WriteData('D'); break;
				case '*': LCD_WriteData('*'); break;
				case '0': LCD_WriteData('0'); break;
				case '#': LCD_WriteData('#'); break;
				default: LCD_DisplayString(1, "error"); break;
			}
			index++;
			break;
		default:
			break;
	}
	return state;
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; 
	DDRD = 0xFF; PORTD = 0x00; 
	DDRC = 0xF0; PORTC = 0x0F; 
	
	unsigned long int K_Tick1_period = 100;
	
	unsigned long int GCD = K_Tick1_period;

	unsigned long int SMTick1_period = K_Tick1_period/GCD;
	
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = -1;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &K_Tick;
	
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	LCD_DisplayString(1, "Congratulations!");
	
	unsigned short i; 
	while(1) {
		for ( i = 0; i < numTasks; i++ ) {
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	return 0;
}



