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
;Array_1
;
.ORIG x3000				; Program starts here
	;--------------
	;Instructions
	;--------------
	LEA R0, MSG
	PUTS				; Output message

	LD R1, DEC_10			; R1 <-- #10
	LEA R2, ARRAY_1			; R2 <-- MEM[ARRAY_1]
	
	DO_WHILE_LOOP			; Loop for input
		GETC			; Prompt the input
		OUT			; Output the input char
		STR R0, R2, #0		; MEM[R2 + #0] <-- R0
		LD R0, SPACE		; R0 <-- SPACE
		OUT			; Output space char
		ADD R2, R2, #1		; R2 <-- R2 + #1
		ADD R1, R1, #-1		; R1 <-- R1 - #1
		BRp DO_WHILE_LOOP	; if (R1 > 0), DO_WHILE_LOOP
	
	HALT
	;--------------
	;Local data
	;---------------
	MSG	.STRINGZ	"ENTER 10 characters in console: \n"
	ARRAY_1	.BLKW		#10	; Reserve 10 spaces for ARRAY_1
	DEC_10	.FILL		#10	; #10 store here
	SPACE	.FILL		x20	; " " store here

.END					;Program ends here
