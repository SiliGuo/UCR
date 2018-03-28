;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 6
; Lab section: 023
; TA: Kenneth O'Neal
;=================================================

;
;Subroutine for read
;
.ORIG x3000				; Program starts here
;----------------
;Instruction
;----------------
LEA R0, MSG
PUTS					; Output message

JSR SUB_READ_BINARY_3400		; Read binary input and store in R2

JSR SUB_PRINT_BINARY_3200		; Print binary number
HALT

;----------------
;Data
;----------------

MSG	.STRINGZ	"Please enter a 16-bit binary number followed by letter 'b' (e.g. b1010011000011100):\n"

;------------------------------------------------------------------------
;Subroutine: SUB_PRINT_BINARY_3200
;Parameter (R0): Output the binary number in format
;	   (R2): Store the number for output in binary
;	   (R4): Count for 16 digits
;	   (R5): Check bit for when to output a space
;Postcondition: The subroutine output the number stores in R2 in 16-bit
;		binary with format 'bxxxx xxxx xxxx xxxx'
;Return Value: None
;------------------------------------------------------------------------

.ORIG x3200
;------------------------
;Subroutine instructions
;------------------------
;(1) Back up R7 & any registers the subroutine changes except Return Values
SUB_PRINT_BINARY_3200
	ST R0, BACKUP_R0_3200		; Backup R0
	ST R2, BACKUP_R2_3200		; Backup R2
	ST R4, BACKUP_R4_3200		; Backup R4
	ST R5, BACKUP_R5_3200		; Backup R5
	ST R7, BACKUP_R7_3200		; Backup R7

;(2) Subroutine's algorithm
LD R4, DEC_16_S				; R4 <-- #16

LD R0, ASC_b				; R0 <-- 'b'
OUT					; Output value in R0

OUTPUT_LOOP
	ADD R2, R2, #0			; R2 <-- R2 + #0
	BRzp OUTPUT_ZERO		; if (R2 > 0) Output '0'
	BRn OUTPUT_ONE			; if (R2 < 0) Output '1'

	OUTPUT_ZERO			; Output '0'
		LD R0, ZERO
		OUT
		BRnzp LOOP_1

	OUTPUT_ONE			; Output '1'
		LD R0, ONE
		OUT
	LOOP_1
	ADD R5, R4, #-13		; Output a ' ' when count to 13
	BRz OUTPUT_SPACE
	ADD R5, R4, #-9			; Output a ' ' when count to 9
	BRz OUTPUT_SPACE
	ADD R5, R4, #-5			; Output a ' ' when count to 5
	BRz OUTPUT_SPACE
	BRnp LOOP_2			; Jump back to loop

	OUTPUT_SPACE			; Output a ' '
		LD R0, SPACE
		OUT	
	
	LOOP_2
	ADD R2, R2, R2			; R2 <-- R2 + R2
	ADD R4, R4, #-1			; R4 <-- R4 - #1
	BRp OUTPUT_LOOP			; if(R4 > 0) OUTPUT_LOOP

;(3) Restore registers
	LD R0, BACKUP_R0_3200		; Restore R0
	LD R2, BACKUP_R2_3200		; Restore R2
	LD R4, BACKUP_R4_3200		; Restore R4
	LD R5, BACKUP_R5_3200		; Restore R5
	LD R7, BACKUP_R7_3200		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_3200	.BLKW	#1		
BACKUP_R2_3200	.BLKW	#1
BACKUP_R4_3200	.BLKW	#1
BACKUP_R5_3200	.BLKW	#1
BACKUP_R7_3200	.BLKW	#1
DEC_16_S	.FILL	#16		; #16 stores here
ZERO		.FILL	x30		; '0' stores here
ONE		.FILL	x31		; '1' stores here
ASC_b		.FILL	x62		; 'b' stores here
SPACE		.FILL	x20		; ' ' stores here

;---------------------------------------------------------------------------
;Subroutine 2: SUB_READ_BINARY_3400
;Parameter (R0): Get the digit that user input
;	   (R1): Count for 16 digits
;	   (R3): Check digit for if input is valid
;	   (R4): Check digit for if input is valid
;Postcondition: Only accept user to input in format 'bxxxx xxxx xxxx xxxx',
;		x can be 0 or 1; any difference will casue an error. 
;Return Value: R2
;---------------------------------------------------------------------------

.ORIG x3400
SUB_READ_BINARY_3400
;(1) Backup registers
	ST R0, BACKUP_R0_3400		; Backup R0
	ST R1, BACKUP_R1_3400		; Backup R1
	ST R3, BACKUP_R3_3400		; Backup R3
	ST R4, BACKUP_R4_3400		; Backup R4
	ST R7, BACKUP_R7_3400		; Backup R7

;(2) Algorithm
	GETC				;Get the letter 'b' and ignore
	LD R1, DEC_16			; R1 <-- #16
	LD R3, N_ZERO			; R3 <-- #-48

	INPUT_LOOP
		GETC			; Get the input 0 or 1
		ADD R2, R2, R2		; R2 <-- R2 + R2
		ADD R4, R0, R3		; R4 <-- R0 + R3
		BRz ADD_ZERO		; if (R4 == 0) ADD_ZERO
		BRnp ADD_ONE		; if (R4 != 0) ADD_ONE

		ADD_ZERO
			ADD R2, R2, #0	; R2 <-- R2 + #0
			BRnzp JUMP_1	; Jump to JUMP_1
		ADD_ONE
			ADD R2, R2, #1	; R2 <-- R2 + #1

		JUMP_1
		ADD R1, R1, #-1		; R1 <-- R1 - #1
		BRp INPUT_LOOP		; if (R1 > 0) INPUT_LOOP

;(3) Restore register
	LD R0, BACKUP_R0_3400		; Restore R0
	LD R1, BACKUP_R1_3400		; Restore R1
	LD R3, BACKUP_R3_3400		; Restore R3
	LD R4, BACKUP_R4_3400		; Restore R4
	LD R7, BACKUP_R7_3400		; Restore R7

;(4) Return
	RET
;----------------
;Subroutine data
;----------------
BACKUP_R0_3400	.BLKW	#1		
BACKUP_R1_3400	.BLKW	#1
BACKUP_R3_3400	.BLKW	#1
BACKUP_R4_3400	.BLKW	#1
BACKUP_R7_3400	.BLKW	#1
DEC_16		.FILL	#16		; #16 stores here
N_ZERO		.FILL	#-48		; #-48 stores here

.END					; Program ends here
