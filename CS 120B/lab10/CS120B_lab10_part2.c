/*
 * CS120B_lab10_part2.c
 *
 * Created: 8/21/2018 2:11:26 PM
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
char* str = "               CS120B is Legend... wait for it DARY! ";
unsigned char cnt = 0;

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum SM1_States { SM1_output };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int SMTick1(int state) {

	// Local Variables
	unsigned char i;
	unsigned char remain;
	
	//State machine transitions
	switch (state) {
		case SM1_output:
			state = SM1_output;
			break;
		default:
			state = SM1_output; // default: Initial state
			break;
	}

	//State machine actions
	switch(state) {
		case SM1_output:
			LCD_ClearScreen();
			if (cnt <= 37) {
				LCD_Cursor(1);
				for (i = 0; i < 16; i++) {
					LCD_WriteData(str[cnt+i]);
				}
			} else {
				remain = cnt - 37;
				for (i = cnt; i < 52; i++) {
					LCD_WriteData(str[i]);
				}
				for (i = 0; i < remain; i++) {
					LCD_WriteData(str[i]);
				}
			}
			cnt = cnt < 52 ? cnt + 1 : 0;
			break;
		default:
			break;
	}

	return state;
}

// Function declaration
unsigned long int findGCD(unsigned long int, unsigned long int);


int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	
	// Period for the tasks
	unsigned long int SMTick1_calc = 350;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = SMTick1_calc;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	
	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &SMTick1;//Function pointer for the tick.

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

