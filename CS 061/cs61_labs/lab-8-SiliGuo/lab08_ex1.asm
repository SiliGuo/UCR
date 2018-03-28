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

HALT

;-----------
;Local data
;-----------
START_ADDR		.FILL	x4000
SUB_GET_STRING_3200	.FILL	x3200

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

.END
