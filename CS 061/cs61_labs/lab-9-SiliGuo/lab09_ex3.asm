;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 9
; Lab section: 023
; TA: Kenneth O'Neal
;=================================================
.ORIG x3000
;-------------
;Instructions
;-------------
LD R4, BASE				; R4 <-- xA000
LD R5, MAX				; R5 <-- xA005
LD R6, BASE				; R6 <-- xA000

INPUT_1
	LEA R0, INTRO1			; Output intro message 1
	PUTS
	GETC				; Prompt for 1st input
	OUT
	LD R1, N_DEC_48			; Check if input is in 0~9
	ADD R1, R0, R1
	BRn ERROR1
	ADD R1, R1, #-9
	BRp ERROR1			; if not, ERROR1
	BRnzp END_INPUT_1		; Jump to END_INPUT_1
ERROR1
	LEA R0, ERR_MSG			; Output error message
	PUTS
	BRnzp INPUT_1			; Jump to INPUT_1
END_INPUT_1
LD R1, N_DEC_48				; Store actural # in R0
ADD R0, R0, R1
LD R1, SUB_STACK_PUSH_3200		; Subroutine SUB_STACK_PUSH_3200
JSRR R1
LD R0, NEWLINE				; Output NEWLINE
OUT

INPUT_2
	LEA R0, INTRO2			; Output intro message 2
	PUTS
	GETC				; Prompt for 2nd input
	OUT
	LD R1, N_DEC_48			; Check if input is in 0~9
	ADD R1, R0, R1
	BRn ERROR2
	ADD R1, R1, #-9
	BRp ERROR2			; if not, ERROR2
	BRnzp END_INPUT_2		; Jump to END_INPUT_2
ERROR2
	LEA R0, ERR_MSG			; Output error message
	PUTS
	BRnzp INPUT_2			; Jump to INPUT_2
END_INPUT_2
LD R1, N_DEC_48				; Store actural # in R0
ADD R0, R0, R1
LD R1, SUB_STACK_PUSH_3200		; Subroutine SUB_STACK_PUSH_3200
JSRR R1
LD R0, NEWLINE				; Outpur NEWLINE
OUT

INPUT_3
	LEA R0, INTRO3			; Output intro message 3
	PUTS
	GETC				; Prompt for the calculation symbol
	OUT
	LD R1, N_DEC_42			; Check if it is '*'
	ADD R1, R0, R1
	BRnp ERROR3			; if not, ERROR3
	BRnzp END_INPUT_3
ERROR3
	LEA R0, ERR_MSG			; Output error message
	PUTS
	BRnzp INPUT_3			; Jump to INPUT_3
END_INPUT_3
LD R0, NEWLINE				; Output NEWLINE
OUT

LD R1, SUB_RPN_MULTIPLY_3600		; Subroutine SUB_RPN_MULTIPLY_3600
JSRR R1

LEA R0, OUT_MSG				; Output output message
PUTS
LD R1, SUB_PRINT_DECIMAL_4000		; Subroutine SUB_PRINT_DECIMAL_4000
JSRR R1
LD R0, NEWLINE				; Output NEWLINE
OUT

HALT
;-----------
;Local data
;-----------
SUB_STACK_PUSH_3200	.FILL	x3200
SUB_RPN_MULTIPLY_3600	.FILL	x3600
SUB_PRINT_DECIMAL_4000	.FILL	x4000
BASE			.FILL	xA000
MAX			.FILL	xA005
NEWLINE			.FILL	x0A
N_DEC_48		.FILL	#-48
N_DEC_42		.FILL	#-42
INTRO1	.STRINGZ	"Please enter a single character number: "
INTRO2	.STRINGZ	"Please enter another single character number: "
INTRO3	.STRINGZ	"Please enter the operatino symbol(Only work for Multiplication): "
ERR_MSG	.STRINGZ	"\nInvalid Input Error!\n"
OUT_MSG	.STRINGZ	"The multiplication result is: "

;---------------------------------------------------------------------------
;Subroutine: SUB_STACK_PUSH_3200
; Parameter (R0): The value to push onto the stack
; Parameter (R4): BASE: A pointer to the base (one less than​ the lowest 
;		  available address) of the stack
; Parameter (R5): MAX: The "highest" available address in the stack
; Parameter (R6): TOS (Top of Stack): A pointer to the current top of the
;		  stack
; Postcondition: The subroutine has pushed (R0) onto the stack (i.e to 
;		 address TOS+1). If the stack was already full (TOS = MAX), 
;		 the subroutine has printed an overflow error message and 
;		 terminated.
; Return Value: R6 ← updated TOS
;---------------------------------------------------------------------------
.ORIG x3200
;(1) Backup registers
	ST R0, BACKUP_R0_3200
	ST R1, BACKUP_R1_3200
	ST R2, BACKUP_R2_3200
	ST R5, BACKUP_R5_3200
	ST R7, BACKUP_R7_3200
;(2) Algorithms
ADD R6, R6, #1				; ADD TOS with 1
NOT R1, R5				; R1 <-- -R5
ADD R1, R1, #1
ADD R2, R1, R6				; R2 <-- R1 + R6
BRnz NOT_OVERFLOW			; if (R2 <= 0) NOT_OVERFLOW

LEA R0, OVERFLOW_MSG			; Output overflow message
PUTS
ADD R6, R6, #-1				; R6 <-- R6 - #1
BRnzp END_PUSH				; Jump to END_PUSH


NOT_OVERFLOW
STR R0, R6, #0				; Mem[R6 + #0] <-- R0
END_PUSH

;(3) Restore registers
	LD R0, BACKUP_R0_3200
	LD R1, BACKUP_R1_3200
	LD R2, BACKUP_R2_3200
	LD R5, BACKUP_R5_3200
	LD R7, BACKUP_R7_3200
;(4) Return
	RET
;----------------
;Subroutine data
;----------------
BACKUP_R0_3200	.BLKW	#1
BACKUP_R1_3200	.BLKW	#1
BACKUP_R2_3200	.BLKW	#1
BACKUP_R5_3200	.BLKW	#1
BACKUP_R7_3200	.BLKW	#1
OVERFLOW_MSG	.STRINGZ	"Overflow Error!\n"

;---------------------------------------------------------------------------
; Subroutine: SUB_STACK_POP_3400
; Parameter (R4): BASE: A pointer to the base (one less than​ the lowest 
;		  available address) of the stack
; Parameter (R5): MAX: The "highest" available address in the stack
; Parameter (R6): TOS (Top of Stack): A pointer to the current top of the 
;		  stack
; Postcondition: The subroutine has popped MEM[top] off of the stack. If the 
;		 stack was already empty (TOS = BASE), the subroutine has 
;		 printed an underflow error message and terminated.
; Return Value: R0 ← value popped off of the stack
; 		R6 ← updated TOS
;---------------------------------------------------------------------------
.ORIG x3400
;(1) Backup registers
	ST R1, BACKUP_R1_3400
	ST R2, BACKUP_R2_3400
	ST R4, BACKUP_R4_3400
	ST R7, BACKUP_R7_3400
;(2) Algorithms
NOT R1, R4				; R1 <-- -R4
ADD R1, R1, #1
ADD R2, R1, R6				; R2 <-- R1 + R6
BRp NOT_UNDERFLOW			; if (R2 > 0) NOT_UNDERFLOW

LEA R0, UNDERFLOW_MSG			; Output underflow message
PUTS
AND R0, R0, #0				; Set R0 to #-1
ADD R0, R0, #-1				; R0 <-- R0 - #1
BRnzp END_POP				; Jump to END_POP

NOT_UNDERFLOW
LDR R0, R6, #0				; R0 <-- Mem[R6 + #0]
ADD R6, R6, #-1				; R6 <-- R6 - #1
END_POP

;(3) Restore registers
	LD R1, BACKUP_R1_3400
	LD R2, BACKUP_R2_3400
	LD R4, BACKUP_R4_3400
	LD R7, BACKUP_R7_3400
;(4) Return
	RET
;----------------
;Subroutine data
;----------------
BACKUP_R1_3400	.BLKW	#1
BACKUP_R2_3400	.BLKW	#1
BACKUP_R4_3400	.BLKW	#1
BACKUP_R7_3400	.BLKW	#1
UNDERFLOW_MSG	.STRINGZ	"Underflow Error!\n"

;---------------------------------------------------------------------------
; Subroutine: SUB_RPN_MULTIPLY_3600
; Parameter (R4): BASE: A pointer to the base (one less than​ the lowest 
;		  available address) of the stack
; Parameter (R5): MAX: The "highest" available address in the stack
; Parameter (R6): TOS (Top of Stack): A pointer to the current top of the 
;		  stack
; Postcondition: The subroutine has popped off the top two values of the 
;		 stack, multiplied them together, and pushed the resulting 
;		 value back onto the stack.
; Return Value: R6 ← updated top value
;---------------------------------------------------------------------------
.ORIG x3600
;(1) Backup registers
	ST R0, BACKUP_R0_3600
	ST R1, BACKUP_R1_3600
	ST R2, BACKUP_R2_3600
	ST R7, BACKUP_R7_3600

;(2) Algorithms
LD R2, SUB_STACK_POP_3400		; Subroutine SUB_STACK_POP_3400
JSRR R2
ADD R1, R0, #0				; R1 <-- R0

LD R2, SUB_STACK_POP_3400		; Subroutine SUB_STACK_POP_3400
JSRR R2

LD R2, SUB_MULTIPLY_3800		; Subroutine SUB_MULTIPLY_3800
JSRR R2

ADD R0, R2, #0				; R0 <-- R2
LD R2, SUB_STACK_PUSH_3200_PRN_MULTIPLY	; Subroutine 
JSRR R2					; SUB_STACK_PUSH_3200_PRN_MULTIPLY

ADD R6, R0, #0				; R6 <-- R0

;(3) Restore registers
	LD R0, BACKUP_R0_3600
	LD R1, BACKUP_R1_3600
	LD R2, BACKUP_R2_3600
	LD R7, BACKUP_R7_3600

;(4) Return
	RET
;----------------
;Subroutine data
;----------------
SUB_STACK_POP_3400			.FILL	x3400
SUB_STACK_PUSH_3200_PRN_MULTIPLY	.FILL	x3200
SUB_MULTIPLY_3800			.FILL	x3800
BACKUP_R0_3600	.BLKW	#1
BACKUP_R1_3600	.BLKW	#1
BACKUP_R2_3600	.BLKW	#1
BACKUP_R7_3600	.BLKW	#1

;---------------------------------------------------------------------------
; Subroutine: SUB_MULTIPLY_3800
; Parameter (R0): First number for multiplication
; Parameter (R1): Second number for multiplication
; Postcondition: The subroutine takes two number and do multiplication and 
;		 store the result
; Return Value: R2 ← result for multiplication
;---------------------------------------------------------------------------
.ORIG x3800
;(1) Backup registers
	ST R0, BACKUP_R0_3800
	ST R1, BACKUP_R1_3800
	ST R7, BACKUP_R7_3800

;(2) Algorithms
AND R2, R2, #0				; R2 <-- #0
ADD R1, R1, #0				; R1 <-- R1
BRz END_MULTIPLY			; if (R1 == 0) END_MULTIPLY

MULTIPLY_LOOP
	ADD R2, R0, R2			; R2 <-- R0 + R2
	ADD R1, R1, #-1			; R1 <-- R1 - #1
	BRp MULTIPLY_LOOP		; if (R1 > 0) MULTIPLY_LOOP
END_MULTIPLY
	
;(3) Restore registers
	LD R0, BACKUP_R0_3800
	LD R1, BACKUP_R1_3800
	LD R7, BACKUP_R7_3800

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_3800	.BLKW	#1
BACKUP_R1_3800	.BLKW	#1
BACKUP_R7_3800	.BLKW	#1

;------------------------------------------------------------------------
;Subroutine: SUB_PRINT_DECIMAL_4000
;Parameter (R6): Pass the value for printing
;Postcondition: The subroutine use the number passed in to output in decimal
;Return Value: None
;------------------------------------------------------------------------

.ORIG x4000				; Subroutine begins here
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_4000		; Backup R0
	ST R1, BACKUP_R1_4000		; Backup R1
	ST R2, BACKUP_R2_4000		; Backup R2
	ST R3, BACKUP_R3_4000		; Backup R3
	ST R4, BACKUP_R4_4000		; Backup R4
	ST R5, BACKUP_R5_4000		; Backup R5
	ST R6, BACKUP_R6_4000		; Backup R6
	ST R7, BACKUP_R7_4000		; Backup R7

;(2) Algorithm
LEA R1, DIVIDER				; Create array of 5 spaces
LD R2, TEN_THOUSAND			; Store -10000 in array
STR R2, R1, #0
ADD R1, R1, #1
LD R2, THOUSAND				; Store -1000 in array
STR R2, R1, #0
ADD R1, R1, #1
LD R2, HUNDRED				; Store -100 in array
STR R2, R1, #0
ADD R1, R1, #1
LD R2, TEN				; Store -10 in array
STR R2, R1, #0
ADD R1, R1, #1
LD R2, ONE				; Store -1 in array
STR R2, R1, #0
ADD R1, R1, #1


ADD R6, R6, #0				; R6 <-- R6
BRz OUTPUT_ZERO
BRp END_SIGN_PRINT			; if (R6 >= 0) END_SIGN_PRINT
BRn NEG_SIGN				; if (R6 < 0) NEG_SIGN

OUTPUT_ZERO
	LD R0, DEC_48
	OUT
	BRnzp END

NEG_SIGN				
	ADD R6, R6, #-1			; Get 2's complement number and
	NOT R6, R6			; store in R5
	LD R0, NEG			; Print '-'
	OUT
END_SIGN_PRINT

LD R1, DEC_5				; R1 <-- #5
LEA R2, DIVIDER				; R2 <-- DIVIDER
AND R5, R5, #0				; R5 <-- #0

PRINT_LOOP
	ADD R4, R6, #0			;R4 <-- R6
	AND R3, R3, #0			;R3 <-- #0
	LDR R0, R2, #0			;R0 <-- Mem[R2 + #0]

	COUNT_LOOP			; Count number and store in R3
		ADD R3, R3, #1
		ADD R4, R0, R4
		BRzp COUNT_LOOP

	ADD R3, R3, #-1			; R3 <-- R3 - #1 (Actual count)
	BRz OUTPUT
	LD R5, SIGN			; R5 <-- #1; set SIGN after first 
					; non-zero digit
OUTPUT
	ADD R5, R5, #0			; if SIGN is not set, print digit
	BRz END_OUTPUT
	LD R0, DEC_48
	ADD R0, R0, R3
	OUT
END_OUTPUT

	ADD R3, R3, #0			; Get new number for next loop
	BRz END_NEW_NUMBER_LOOP		; e.g. 12345 --> 2345
	NEW_NUMBER_LOOP
		LDR R0, R2, #0
		ADD R6, R0, R6
		ADD R3, R3, #-1
		BRp NEW_NUMBER_LOOP
	END_NEW_NUMBER_LOOP

	ADD R2, R2, #1			; R2 <-- R2 + #1
	ADD R1, R1, #-1			; R1 <-- R1 - #1
	BRp PRINT_LOOP			; if (R1 >0) PRINT_LOOP
END

;(3) Restore registers
	LD R0, BACKUP_R0_4000		; Restore R0
	LD R1, BACKUP_R1_4000		; Restore R1
	LD R2, BACKUP_R2_4000		; Restore R2
	LD R3, BACKUP_R3_4000		; Restore R3
	LD R4, BACKUP_R4_4000		; Restore R4
	LD R5, BACKUP_R5_4000		; Restore R5
	LD R6, BACKUP_R6_4000		; Restore R6
	LD R7, BACKUP_R7_4000		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_4000	.BLKW	#1
BACKUP_R1_4000	.BLKW	#1
BACKUP_R2_4000	.BLKW	#1
BACKUP_R3_4000	.BLKW	#1
BACKUP_R4_4000	.BLKW	#1
BACKUP_R5_4000	.BLKW	#1
BACKUP_R6_4000	.BLKW	#1
BACKUP_R7_4000	.BLKW	#1
POS		.FILL	#43
NEG		.FILL	#45
DEC_5		.FILL	#5
DIVIDER		.BLKW	#5
TEN_THOUSAND	.FILL	#-10000
THOUSAND	.FILL	#-1000
HUNDRED		.FILL	#-100
TEN		.FILL	#-10
ONE		.FILL	#-1
DEC_48		.FILL	#48
SIGN		.FILL	#1
.END
