/*
 * Custom_Project.c
 *
 * Created: 8/26/2018 10:54:55 PM
 * Author : GSL
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "timer.h"
#include "nokia5110.c"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}

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

//--------Custom Characters---------------------------------------------------
unsigned char hero[8] = {0x00, 0x0E, 0x1F, 0x0E, 0x04, 0x0E, 0x04, 0x0A};
unsigned char brick[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
unsigned char thornA[8] = {0x00, 0x04, 0x0E, 0x1F, 0x04, 0x15, 0x15, 0x1F};
unsigned char thornB[8] = {0x1F, 0x15, 0x15, 0x04, 0x1F, 0x0E, 0x04, 0x00};
unsigned char ghost[8] = {0x00, 0x0E, 0x1F, 0x15, 0x1F, 0x1F, 0x1F, 0x15};
unsigned char flag[8] = {0x00, 0x04, 0x06, 0x07, 0x04, 0x04, 0x04, 0x0E};

//--------End Custom Characters-----------------------------------------------

//--------Shared Variables----------------------------------------------------
unsigned char up_map[49] = {0, 0, 0, 0, 0, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 
						    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 1, 0, 0};
unsigned char down_map[49] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 2, 0,
							  0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
							  0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 5};


unsigned char ghost_step[6] = {20, 21, 22, 23, 24, 25};//, 24, 23, 22, 21};
unsigned char status = 0; // Start or pause
unsigned char hero_pos = 0; // The position of hero
unsigned char map_up = 0; // The number of spaces has scrolled in above map 
unsigned char map_down = 0; // The number of spaces has scrolled in below map
unsigned char last = 0; // Indicate the last page
unsigned char lose = 0; // Set to 1 when player lose the game
unsigned char win = 0; // Set to 1 when player win the game
unsigned char lose_cnt = 0; // Set to 1 if ever lost
unsigned char time_cnt = 60; // COunt for time passed

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum Start_States { Start_init, Start_condition };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Start_tick(int state) {
	
	// Local Variables
	unsigned char start = ~PINC & 0x01;
	//State machine transitions
	switch (state) {
		case Start_init:
			if (start) {
				if (status == 0) {
					if (lose == 1 || win == 1) {
						status = 0;
						hero_pos = 18;
						map_up = 0;
						map_down = 0;
						last = 0;
						lose = 0;
						win = 0;
						time_cnt = 60;
					} else {
						status = 1;
					}
				} else {
					status = 0;
				}
				state = Start_condition;
			} else {
				state = Start_init;
			}
			break;
		case Start_condition:
			state = start ? Start_condition : Start_init;
			break;
		default:
			status = 0;
			state = Start_init; // default: Initial state
			break;
	}

	//State machine actions
	switch(state) {
		case Start_init:			
			break;
		case Start_condition:
			break;
		default:
			break;
	}
	return state;
}

//Enumeration of states.
enum Move_States { Move_init, Move_left, Move_right };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Move_tick(int state) {
	
	// Local Variables
	unsigned char l = ~PINC & 0x02;
	unsigned char r = ~PINC & 0x08;
	//State machine transitions
	switch (state) {
		case Move_init:
			if (status && l && !r) {
				state = Move_left;
			} else if (status && !l && r) {
				state = Move_right;
			} else {
				state = Move_init;
			}
			break;
		case Move_left:
			if (status && l && !r) {
				state = Move_left;
			} else {
				state = Move_init;
			}
			break;
		case Move_right:
			if (status && !l && r) {
				state = Move_right;
			} else {
				state = Move_init;
			}
			break;
		default:
			hero_pos = 18;
			state = Move_init; // default: Initial state
			break;
	}

	//State machine actions
	switch(state) {
		case Move_init:
			break;
		case Move_left:
			if (hero_pos != 1 && hero_pos != 17) {
				if (hero_pos < 17) {
					hero_pos -= up_map[map_up+hero_pos-1] != 1 ? 1 : 0;
				} else {
					hero_pos -= down_map[map_down+hero_pos-17] != 1 ? 1 : 0;
				}
			}
			break;
		case Move_right:
			if (!last) {
				if (hero_pos < 26) {
					if (hero_pos < 17) {
						hero_pos += up_map[map_up+hero_pos+1] != 1 ? 1 : 0;
					} else {
						hero_pos += down_map[map_down+hero_pos-15] != 1 ? 1 : 0;
					}
				}
			} else {
				if (hero_pos < 32) {
					if (hero_pos < 17) {
						hero_pos += up_map[map_up+hero_pos+1] != 1 ? 1 : 0;
					} else {
						hero_pos += down_map[map_down+hero_pos-15] != 1 ? 1 : 0;
					}
				}
			}
			break;
		default:
			break;
	}
	if (status) {
		LCD_ClearScreen();
		LCD_WriteData(' ');
		LCD_Cursor(hero_pos);
		LCD_WriteData(0);
		LCD_Cursor(0);
	}
	return state;
}

//Enumeration of states.
enum Jump_States { Jump_init, Jump_jump, Jump_wait };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Jump_tick(int state) {
	// Local variables
	unsigned char j = ~PINC & 0x04;
	static unsigned char cnt = 0;
	
	switch(state) {
		case Jump_init:
			if (status && j) {
				if (hero_pos > 16 && up_map[map_up+hero_pos-16] != 1) {
					hero_pos -= 16;
					state = Jump_jump;
				} else {
					state = Jump_init;
				}
			} else {
				state = Jump_init;
			}
			break;
		case Jump_jump:
//			hero_pos += 16;
//			state = Jump_init;
			if (cnt < 2) {
				state = Jump_jump;
			} else {
				if (down_map[map_down+hero_pos] != 1) {
					hero_pos += 16;
					state = Jump_init;
				} else {
					state = Jump_wait;
				}
			}
			break;
		case Jump_wait:
			if (down_map[map_down+hero_pos] != 1) {
				hero_pos += 16;
				state = Jump_init;
			} else {
				state = Jump_wait;
			}
			break;
		default:
			state = Jump_init;
			break;
	}
	
	switch(state) {
		case Jump_init:
			cnt = 0;
			break;
		case Jump_jump:
			cnt = cnt < 2 ? cnt + 1 : 0;
			break;
		case Jump_wait:
			break;
		default:
			break;
	}
	if (hero_pos < 1) { hero_pos = 1; }
	if (!last) {
		if (hero_pos > 10 && hero_pos < 17) { hero_pos = 10; }
		if (hero_pos > 26) { hero_pos = 26; }
	}
	if (status) {
		LCD_ClearScreen();
		LCD_WriteData(' ');
		LCD_Cursor(hero_pos);
		LCD_WriteData(0);
		LCD_Cursor(0);
	}
	return state;
}

//Enumeration of states.
enum Map_States { Map_init, Map_scroll };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Map_tick(int state) {
	//Local variable
	unsigned char r = ~PINC & 0x08;
	
	switch(state) {
		case Map_init:
			if ((hero_pos == 10 || hero_pos == 26) && r) {
				state = Map_scroll;
			} else {
				state = Map_init;
			}
			break;
		case Map_scroll:
			if ((hero_pos == 10 || hero_pos == 26) && r) {
				state = Map_scroll;
			} else {
				state = Map_init;
			}
			break;
		default:
			map_up = 0;
			map_down = 0;
			state = Map_init;
			break;
	}
	
	switch(state) {
		case Map_init:
//			cnt = cnt < 19 ? cnt + 1 : 0;
			break;
		case Map_scroll:
//			cnt = cnt < 19 ? cnt + 1 : 0;
			if ((hero_pos == 10 && up_map[map_up + 11] != 1) || (hero_pos == 26 && down_map[map_down + 11] != 1)) {
				map_up += map_up < 32 ? 1 : 0;
				map_down += map_down < 32 ? 1 : 0;
			}
			if (map_up == 32) { last = 1; }
			break;
		default:
			break;
	}

//		for (i = 0; i < 19; i++) {
//			down_map[ghost_step[i]] = (i == cnt) ? 4 : 0;
//		}
/*
	if (status == 0) { 
		if (lose == 0) {
			LCD_DisplayString(1, " Side Scroller");
			LCD_Cursor(18);
			LCD_WriteData(0);
			LCD_Cursor(0);
		}
		return state; 
		}
	for (i = 1; i <= 16; i++) {
		if (up_map[map_up + i] != 0) {
			LCD_Cursor(i);
			LCD_WriteData(up_map[map_up + i]);
		}
		if (down_map[map_down + i] != 0) {
			LCD_Cursor(i + 16);
			LCD_WriteData(down_map[map_down + i]);
		}
	} 
	LCD_Cursor(0);
	*/
	return state;
}

//Enumeration of states.
enum Ghost_States { Ghost_1, Ghost_2, Ghost_3, Ghost_4, Ghost_5, Ghost_6 };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Ghost_tick(int state) {
	//Local variable
	static unsigned char inc;
	unsigned char i;
	
	switch(state) {
		case Ghost_1:
			inc = 1;
			state = Ghost_2;
			break;
		case Ghost_2:
			if (inc) {
				state = Ghost_3;
			} else {
				state = Ghost_1;
			}
			break;
		case Ghost_3:
			if (inc) {
				state = Ghost_4;
			} else {
				state = Ghost_2;
			}
			break;
		case Ghost_4:
			if (inc) {
				state = Ghost_5;
			} else {
				state = Ghost_3;
			}
			break;
		case Ghost_5:
			if (inc) {
				state = Ghost_6;
			} else {
				state = Ghost_4;
			}
			break;
		case Ghost_6:
			inc = 0;
			state = Ghost_5;
			break;
		default:
			inc = 1;
			state = Ghost_1;
			break;
	}
	
	switch(state) {
		case Ghost_1:
			down_map[20] = 4;
			down_map[21] = 0;
			down_map[22] = 0;
			down_map[23] = 0;
			down_map[24] = 0;
			down_map[25] = 0;
			break;
		case Ghost_2:
			down_map[20] = 0;
			down_map[21] = 4;
			down_map[22] = 0;
			down_map[23] = 0;
			down_map[24] = 0;
			down_map[25] = 0;
			break;
		case Ghost_3:
			down_map[20] = 0;
			down_map[21] = 0;
			down_map[22] = 4;
			down_map[23] = 0;
			down_map[24] = 0;
			down_map[25] = 0;
			break;
		case Ghost_4:
			down_map[20] = 0;
			down_map[21] = 0;
			down_map[22] = 0;
			down_map[23] = 4;
			down_map[24] = 0;
			down_map[25] = 0;
			break;
		case Ghost_5:
			down_map[20] = 0;
			down_map[21] = 0;
			down_map[22] = 0;
			down_map[23] = 0;
			down_map[24] = 4;
			down_map[25] = 0;
			break;
		case Ghost_6:
			down_map[20] = 0;
			down_map[21] = 0;
			down_map[22] = 0;
			down_map[23] = 0;
			down_map[24] = 0;
			down_map[25] = 4;
			break;
		default:
			break;
	}
	
	if (status == 0) {
		if (lose == 0 && win == 0) {
			LCD_DisplayString(1, " Side Scroller");
			LCD_Cursor(18);
			LCD_WriteData(0);
			LCD_Cursor(32);
			LCD_WriteData(5);
			LCD_Cursor(0);
		}
		return state;
	}

	for (i = 1; i <= 16; i++) {
		if (up_map[map_up + i] != 0) {
			LCD_Cursor(i);
			LCD_WriteData(up_map[map_up + i]);
		}
		if (down_map[map_down + i] != 0) {
			LCD_Cursor(i + 16);
			LCD_WriteData(down_map[map_down + i]);
		}
	}
	LCD_Cursor(0);
	return state;
}

//Enumeration of states.
enum Check_States { Check_init };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Check_tick(int state) {
	//Local variable
	static unsigned char cnt;
	unsigned char a, b, c;
	
	switch(state) {
		case Check_init:
			state = Check_init;
			break;
		default:
			cnt = 0;
			state = Check_init;
			break;
	}
	
	switch(state) {
		case Check_init:
			if (status) {
				cnt = cnt < 4 ? cnt + 1 : 0;
				if (cnt == 4) {
					time_cnt--;
					if (time_cnt == 0) {
						lose = 1;
					}
				}
			}
			if ((hero_pos < 17 && up_map[map_up + hero_pos] == 2) || (hero_pos >= 17 && down_map[map_down + hero_pos - 16] == 2) ||
				(hero_pos < 17 && up_map[map_up + hero_pos] == 3) || (hero_pos >= 17 && down_map[map_down + hero_pos - 16] == 3) ||
				(hero_pos < 17 && up_map[map_up + hero_pos] == 4) || (hero_pos >= 17 && down_map[map_down + hero_pos - 16] == 4)) {
				lose = 1;
				lose_cnt = 1;
			} else if (hero_pos == 32 && down_map[map_down + hero_pos - 16] == 5) {
				win = 1;
			}
			break;
		default:
			break;
	}

	a = time_cnt / 10;
	b = time_cnt % 10;
	nokia_lcd_init();
	nokia_lcd_clear();
	nokia_lcd_write_string("Time:",1);
	nokia_lcd_set_cursor(45, 0);
	nokia_lcd_write_char(a + '0', 2);
	nokia_lcd_write_char(b + '0', 2);
	
	a = EEPROM_read(0) / 100;
	b = (EEPROM_read(0) - 100 * a) / 10;
	c = EEPROM_read(0) % 10;
	nokia_lcd_set_cursor(0, 20);
	nokia_lcd_write_string("Highest score:", 1);
	nokia_lcd_set_cursor(40, 30);
	nokia_lcd_write_char(a + '0', 2);
	nokia_lcd_write_char(b + '0', 2);
	nokia_lcd_write_char(c + '0', 2);
	nokia_lcd_render();

	if (lose) {
		status = 0;
		LCD_ClearScreen();
		LCD_DisplayString(1, "     Sorry         You lose!");
		LCD_Cursor(0);
	}
	return state;
}

enum Score_States { Score_init };

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int Score_tick(int state) {
	// Local variable
	unsigned char score;
	unsigned char a, b, c;
	
	switch(state) {
		case Score_init:
			state = Score_init;
			break;
		default:
			score = 100;
			state = Score_init;
			break;
	}
	
	switch(state) {
		case Score_init:
			if (win) {
				status = 0;
				score -= time_cnt > 50 ? 0 : (50 - time_cnt);
				score += lose_cnt ? 0 : 20;
				
				if (score > EEPROM_read(0)) {
					EEPROM_write(0, score);
				}
				
				LCD_DisplayString(1, "    You win!       Score: ");
				
				a = score / 100;
				b = (score - a * 100) / 10;
				c = score % 10;
				LCD_WriteData(a + '0');
				LCD_WriteData(b + '0');
				LCD_WriteData(c + '0');
				LCD_Cursor(0);
			}
	}
	
	return state;	
}

int main(void)
{
	DDRC = 0x00; PORTC = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	
	// Period for the tasks
	unsigned long int Start_tick_calc = 100;
	unsigned long int Move_tick_calc = 200;
	unsigned long int Jump_tick_calc = 200;
	unsigned long int Map_tick_calc = 200;
	unsigned long int Check_tick_calc = 200;
	unsigned long int Ghost_tick_calc = 200;
	unsigned long int Score_tick_calc = 200;

	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(Start_tick_calc, Move_tick_calc);
	tmpGCD = findGCD(tmpGCD, Jump_tick_calc);
	tmpGCD = findGCD(tmpGCD, Map_tick_calc);
	tmpGCD = findGCD(tmpGCD, Check_tick_calc);
	tmpGCD = findGCD(tmpGCD, Ghost_tick_calc);
	tmpGCD = findGCD(tmpGCD, Score_tick_calc);
	
	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int Start_tick_period = Start_tick_calc/GCD;
	unsigned long int Move_tick_period = Move_tick_calc/GCD;
	unsigned long int Jump_tick_period = Jump_tick_calc/GCD;
	unsigned long int Map_tick_period = Map_tick_calc/GCD;
	unsigned long int Check_tick_period = Check_tick_calc/GCD;
	unsigned long int Ghost_tick_period = Ghost_tick_calc/GCD;
	unsigned long int Score_tick_period = Score_tick_calc/GCD;
	
	//Declare an array of tasks
	static task task1, task2, task3, task4, task5, task6, task7;
	task *tasks[] = { &task1, &task2, &task3, &task4, &task5, &task6, &task7 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = Start_tick_period;//Task Period.
	task1.elapsedTime = Start_tick_period;//Task current elapsed time.
	task1.TickFct = &Start_tick;//Function pointer for the tick.
	
	// Task 2
	task2.state = -1;//Task initial state.
	task2.period = Move_tick_period;//Task Period.
	task2.elapsedTime = Move_tick_period;//Task current elapsed time.
	task2.TickFct = &Move_tick;//Function pointer for the tick.
	
	// Task 3
	task3.state = -1;//Task initial state.
	task3.period = Jump_tick_period;//Task Period.
	task3.elapsedTime = Jump_tick_period; // Task current elasped time.
	task3.TickFct = &Jump_tick; // Function pointer for the tick.

	// Task 4
	task4.state = -1;//Task initial state.
	task4.period = Map_tick_period;//Task Period.
	task4.elapsedTime = Map_tick_period; // Task current elasped time.
	task4.TickFct = &Map_tick; // Function pointer for the tick.

	// Task6
	task5.state = -1;
	task5.period = Ghost_tick_period;
	task5.elapsedTime = Ghost_tick_period;
	task5.TickFct = &Ghost_tick;
	
	// Task6
	task6.state = -1;
	task6.period = Check_tick_period;
	task6.elapsedTime = Check_tick_period;
	task6.TickFct = &Check_tick;
	
	// Task7
	task7.state = -1;
	task7.period = Score_tick_period;
	task7.elapsedTime = Score_tick_period;
	task7.TickFct = &Score_tick;

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	//EEPROM_write(0, 0);
	if (EEPROM_read(0) == 255) { EEPROM_write(0, 0); }
	
	// Declare Custom Characters
	LCD_CustomChar(0, hero);
	LCD_CustomChar(1, brick);
	LCD_CustomChar(2, thornA);
	LCD_CustomChar(3, thornB);
	LCD_CustomChar(4, ghost);
	LCD_CustomChar(5, flag);
	
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