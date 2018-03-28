;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 023
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

.ORIG x3000				; Program begins here
;-------------
;Instructions
;-------------
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
PROCESS_LOOP
	LD R0, MENU_3400		; Subroutine Menu_3400
	JSRR R0	
	
	ADD R2, R1, #-1			; if (R2 == 1) SUB_1
	BRz SUB_1
	ADD R2, R1, #-2			; if (R2 == 2) SUB_2
	BRz SUB_2
	ADD R2, R1, #-3			; if (R2 == 3) SUB_3
	BRz SUB_3
	ADD R2, R1, #-4			; if (R2 == 4) SUB_4
	BRz SUB_4
	ADD R2, R1, #-5			; if (R2 == 5) SUB_5
	BRz SUB_5
	ADD R2, R1, #-6			; if (R2 == 6) SUB_6
	BRz SUB_6
	ADD R2, R1, #-7			; if (R2 == 7) SUB_7
	BRz SUB_7

SUB_1
	LD R0, ALL_MACHINES_BUSY_3600	; Subroutine ALL_MACHINES_BUSY_3600
	JSRR R0
	ADD R1, R2, #-1			; R1 <-- R2 - #1
	BRz BUSY			; if (R1 == 0) BUSY
	BRn NOT_BUSY			; if (R1 <0) NOT_BUSY
BUSY
	LEA R0, ALLBUSY			; Output message
	PUTS
	BRnzp END_SUB_1			; Jump to END_SUB_1
NOT_BUSY
	LEA R0, ALLNOTBUSY		; Output message
	PUTS
END_SUB_1
	BRnzp PROCESS_LOOP		; Back to PROCESS_LOOP

SUB_2
	LD R0, ALL_MACHINES_FREE_3800	; Subroutine ALL_MACHINES_FREE_3800
	JSRR R0
	ADD R1, R2, #-1			; R1 <-- R2 - #1
	BRz FREE			; if (R1 == 0) FREE
	BRn NOT_FREE			; if (R1 <0) NOT_FREE
FREE
	LEA R0, ALLFREE			; Output message
	PUTS
	BRnzp END_SUB_2
NOT_FREE
	LEA R0, ALLNOTFREE		; Output message
	PUTS
END_SUB_2
	BRnzp PROCESS_LOOP

SUB_3
	LD R0, NUM_BUSY_MACHINES_4000
	JSRR R0
	LEA R0, BUSYMACHINE1		; Output message
	PUTS
	LD R0, PRINT_NUMBER_5000
	JSRR R0
	LEA R0, BUSYMACHINE2
	PUTS
	BRnzp PROCESS_LOOP

SUB_4
	LD R0, NUM_FREE_MACHINES_4200
	JSRR R0
	LEA R0, FREEMACHINE1		; Output message
	PUTS
	LD R0, PRINT_NUMBER_5000
	JSRR R0
	LEA R0, FREEMACHINE2
	PUTS
	BRnzp PROCESS_LOOP

SUB_5
	LD R0, GET_INPUT_4800
	JSRR R0
	LD R0, MACHINES_STATUS_4400
	JSRR R0
	LEA R0, STATUS1			; Output message
	PUTS
	ADD R3, R2, #0
	ADD R2, R1, #0
	LD R0, PRINT_NUMBER_5000
	JSRR R0
	ADD R2, R3, #0
	BRz STATUS_BUSY
	LEA R0, STATUS3
	PUTS
	BRnzp END_STATUS
STATUS_BUSY
	LEA R0, STATUS2
	PUTS
END_STATUS	
	BRnzp PROCESS_LOOP

SUB_6
	LD R0, FIRST_FREE_4600
	JSRR R0
	ADD R3, R2, #-16
	BRz NO_FREE
	LEA R0, FIRSTFREE		; Output message
	PUTS
	LD R0, PRINT_NUMBER_5000
	JSRR R0
	LEA R0, FIRSTFREE2
	PUTS
	BRnzp END_SUB_6
NO_FREE
	LEA R0, FIRSTFREE3
	PUTS
END_SUB_6
	BRnzp PROCESS_LOOP

SUB_7
	LEA R0, Goodbye
	PUTS
HALT
;---------------	
;Data
;---------------
;Add address for subroutines
MENU_3400		.FILL	x3400
ALL_MACHINES_BUSY_3600	.FILL	x3600
ALL_MACHINES_FREE_3800	.FILL	x3800
NUM_BUSY_MACHINES_4000	.FILL	x4000
NUM_FREE_MACHINES_4200	.FILL	x4200
MACHINES_STATUS_4400	.FILL	x4400
FIRST_FREE_4600		.FILL	x4600
GET_INPUT_4800		.FILL	x4800
PRINT_NUMBER_5000	.FILL	x5000

;Other data 

;Strings for options
Goodbye 	.Stringz	"Goodbye!\n"
ALLNOTBUSY 	.Stringz	"Not all machines are busy\n"
ALLBUSY 	.Stringz	"All machines are busy\n"
ALLFREE 	.STRINGZ	"All machines are free\n"
ALLNOTFREE	.STRINGZ	"Not all machines are free\n"
BUSYMACHINE1	.STRINGZ	"There are "
BUSYMACHINE2	.STRINGZ	" busy machines\n"
FREEMACHINE1	.STRINGZ	"There are "
FREEMACHINE2	.STRINGZ	" free machines\n"
STATUS1		.STRINGZ	"Machine "
STATUS2		.STRINGZ	" is busy\n"
STATUS3		.STRINGZ	" is free\n"
FIRSTFREE	.STRINGZ	"The first available machine is number "
FIRSTFREE2	.STRINGZ	"\n"
FIRSTFREE3	.STRINGZ	"No machines are free\n"


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: MENU_3400
; Inputs: None
; Postcondition: The subroutine has printed out a menu with numerical options, allowed the
;                          user to select an option, and returned the selected option.
; Return Value (R1): The option selected:  #1, #2, #3, #4, #5, #6 or #7
; no other return value is possible
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine MENU
;--------------------------------
.ORIG x3400
;(1) Backup registers
	ST R0, BACKUP_R0_3400		; Backup R0
	ST R2, BACKUP_R2_3400		; Backup R2
	ST R7, BACKUP_R7_3400		; Backup R7
;(2) Alogrithm
MENU_LOOP
	LD R0, Menu_string_addr		; R0 <-- xABCD
	PUTS

	GETC				; Prompt input
	OUT				; Output input value
	LD R2, N_DEC_49_3400		; R2 <-- #-49
	ADD R2, R0, R2			; R2 <-- R0 + R2
	BRn ERROR_3400			; if (R2 <0) ERROR_3400
	ADD R2, R2, #-6			; R2 <-- R2 - #6
	BRp ERROR_3400			; if (R2 >0) ERROR_3400

	LD R1, N_DEC_48_3400		; R1 <-- #-48
	ADD R1, R0, R1			; R1 <-- R0 + R1

	LD R0, NEWLINE_3400		; R0 <-- '\n'
	OUT				
	BRnzp END_MENU_LOOP		; Jump to END_MENU_LOOP

ERROR_3400
	LD R0, NEWLINE_3400		; Output NEWLINE
	OUT
	LEA R0, Error_message_1		; Output error message
	PUTS
	BRnzp MENU_LOOP
END_MENU_LOOP
	

;(3) Restore registers
	LD R0, BACKUP_R0_3400
	LD R2, BACKUP_R2_3400
	LD R7, BACKUP_R7_3400
;(4) Return
	RET

;--------------------------------
;Data for subroutine MENU
;--------------------------------
BACKUP_R0_3400		.BLKW		#1
BACKUP_R2_3400		.BLKW		#1
BACKUP_R7_3400		.BLKW		#1
Error_message_1 	.STRINGZ	"INVALID INPUT\n"
Menu_string_addr 	.FILL		x6000
NEWLINE_3400		.FILL		x0A
N_DEC_48_3400		.FILL		#-48
N_DEC_49_3400		.FILL		#-49

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_BUSY_3600
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are busy
; Return value (R2): 1 if all machines are busy,    0 otherwise
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine ALL_MACHINES_BUSY
;--------------------------------
.ORIG x3600
;(1) Backup registers
	ST R1, BACKUP_R1_3600
	ST R3, BACKUP_R3_3600
	ST R7, BACKUP_R7_3600
;(2) Algorithms
LD R1, BUSYNESS_ADDR_ALL_MACHINES_BUSY
LDR R3, R1, #0
LD R2, DEC_1_3600

LD R1, DEC_16_3600
BUSY_LOOP
	ADD R3, R3, #0
	BRzp NOT_SET_FREE
	AND R2, R2, #0

NOT_SET_FREE
	ADD R3, R3, R3
	ADD R1, R1, #-1
	BRp BUSY_LOOP

;(3) Restore registers
	LD R1, BACKUP_R1_3600
	LD R3, BACKUP_R3_3600
	LD R7, BACKUP_R7_3600
;(4) Return
	RET

;--------------------------------
;Data for subroutine ALL_MACHINES_BUSY
;--------------------------------
BACKUP_R1_3600	.BLKW	#1
BACKUP_R3_3600	.BLKW	#1
BACKUP_R7_3600	.BLKW	#1
BUSYNESS_ADDR_ALL_MACHINES_BUSY .Fill xD000
DEC_1_3600	.FILL	#1
DEC_16_3600	.FILL	#16

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_FREE_3800
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are free
; Return value (R2): 1 if all machines are free,    0 otherwise
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine ALL_MACHINES_FREE
;--------------------------------
.ORIG x3800
;(1) Backup registers
	ST R1, BACKUP_R1_3800
	ST R3, BACKUP_R3_3800
	ST R7, BACKUP_R7_3800

;(2) Algorithms
LD R1, BUSYNESS_ADDR_ALL_MACHINES_FREE
LDR R3, R1, #0
LD R2, DEC_1_3800

LD R1, DEC_16_3800
FREE_LOOP
	ADD R3, R3, #0
	BRn NOT_SET_BUSY
	AND R2, R2, #0

NOT_SET_BUSY
	ADD R3, R3, R3
	ADD R1, R1, #-1
	BRp FREE_LOOP

;(3) Restore registers
	LD R1, BACKUP_R1_3800
	LD R3, BACKUP_R3_3800
	LD R7, BACKUP_R7_3800
;(4) Return
	RET

;--------------------------------
;Data for subroutine ALL_MACHINES_FREE
;--------------------------------
BACKUP_R1_3800	.BLKW	#1
BACKUP_R3_3800	.BLKW	#1
BACKUP_R7_3800	.BLKW	#1
BUSYNESS_ADDR_ALL_MACHINES_FREE .Fill xD000
DEC_1_3800	.FILL	#1
DEC_16_3800	.FILL	#16

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: NUM_BUSY_MACHINES_4000
; Inputs: None
; Postcondition: The subroutine has returned the number of busy machines.
; Return Value (R2): The number of machines that are busy
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine NUM_BUSY_MACHINES
;--------------------------------
.ORIG x4000
;(1) Backup registers
	ST R1, BACKUP_R1_4000
	ST R3, BACKUP_R3_4000
	ST R7, BACKUP_R7_4000
;(2) Algorithms
LD R1, BUSYNESS_ADDR_NUM_BUSY_MACHINES
LDR R3, R1, #0
AND R2, R2, #0

LD R1, DEC_16_4000
COUNT_BUSY_LOOP
	ADD R3, R3, #0
	BRn JUMP_COUNT_BUSY
	ADD R2, R2, #1

JUMP_COUNT_BUSY
	ADD R3, R3, R3
	ADD R1, R1, #-1
	BRp COUNT_BUSY_LOOP

;(3) Restore registers
	LD R1, BACKUP_R1_4000
	LD R3, BACKUP_R3_4000
	LD R7, BACKUP_R7_4000
;(4) Return
	RET

;--------------------------------
;Data for subroutine NUM_BUSY_MACHINES
;--------------------------------
BACKUP_R1_4000	.BLKW	#1
BACKUP_R3_4000	.BLKW	#1
BACKUP_R7_4000	.BLKW	#1
BUSYNESS_ADDR_NUM_BUSY_MACHINES .Fill xD000
DEC_16_4000	.FILL	#16


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: NUM_FREE_MACHINES_4200
; Inputs: None
; Postcondition: The subroutine has returned the number of free machines
; Return Value (R2): The number of machines that are free 
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine NUM_FREE_MACHINES
;--------------------------------
.ORIG x4200
;(1) Backup registers
	ST R1, BACKUP_R1_4200
	ST R3, BACKUP_R3_4200
	ST R7, BACKUP_R7_4200
;(2) Algorithms
LD R1, BUSYNESS_ADDR_NUM_FREE_MACHINES
LDR R3, R1, #0
AND R2, R2, #0

LD R1, DEC_16_4200
COUNT_FREE_LOOP
	ADD R3, R3, #0
	BRzp JUMP_COUNT_FREE
	ADD R2, R2, #1

JUMP_COUNT_FREE
	ADD R3, R3, R3
	ADD R1, R1, #-1
	BRp COUNT_FREE_LOOP

;(3) Restore registers
	LD R1, BACKUP_R1_4200
	LD R3, BACKUP_R3_4200
	LD R7, BACKUP_R7_4200
;(4) Return
	RET

;--------------------------------
;Data for subroutine NUM_FREE_MACHINES
;--------------------------------
BACKUP_R1_4200	.BLKW	#1
BACKUP_R3_4200	.BLKW	#1
BACKUP_R7_4200	.BLKW	#1
BUSYNESS_ADDR_NUM_FREE_MACHINES .Fill xD000
DEC_16_4200	.FILL	#16


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: MACHINE_STATUS_4400
; Input (R1): Which machine to check
; Postcondition: The subroutine has returned a value indicating whether the machine indicated
;                          by (R1) is busy or not.
; Return Value (R2): 0 if machine (R1) is busy, 1 if it is free
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine MACHINE_STATUS
;--------------------------------
.ORIG x4400
;(1) Backup registers
	ST R1, BACKUP_R1_4400
	ST R3, BACKUP_R3_4400
	ST R4, BACKUP_R4_4400
	ST R7, BACKUP_R7_4400
;(2) Algorithms
LD R4, BUSYNESS_ADDR_MACHINE_STATUS
LDR R3, R4, #0

AND R2, R2, #0
NOT R4, R1
ADD R4, R4, #1
ADD R0, R4, #15
BRz STATUS_CHECK


SHIFT_LOOP
	ADD R3, R3, R3
	ADD R0, R0, #-1
	BRp SHIFT_LOOP

STATUS_CHECK
	ADD R3, R3, #0
	BRzp END_STATUS_CHECK
	LD R2, DEC_1_4400
END_STATUS_CHECK

;(3) Restore registers
	LD R1, BACKUP_R1_4400
	LD R3, BACKUP_R3_4400
	LD R4, BACKUP_R4_4400
	LD R7, BACKUP_R7_4400
;(4) Return
	RET

;--------------------------------
;Data for subroutine MACHINE_STATUS
;--------------------------------
BACKUP_R1_4400	.BLKW	#1
BACKUP_R3_4400	.BLKW	#1
BACKUP_R4_4400	.BLKW	#1
BACKUP_R7_4400	.BLKW	#1
BUSYNESS_ADDR_MACHINE_STATUS.Fill xD000
DEC_1_4400	.FILL	#1

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: FIRST_FREE_4600
; Inputs: None
; Postcondition: 
; The subroutine has returned a value indicating the lowest numbered free machine
; Return Value (R2): the number of the free machine
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine FIRST_FREE
;--------------------------------
.ORIG x4600
;(1) Backup registers
	ST R0, BACKUP_R0_4600
	ST R1, BACKUP_R1_4600
	ST R3, BACKUP_R3_4600
	ST R4, BACKUP_R4_4600
	ST R5, BACKUP_R5_4600
	ST R6, BACKUP_R6_4600
	ST R7, BACKUP_R7_4600
;(2) Algorithms
LD R0, BUSYNESS_ADDR_FIRST_FREE
LDR R1, R0, #0
LD R2, DEC_16_4600
LD R0, DEC_16_4600
AND R6, R6, #0
FIRST_FREE
	ADD R3, R0, #-1
	ADD R4, R1, #0
	ADD R5, R0, #-1
	BRz END_SHIFT
	SHIFT_4600
		ADD R4, R4, R4
		ADD R3, R3, #-1
		BRp SHIFT_4600
END_SHIFT
	ADD R6, R6, #1
	ADD R4, R4, #0
	BRzp BIT_BUSY
	ADD R2, R6, #-1
	BRnzp END_FIRST_FREE
BIT_BUSY
	ADD R0, R0, #-1
	BRp FIRST_FREE
END_FIRST_FREE

;(3) Restore registers
	LD R0, BACKUP_R0_4600
	LD R1, BACKUP_R1_4600
	LD R3, BACKUP_R3_4600
	LD R4, BACKUP_R4_4600
	LD R5, BACKUP_R5_4600
	LD R6, BACKUP_R6_4600
	LD R7, BACKUP_R7_4600
;(4) Return
	RET

;--------------------------------
;Data for subroutine FIRST_FREE
;--------------------------------
BACKUP_R0_4600	.BLKW	#1
BACKUP_R1_4600	.BLKW	#1
BACKUP_R3_4600	.BLKW	#1
BACKUP_R4_4600	.BLKW	#1
BACKUP_R5_4600	.BLKW	#1
BACKUP_R6_4600	.BLKW	#1
BACKUP_R7_4600	.BLKW	#1
BUSYNESS_ADDR_FIRST_FREE .Fill xD000
DEC_16_4600	.FILL	#16

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: GET_INPUT_4800
; Inputs: None
; Postcondition: 
; The subroutine get up to a 5 digit input from the user within the range [-32768,32767]
; Return Value (R1): The value of the contructed input
; NOTE: This subroutine should be the same as the one that you did in assignment 5
;	to get input from the user, except the prompt is different.
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine 
;--------------------------------
.ORIG x4800
;(1) Backup registers
	ST R0, BACKUP_R0_4800		; Backup R0
	ST R2, BACKUP_R2_4800		; Backup R2
	ST R3, BACKUP_R3_4800		; Backup R3
	ST R4, BACKUP_R4_4800		; Backup R4
	ST R5, BACKUP_R5_4800		; Backup R5
	ST R6, BACKUP_R6_4800		; Backup R6
	ST R7, BACKUP_R7_4800		; Backup R7
;(2) Algorithms
AND R1, R1, #0
LEA R0, prompt
PUTS

LD R2, N_DEC_48_4800			; R2 <-- #-48
LD R3, N_NEWLINE_4800			; R3 <-- #-10

SIGN_CHECK
	GETC

	ADD R4, R0, R3			; Check for '\n'
	BRz ERROR			; if input a '\n', END_INPUT_LOOP
	OUT				; Output

	LD R4, N_POS_4800		; Check for '+'
	ADD R4, R0, R4
	BRz SECOND_CHECK		; if input a '+', INPUT_LOOP

	LD R4, N_NEG_4800		; Check for '-'
	ADD R4, R0, R4
	BRz MARK_NEG			; if input a '-', MARK_NEG
	BRnp ERROR_CHECK		; else, ERROR_CHECK

MARK_NEG				; if input a '-', set R6 <-- #1
	ADD R6, R6, #1
SECOND_CHECK
	GETC
	ADD R4, R0, R3
	BRz ERROR
	OUT
	BRnp ERROR_CHECK

INPUT_LOOP
	GETC				; Prompt from user
	ADD R4, R0, R3			; Check for '\n'
	BRz END_INPUT_LOOP		; if input a '\n', END_INPUT_LOOP
	OUT				; output

ERROR_CHECK
	ADD R4, R0, R2			; Check if input < 0 (ASCII code)
	BRn ERROR
	ADD R4, R4, #-9			; Check if input > 9 (ASCII code)
	BRp ERROR
	BRnz CONTINUE

ERROR
	AND R6, R6, #0
	LD R0, NEWLINE_4800
	OUT
;NOT_OUTPUT
	LEA R0, Error_message_2
	PUTS
	LEA R0, prompt
	PUTS
	AND R1, R1, #0
	BRz SIGN_CHECK
	
CONTINUE
	LD R5, DEC_9_4800
	ADD R4, R1, #0
	MULTI_TEN
		ADD R1, R4, R1
		ADD R5, R5, #-1
		BRp MULTI_TEN

	ADD R0,R0, R2
	ADD R1, R1, R0
	BRnzp INPUT_LOOP
END_INPUT_LOOP
	
ADD R6, R6, #0
BRz END_CONVERT

CONVERT
	NOT R1, R1
	ADD R1, R1, #1
END_CONVERT
BRn ERROR
ADD R4, R1, #-15
BRp ERROR

LD R0, NEWLINE_4800
OUT

;(3) Restore registers
	LD R0, BACKUP_R0_4800		; Restore R0
	LD R2, BACKUP_R2_4800		; Restore R2
	LD R3, BACKUP_R3_4800		; Restore R3
	LD R4, BACKUP_R4_4800		; Restore R4
	LD R5, BACKUP_R5_4800		; Restore R5
	LD R6, BACKUP_R6_4800		; Restore R6
	LD R7, BACKUP_R7_4800		; Restore R7

;(4) Return
	RET

;--------------------------------
;Data for subroutine Get input
;--------------------------------
BACKUP_R0_4800	.BLKW	#1
BACKUP_R2_4800	.BLKW	#1
BACKUP_R3_4800	.BLKW	#1
BACKUP_R4_4800	.BLKW	#1
BACKUP_R5_4800	.BLKW	#1
BACKUP_R6_4800	.BLKW	#1
BACKUP_R7_4800	.BLKW	#1
prompt .STRINGZ "Enter which machine you want the status of (0 - 15), followed by ENTER: "
Error_message_2 .STRINGZ "ERROR INVALID INPUT\n"
NEWLINE_4800	.FILL	x0A
DEC_9_4800	.FILL	#9
N_DEC_48_4800	.FILL	#-48
N_NEWLINE_4800	.FILL	#-10
N_POS_4800	.FILL	#-43
N_NEG_4800	.FILL	#-45
;-----------------------------------------------------------------------------------------------------------------
; Subroutine: PRINT_NUMBER_5000
; Inputs: 
; Postcondition: 
; The subroutine prints the number that is in 
; Return Value : 
; NOTE: This subroutine should print the number to the user WITHOUT 
;		leading 0's and DOES NOT output the '+' for positive numbers.
;-----------------------------------------------------------------------------------------------------------------
;-------------------------------
;INSERT CODE For Subroutine 
;--------------------------------
.ORIG x5000				; Subroutine begins here
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_5000		; Backup R0
	ST R1, BACKUP_R1_5000		; Backup R1
	ST R2, BACKUP_R2_5000		; Backup R2
	ST R3, BACKUP_R3_5000		; Backup R3
	ST R4, BACKUP_R4_5000		; Backup R4
	ST R5, BACKUP_R5_5000		; Backup R5
	ST R6, BACKUP_R6_5000		; Backup R6
	ST R7, BACKUP_R7_5000		; Backup R7

;(2) Algorithm
LEA R1, DIVIDER				; Create array of 5 spaces
LD R5, TEN_THOUSAND			; Store -10000 in array
STR R5, R1, #0
ADD R1, R1, #1
LD R5, THOUSAND				; Store -1000 in array
STR R5, R1, #0
ADD R1, R1, #1
LD R5, HUNDRED				; Store -100 in array
STR R5, R1, #0
ADD R1, R1, #1
LD R5, TEN				; Store -10 in array
STR R5, R1, #0
ADD R1, R1, #1
LD R5, ONE				; Store -1 in array
STR R5, R1, #0
ADD R1, R1, #1


ADD R2, R2, #0				; R5 <-- R5
BRz OUTPUT_ZERO
BRp END_SIGN_PRINT			; if (R5 >= 0) POS_SIGN
BRn NEG_SIGN				; if (R5 < 0) NEG_SIGN

OUTPUT_ZERO
	LD R0, DEC_48_5000
	OUT
	BRnzp END

NEG_SIGN				
	ADD R2, R2, #-1
	NOT R2, R2
	LD R0, NEG
	OUT
END_SIGN_PRINT

LD R1, DEC_5
LEA R5, DIVIDER
AND R6, R6, #0

PRINT_LOOP
	ADD R4, R2, #0
	AND R3, R3, #0
	LDR R0, R5, #0

	COUNT_LOOP_5000
		ADD R3, R3, #1
		ADD R4, R0, R4
		BRzp COUNT_LOOP_5000

	ADD R3, R3, #-1
	BRz OUTPUT
	LD R6, SIGN
					
OUTPUT
	ADD R6, R6, #0
	BRz END_OUTPUT
	LD R0, DEC_48_5000
	ADD R0, R0, R3
	OUT
END_OUTPUT

	ADD R3, R3, #0
	BRz END_NEW_NUMBER_LOOP
	NEW_NUMBER_LOOP
		LDR R0, R5, #0
		ADD R2, R0, R2
		ADD R3, R3, #-1
		BRp NEW_NUMBER_LOOP
	END_NEW_NUMBER_LOOP

	ADD R5, R5, #1
	ADD R1, R1, #-1
	BRp PRINT_LOOP
END

;(3) Restore registers
	LD R0, BACKUP_R0_5000		; Restore R0
	LD R1, BACKUP_R1_5000		; Restore R1
	LD R2, BACKUP_R2_5000		; Restore R2
	LD R3, BACKUP_R3_5000		; Restore R3
	LD R4, BACKUP_R4_5000		; Restore R4
	LD R5, BACKUP_R5_5000		; Restore R5
	LD R6, BACKUP_R6_5000		; Restore R6
	LD R7, BACKUP_R7_5000		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_5000	.BLKW	#1
BACKUP_R1_5000	.BLKW	#1
BACKUP_R2_5000	.BLKW	#1
BACKUP_R3_5000	.BLKW	#1
BACKUP_R4_5000	.BLKW	#1
BACKUP_R5_5000	.BLKW	#1
BACKUP_R6_5000	.BLKW	#1
BACKUP_R7_5000	.BLKW	#1
POS		.FILL	#43
NEG		.FILL	#45
DEC_5		.FILL	#5
DIVIDER		.BLKW	#5
TEN_THOUSAND	.FILL	#-10000
THOUSAND	.FILL	#-1000
HUNDRED		.FILL	#-100
TEN		.FILL	#-10
ONE		.FILL	#-1
DEC_48_5000	.FILL	#48
SIGN		.FILL	#1



.ORIG x6000
MENUSTRING .STRINGZ "**********************\n* The Busyness Server *\n**********************\n1. Check to see whether all machines are busy\n2. Check to see whether all machines are free\n3. Report the number of busy machines\n4. Report the number of free machines\n5. Report the status of machine n\n6. Report the number of the first available machine\n7. Quit\n"

.ORIG xD000			; Remote data
BUSYNESS .FILL xABCD		; <----!!!VALUE FOR BUSYNESS VECTOR!!!

;---------------	
;END of PROGRAM
;---------------	
.END
