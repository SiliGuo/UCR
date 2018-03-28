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

LD R2, DEC_5				; R2 <-- #5
PRE_LOOP
	ADD R6, R6, #1			; ADD TOS with #1
	ADD R3, R3, #1			; R3 <-- R3 + #1
	STR R3, R6, #0			; Mem[R6 + #0] <-- R3
	ADD R2, R2, #-1			; R2 <-- R2 - #1
	BRp PRE_LOOP			; if (R2 > 0) PRE_LOOP

LD R2, DEC_6				; R2 <-- #6
POP_LOOP
	LD R1, SUB_STACK_POP_3400	; Subroutine SUB_STACK_POP_3400
	JSRR R1
	ADD R1, R0, #1			; R1 <-- R0 + #1
	BRz NOT_OUTPUT			; if (R1 == 0) NOT_OUTPUT
	LD R3, DEC_48			; Output pop value
	ADD R0, R0, R3
	OUT
NOT_OUTPUT
	ADD R2, R2, #-1			; R2 <-- R2 - #1
	BRp POP_LOOP			; if (R2 > 0) POP_LOOP
HALT
;-----------
;Local data
;-----------
SUB_STACK_POP_3400	.FILL	x3400
BASE	.FILL	xA000
MAX	.FILL	xA005
DEC_48	.FILL	#48
DEC_5	.FILL	#5
DEC_6	.FILL	#6

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
; Return Value: R0 ← value popped off of the stack, -1 when underflow
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
UNDERFLOW_MSG	.STRINGZ	"\nUnderflow Error!\n"
.END
