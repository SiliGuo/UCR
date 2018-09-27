/*
 * CS120B_lab10_part5.c
 *
 * Created: 8/22/2018 1:11:23 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "timer.h"

//--------Find GCD function --------------------------------------------------
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

//--------End Task scheduler data structure-----------------------------------

//--------Shared Variables----------------------------------------------------
unsigned char status = 0;
unsigned char up_position = 0;
unsigned char down_position = 0;
unsigned char cursor = 0;

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum SM1_States { SM1_init, SM1_start };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int SMTick1(int state) {
	
	// Local Variables
	unsigned char start = ~PINC & 0x01;
	//State machine transitions
	switch (state) {
		case SM1_init:
			if (start) {
				status = status == 0 ? 1 : 0;
				state = SM1_start;
			} else {
				state = SM1_init;
			}
			break;
		case SM1_start:
			state = start ? SM1_start : SM1_init;
			break;
		default:
			status = 0;
			state = SM1_init; // default: Initial state
			break;
	}

	//State machine actions
	switch(state) {
		case SM1_init:			
			break;
		case SM1_start:
			break;
		default:
			break;
	}
	return state;
}

//Enumeration of states.
enum SM2_States { SM2_init, SM2_move };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int SMTick2(int state) {
	
	// Local Variables
	
	//State machine transitions
	switch (state) {
		case SM2_init:
			state = status ? SM2_move : SM2_init;
			break;
		case SM2_move:
			state = status ? SM2_move : SM2_init;
			break;
		default:
			up_position = 7;
			down_position = 28;
			state = SM2_init; // default: Initial state
			break;
	}

	//State machine actions
	switch(state) {
		case SM2_init:
			break;
		case SM2_move:
			up_position = up_position > 1 ? up_position - 1 : 16;
			down_position = down_position > 17 ? down_position - 1 : 32;
			break;
		default:
			break;
	}
	LCD_ClearScreen();
	LCD_WriteData(' ');
	LCD_Cursor(up_position);
	LCD_WriteData('#');
	LCD_Cursor(down_position);
	LCD_WriteData('#');
	LCD_Cursor(2);
	return state;
}

//Enumeration of states.
enum SM3_States { SM3_init, SM3_game, SM3_up, SM3_down };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int SMTick3(int state) {
	// Local variables
	unsigned char up = ~PINC & 0x02;
	unsigned char down = ~PINC & 0x04;
	
	switch(state) {
		case SM3_init:
			state = status ? SM3_game : SM3_init;
			break;
		case SM3_game:
			if (!status) {
				state = SM3_init;
			} else if (status && up) {
				cursor -= cursor > 16 ? 16 : 0;
				state = SM3_up;
			} else if (status && down) {
				cursor += cursor < 17 ? 16 : 0;
				state = SM3_down;
			} else {
				state = SM3_game;
			}
			break;
		case SM3_up:
			state = up ? SM3_up : SM3_game;
			break;
		case SM3_down:
			state = down ? SM3_down : SM3_game;
			break;
		default:
			cursor = 2;
			state = SM3_init;
			break;
	}
	
	switch(state) {
		case SM3_init:
			break;
		case SM3_game:
			break;
		case SM3_up:
			break;
		case SM3_down:
			break;
		default:
			break;
	}
	LCD_Cursor(cursor);
	return state;
}

//Enumeration of states.
enum SM4_States { SM4_init };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int SMTick4(int state) {
	switch(state) {
		case SM4_init:
			state = SM4_init;
			break;
		default:
			state = SM4_init;
			break;
	}
	
	switch(state) {
		case SM4_init:
			if (cursor == up_position || cursor == down_position) {
				status = 0;
				LCD_ClearScreen();
				LCD_DisplayString(1, "   Hurray for   Embedded Systems");
			}
			break;
		default:
			break;
	}
}
	
int main(void)
{
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	
	// Period for the tasks
	unsigned long int SMTick1_calc = 200;
	unsigned long int SMTick2_calc = 200;
	unsigned long int SMTick3_calc = 100;
	unsigned long int SMTick4_calc = 100;

	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
	tmpGCD = findGCD(tmpGCD, SMTick3_calc);
	tmpGCD = findGCD(tmpGCD, SMTick4_calc);
	
	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	unsigned long int SMTick2_period = SMTick2_calc/GCD;
	unsigned long int SMTick3_period = SMTick3_calc/GCD;
	unsigned long int SMTick4_period = SMTick3_calc/GCD;
	
	//Declare an array of tasks
	static task task1, task2, task3, task4;
	task *tasks[] = { &task1, &task2, &task3, &task4 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &SMTick1;//Function pointer for the tick.
	
	// Task 2
	task2.state = -1;//Task initial state.
	task2.period = SMTick2_period;//Task Period.
	task2.elapsedTime = SMTick2_period;//Task current elapsed time.
	task2.TickFct = &SMTick2;//Function pointer for the tick.
	
	// Task 3
	task3.state = -1;//Task initial state.
	task3.period = SMTick3_period;//Task Period.
	task3.elapsedTime = SMTick3_period; // Task current elasped time.
	task3.TickFct = &SMTick3; // Function pointer for the tick.

	// Task 4
	task4.state = -1;//Task initial state.
	task4.period = SMTick4_period;//Task Period.
	task4.elapsedTime = SMTick4_period; // Task current elasped time.
	task4.TickFct = &SMTick4; // Function pointer for the tick.

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	LCD_init();

    unsigned short i; // Scheduler for-loop iterator
    while(1) {
	    // Scheduler code
	    for ( i = 0; i < numTasks; i++ ) {
		    // Task is ready to tick
		    if ( tasks[i]->elapsedTime == tasks[i]->period ) {
			    // Setting next state for task
			    tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			    // Reset the elapsed time for next tick.
			    tasks[i]->elapsedTime = 0;
		    }
		    tasks[i]->elapsedTime += 1;
	    }
	    while(!TimerFlag);
	    TimerFlag = 0;
    }

    // Error: Program should not exit!
    return 0;

}