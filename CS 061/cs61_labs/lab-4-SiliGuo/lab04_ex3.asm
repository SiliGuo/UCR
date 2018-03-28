;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 4
; Lab section: 023
; TA: Kenneth O'Neal
; 
;=================================================

;
;Array_2
;
.ORIG x3000				; Program starts here
	;-------------------------------
	;Instructions
	;-------------------------------
	LEA R0, MSG
	PUTS				; Output message

	LD R1, DEC_10			; R1 <-- #10
	LEA R2, ARRAY_1			; R2 <-- MEM[ARRAY_1]
	;-------------------------------
	;Loop for input
	;-------------------------------
	INPUT_LOOP			; Loop for input
		GETC			; Prompt the input
		STR R0, R2, #0		; MEM[R2 + #0] <-- R0
		ADD R2, R2, #1		; R2 <-- R2 + #1
		ADD R1, R1, #-1		; R1 <-- R1 - #1
		BRp INPUT_LOOP		; if (R1 > 0), INPUT_LOOP

	LD R1, DEC_10			; R1 <-- #10
	LEA R2, ARRAY_1			; R2 <-- MEM[ARRAY_1]
	;-------------------------------
	;Loop for output
	;-------------------------------
	OUTPUT_LOOP			; Loop for output
		LDR R0, R2, #0		; R0 <-- R2 + #0
		OUT			; Output the value stored in R0
		LD R0, NEWLINE		; R0 <-- NEWLINE
		OUT			; Output NEWLINE
		ADD R2, R2, #1		; R2 <-- R2 + #1
		ADD R1, R1, #-1		; R1 <-- R1 + #1
		BRp OUTPUT_LOOP		; if (R1 >0), OUTPUT_LOOP
	
	HALT
	;--------------
	;Local data
	;---------------
	MSG	.STRINGZ	"ENTER 10 characters in console: \n"
	ARRAY_1	.BLKW		#10	; Reserve 10 spaces for ARRAY_1
	DEC_10	.FILL		#10	; #10 store here
	NEWLINE	.FILL		x0A	; "\n" store here

.END					;Program ends here
