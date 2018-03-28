;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 7
; Lab section: 023
; TA: Kenneth O'Neal
;=================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------

AND R5, R5, #0			; R5 <-- #0
LD R1, SUB_READ_DECIMAL_3200
JSRR R1				; Jump to subroutine 1

ADD R5, R5, #1
LD R2, SUB_PRINT_DECIMAL_3400
JSRR R2				; Jump to subroutine 2

HALT

;-----------
;Local data
;-----------
SUB_READ_DECIMAL_3200	.FILL	x3200
SUB_PRINT_DECIMAL_3400	.FILL	x3400
;------------------------------------------------------------------------
;Subroutine: SUB_READ_DECIMAL_3200
;Parameter (R0): Prompt input and output the input value
;	   (R1): Count loop times in MULTI_TEN loop
;	   (R2): Store the number for transfering number from ASCII code
;	   (R4): Check bit for input
;	   (R6): Mark as #1 if the number is negative
;Postcondition: The subroutine prompt from user input, output what user
;		typed on keyboard, and check for invalidation; it finally
;		store the valid vaule in R5
;Return Value: R5
;------------------------------------------------------------------------

.ORIG x3200				; Subroutine begins here
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_3200		; Backup R0
	ST R1, BACKUP_R1_3200		; Backup R1
	ST R2, BACKUP_R2_3200		; Backup R2
	ST R3, BACKUP_R3_3200		; Backup R3
	ST R4, BACKUP_R4_3200		; Backup R4
	ST R6, BACKUP_R6_3200		; Backup R6
	ST R7, BACKUP_R7_3200		; Backup R7

;(2) Algorithm
LD R0, introMessage			; Output Intro Message
PUTS

LD R2, N_DEC_48				; R2 <-- #-48
LD R3, N_NEWLINE			; R3 <-- #-10

SIGN_CHECK
	GETC				; Prompt input

	ADD R4, R0, R3			; Check for '\n'
	BRz ERROR			; if input a '\n', END_INPUT_LOOP
	OUT				; Output

	LD R4, N_POS			; Check for '+'
	ADD R4, R0, R4
	BRz SECOND_CHECK		; if input a '+', INPUT_LOOP

	LD R4, N_NEG			; Check for '-'
	ADD R4, R0, R4
	BRz MARK_NEG			; if input a '-', MARK_NEG
	BRnp ERROR_CHECK		; else, ERROR_CHECK

MARK_NEG				; if input a '-', set R6 <-- #1
	ADD R6, R6, #1
SECOND_CHECK
	GETC
	ADD R4, R0, R3
	BRz NEED_NEWLINE
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
	BRnz CONTINUE			; No error, continue

NEED_NEWLINE
	LD R0, NEWLINE			; Output NEWLINE
	OUT
	AND R6, R6, #0
ERROR
	ADD R4, R0, R3			; Check for '\n'
	BRz NOT_OUTPUT			; if input a '\n', NOT_OUTPUT
	LD R0, NEWLINE			; Output NEWLINE
	OUT
NOT_OUTPUT
	LD R0, errorMessage  		; Output Error Message
	PUTS
	LD R0, introMessage		; Output Intro Message
	PUTS
	AND R5, R5, #0			; R5 <-- #0
	BRz SIGN_CHECK			; Jump to SIGN_CHECK
	
CONTINUE
	LD R1, DEC_9			; R1 <-- #9
	ADD R4, R5, #0			; R4 <-- R5
	MULTI_TEN			; R5 <-- 10 * R5
		ADD R5, R4, R5
		ADD R1, R1, #-1
		BRp MULTI_TEN

	ADD R0,R0, R2			; Convert ASCII code to number
	ADD R5, R5, R0			; Calculate number store in R5
	BRnzp INPUT_LOOP		; Loop back to INPUT_LOOP
END_INPUT_LOOP
	
ADD R6, R6, #0				; Check for negative
BRz END_CONVERT				; if (R6 != 0) Convert to negative

CONVERT					; 2's complement
	NOT R5, R5
	ADD R5, R5, #1
END_CONVERT

LD R0, NEWLINE				; Output NEWLINE
OUT

;(3) Restore registers
	LD R0, BACKUP_R0_3200		; Restore R0
	LD R1, BACKUP_R1_3200		; Restore R1
	LD R2, BACKUP_R2_3200		; Restore R2
	LD R3, BACKUP_R3_3200		; Restore R3
	LD R4, BACKUP_R4_3200		; Restore R4
	LD R6, BACKUP_R6_3200		; Restore R6
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
BACKUP_R4_3200	.BLKW	#1
BACKUP_R6_3200	.BLKW	#1
BACKUP_R7_3200	.BLKW	#1
introMessage	.FILL	x6000		; Intro message address stores here
errorMessage	.FILL	x6100		; Error message address stores here
DEC_9		.FILL	#9		; #9 stores here
NEWLINE		.FILL	x0A		; '\n' soters here
N_DEC_48	.FILL	#-48		; #-48 stoers here
N_NEWLINE	.FILL	#-10		; #-10 stoers here
N_POS		.FILL	#-43		; #-43 stores here
N_NEG		.FILL	#-45		; #-45 stores here

;------------
;Remote data
;---------------
;messages
;---------------
.ORIG x6000
intro .STRINGZ	"Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"
;---------------
;error_messages
;---------------
.ORIG x6100	
error_mes .STRINGZ	"ERROR INVALID INPUT\n"

;------------------------------------------------------------------------
;Subroutine: SUB_PRINT_DECIMAL_3400
;Parameter (R0): Output the decimal value
;	   (R1): Count loop times in PRINT_LOOP
;	   (R2): Store the address of DIVIDER array
;	   (R4): Copy original number and do algorithm
;	   (R5): Store original number
;	   (R6): Mark as #1 after first non-zero digit prints out
;Postcondition: The subroutine use the number passed in to output in decimal
;Return Value: None
;------------------------------------------------------------------------

.ORIG x3400				; Subroutine begins here
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_3400		; Backup R0
	ST R1, BACKUP_R1_3400		; Backup R1
	ST R2, BACKUP_R2_3400		; Backup R2
	ST R3, BACKUP_R3_3400		; Backup R3
	ST R4, BACKUP_R4_3400		; Backup R4
	ST R5, BACKUP_R5_3400		; Backup R5
	ST R6, BACKUP_R6_3400		; Backup R6
	ST R7, BACKUP_R7_3400		; Backup R7

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


ADD R5, R5, #0				; R5 <-- R5
BRz OUTPUT_ZERO
BRp POS_SIGN				; if (R5 >= 0) POS_SIGN
BRn NEG_SIGN				; if (R5 < 0) NEG_SIGN

OUTPUT_ZERO
	LD R0, DEC_48
	OUT
	BRnzp END
POS_SIGN
	LD R0, POS			; Print '+'
	OUT
	BRnzp END_SIGN_PRINT
NEG_SIGN				
	ADD R5, R5, #-1			; Get 2's complement number and
	NOT R5, R5			; store in R5
	LD R0, NEG			; Print '-'
	OUT
END_SIGN_PRINT

LD R1, DEC_5				; R1 <-- #5
LEA R2, DIVIDER				; R2 <-- DIVIDER
AND R6, R6, #0				; R6 <-- #0

PRINT_LOOP
	ADD R4, R5, #0			;R4 <-- R5
	AND R3, R3, #0			;R3 <-- #0
	LDR R0, R2, #0			;R0 <-- Mem[R2 + #0]

	COUNT_LOOP			; Count number and store in R3
		ADD R3, R3, #1
		ADD R4, R0, R4
		BRzp COUNT_LOOP

	ADD R3, R3, #-1			; R3 <-- R3 - #1 (Actual count)
	BRz OUTPUT
	LD R6, SIGN			; R6 <-- #1; set SIGN after first 
					; non-zero digit
OUTPUT
	ADD R6, R6, #0			; if SIGN is not set, print digit
	BRz END_OUTPUT
	LD R0, DEC_48
	ADD R0, R0, R3
	OUT
END_OUTPUT

	ADD R3, R3, #0			; Get new number for next loop
	BRz END_NEW_NUMBER_LOOP		; e.g. 12345 --> 2345
	NEW_NUMBER_LOOP
		LDR R0, R2, #0
		ADD R5, R0, R5
		ADD R3, R3, #-1
		BRp NEW_NUMBER_LOOP
	END_NEW_NUMBER_LOOP

	ADD R2, R2, #1			; R2 <-- R2 + #1
	ADD R1, R1, #-1			; R1 <-- R1 - #1
	BRp PRINT_LOOP			; if (R1 >0) PRINT_LOOP
END

;(3) Restore registers
	LD R0, BACKUP_R0_3400		; Restore R0
	LD R1, BACKUP_R1_3400		; Restore R1
	LD R2, BACKUP_R2_3400		; Restore R2
	LD R3, BACKUP_R3_3400		; Restore R3
	LD R4, BACKUP_R4_3400		; Restore R4
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
BACKUP_R4_3400	.BLKW	#1
BACKUP_R5_3400	.BLKW	#1
BACKUP_R6_3400	.BLKW	#1
BACKUP_R7_3400	.BLKW	#1
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
