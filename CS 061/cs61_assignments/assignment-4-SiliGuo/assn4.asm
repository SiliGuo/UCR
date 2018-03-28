;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Assignment name: Assignment 4
; Lab section: 023
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------------------------
;INSERT CODE STARTING FROM HERE 
;--------------------------------
AND R5, R5, #0			; R5 <-- #0
JSR SUB_READ_3200		; Jump to subroutine

HALT

;------------------------------------------------------------------------
;Subroutine: SUB_READ_3200
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
SUB_READ_3200
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
;---------------
;END of PROGRAM
;---------------
.END
