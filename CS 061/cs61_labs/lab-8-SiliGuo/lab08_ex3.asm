;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 8
; Lab section: 023
; TA: Kenneth O'Neal
;=================================================

.ORIG x3000
;------------
;Instruction
;------------
LD R0, START_ADDR			; Store start address as a parameter
LD R1, SUB_GET_STRING_3200		; R1 <-- x3200
JSRR R1					; Subroutine SUB_GET_STRING_3200
PUTS					; Output string

LD R0, START_ADDR
LD R1, SUB_TO_UPPER_3600
JSRR R1

LD R0, START_ADDR			; Store start address as a parameter
LD R1, SUB_IS_A_PALINDROME_3400		; R1 <-- x3400
JSRR R1					; Subroutine SUB_IS_A_PALINDROME_3400
HALT

;-----------
;Local data
;-----------
START_ADDR			.FILL	x4000
SUB_GET_STRING_3200		.FILL	x3200
SUB_IS_A_PALINDROME_3400	.FILL	x3400
SUB_TO_UPPER_3600		.FILL	x3600

;------------------------------------------------------------------------
;Subroutine: SUB_GET_STRING_3200
;Parameter (R0): The address of where to start storing the string
;Postcondition: The subroutine has allowed the user to input a string,
; 		terminated by the [ENTER] key, and has stored it in an
; 		array that starts at (R0) and is NULL-terminated.
;Return Value: R5 The number of non-sentinel characters read from the user
;------------------------------------------------------------------------

.ORIG x3200
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_3200		; Backup R0
	ST R1, BACKUP_R1_3200		; Backup R1
	ST R2, BACKUP_R2_3200		; Backup R2
	ST R3, BACKUP_R3_3200		; Backup R3
	ST R7, BACKUP_R7_3200		; Backup R7

;(2) Algrothim
LD R1, N_NEWLINE			; R1 <-- #-10
ADD R2, R0, #0				; R2 <-- R0 (Start address)
AND R5, R5, #0				; R5 <-- #0

INPUT_LOOP
	GETC				; Prompt input from user
	ADD R3, R0, R1			; R3 <-- R0 + R1
	BRz END_INPUT_LOOP		; if (R3 == 0) END_INPUT_LOOP
	
	ADD R5, R5, #1			; R5 <-- R5 + #1
	STR R0, R2, #0			; Mem[R2 + #0] <-- R0
	ADD R2, R2, #1			; R2 <-- R2 + #1
	BRnzp INPUT_LOOP		; Jump to INPUT_LOOP	
END_INPUT_LOOP

AND R0, R0, #0				; R0 <-- #0
STR R0, R2, #0				; Mem[R2 + #0] <-- R0

;(3) Restore registers
	LD R0, BACKUP_R0_3200		; Restore R0
	LD R1, BACKUP_R1_3200		; Restore R1
	LD R2, BACKUP_R2_3200		; Restore R2
	LD R3, BACKUP_R3_3200		; Restore R3
	LD R7, BACKUP_R7_3200		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_3200	.BLKW	#1
BACKUP_R1_3200	.BLKW	#1
BACKUP_R2_3200	.BLKW	#1
BACKUP_R3_3200	.BLKW	#1
BACKUP_R7_3200	.BLKW	#1
N_NEWLINE	.FILL	#-10		; #-10 stores here

;------------------------------------------------------------------------
;Subroutine: SUB_IS_A_PALINDROME_3400
;Parameter (R0): The address of a string
;Parameter (R5): The number of characters in the array
;Postcondition: The subroutine has determined whether the string at (R0)
;		is a palindrome or not, and returned a flag to that effect.
;Return Value: R4 {1 if the string is a palindrome, 0 otherwise}
;------------------------------------------------------------------------

.ORIG x3400
;------------------------
;Subroutine Instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_3400		; Backup R0
	ST R1, BACKUP_R1_3400		; Backup R1
	ST R2, BACKUP_R2_3400		; Backup R2
	ST R3, BACKUP_R3_3400		; Backup R3
	ST R5, BACKUP_R5_3400		; Backup R5
	ST R6, BACKUP_R6_3400		; Backup R6
	ST R7, BACKUP_R7_3400		; Backup R7

;(2) Algorithm
AND R4, R4, #0				; R4 <-- #0
ADD R1, R5, #-1				; R1 <-- R5 - #1
BRz SET_PALINDROME			; if (R1 == 0) SET_PALINDROME

ADD R1, R0, R5				; R1 <-- R0 + R5
ADD R1, R1, #-1				; R1 <-- R1 - #1

ADD R2, R5, #0				; R2 <-- R5
AND R5, R5, #0				; R5 <-- #0
DIVIDE_BY_TWO				; R5 <-- R5 / 2
	ADD R5, R5, #1
	ADD R2, R2, #-2
	BRzp DIVIDE_BY_TWO
ADD R5, R5, #-1

CHECK_PALINDROME
	LDR R2, R0, #0			; R2 <-- Mem[R0 + #0]
	LDR R3, R1, #0			; R3 <-- Mem[R1 + #0]

	NOT R3, R3			; R3 <-- 2's complement
	ADD R3, R3, #1

	ADD R6, R2, R3			; R6 <-- R2 + R3
	BRnp NOT_PALINDROME		; if (R6 != 0) NOT_PALINDROME

	ADD R0, R0, #1			; R0 <-- R0 + #1
	ADD R1, R1, #-1			; R1 <-- R1 - #1
	ADD R5, R5, #-1			; R5 <-- R5 - #1
	BRp CHECK_PALINDROME		; if (R5 > 0) CHECK_PALINDROME

SET_PALINDROME
	ADD R4, R4, #1			; R4 <-- R4 + #1
NOT_PALINDROME

;(3) Restore registers
	LD R0, BACKUP_R0_3400		; Restore R0
	LD R1, BACKUP_R1_3400		; Restore R1
	LD R2, BACKUP_R2_3400		; Restore R2
	LD R3, BACKUP_R3_3400		; Restore R3
	LD R5, BACKUP_R5_3400		; Restore R5
	LD R6, BACKUP_R6_3400		; Restore R6
	LD R7, BACKUP_R7_3400		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_3400	.BLKW	#1
BACKUP_R1_3400	.BLKW	#1
BACKUP_R2_3400	.BLKW	#1
BACKUP_R3_3400	.BLKW	#1
BACKUP_R5_3400	.BLKW	#1
BACKUP_R6_3400	.BLKW	#1
BACKUP_R7_3400	.BLKW	#1
DEC_32		.FILL	#32
N_DEC_32	.FILL	#-32

;------------------------------------------------------------------------
;Subroutine: SUB_TO_UPPER_3600
;Parameter (R0): Starting address of a null-terminated string
;Postcondition: The subroutine has converted the string to upper-case 
;		in-place; i.e. the upper-case string has replaced the
;               original string
;Return Value: None
;------------------------------------------------------------------------

.ORIG x3600
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_3600		; Backup R0
	ST R1, BACKUP_R1_3600		; Backup R1
	ST R2, BACKUP_R2_3600		; Backup R2
	ST R5, BACKUP_R5_3600		; Backup R5
	ST R7, BACKUP_R7_3600		; Backup R7

;(2) Algorithm
CAPITAL_LOOP
	LDR R1, R0, #0			; R1 <-- Mem[R0 + #0]
	
	LD R2, N_DEC_97			; R2 <-- #-97
	ADD R2, R1, R2			; R2 <-- R1 + R2
	BRn CAPITAL			; if (R2 < 0) CAPITAL
	LD R2, N_DEC_122		; R2 <-- #-122
	ADD R2, R1, R2			; R2 <-- R1 + R2
	BRp CAPITAL			; if (R2 > 0) CAPITAL

	LD R2, N_DEC_32_3600		; R2 <-- #-32
	ADD R1, R1, R2			; R1 <-- R1 + R2
	STR R1, R0, #0			; Mem[R0 + #0] <-- R1

CAPITAL
	ADD R0, R0, #1			; R0 <-- R0 + #1
	ADD R5, R5, #-1			; R5 <-- R5 - #1
	BRp CAPITAL_LOOP		; if (R5 > 0) CAPITAL_LOOP

;(3) Restore registers
	LD R0, BACKUP_R0_3600		; Restore R0
	LD R1, BACKUP_R1_3600		; Restore R1
	LD R2, BACKUP_R2_3600		; Restore R2
	LD R5, BACKUP_R5_3600		; Restore R5
	LD R7, BACKUP_R7_3600		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_3600	.BLKW	#1
BACKUP_R1_3600	.BLKW	#1
BACKUP_R2_3600	.BLKW	#1
BACKUP_R5_3600	.BLKW	#1
BACKUP_R7_3600	.BLKW	#1
N_DEC_97	.FILL	#-97
N_DEC_122	.FILL	#-122
N_DEC_32_3600	.FILL	#-32
.END
