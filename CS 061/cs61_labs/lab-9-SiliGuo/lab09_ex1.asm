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

LEA R0, INTRO				; Output intro message
PUTS

LD R2, DEC_6				; R2 <-- #6
PUSH_LOOP
	GETC				; prompt input for push
	OUT
	LD R1, SUB_STACK_PUSH_3200	; Subroutine SUB_STACK_PUSH_3200
	JSRR R1
	ADD R2, R2, #-1			; R2 <-- R2 - #1
	BRp PUSH_LOOP			; if (R2 > 0) PUSH_LOOP

HALT
;-----------
;Local data
;-----------
SUB_STACK_PUSH_3200	.FILL	x3200
BASE	.FILL	xA000
MAX	.FILL	xA005
DEC_6	.FILL	#6
INTRO	.STRINGZ	"Enter a single character:\n"

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
ADD R6, R6, #1				; ADD TOS with #1
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
OVERFLOW_MSG	.STRINGZ	"\nOverflow Error!\n"
.END
