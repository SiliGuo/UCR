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
;Array and sentinel controlled loop
;
.ORIG x3000				; Program starts here
	;-------------------------------
	;Instructions
	;-------------------------------
	LEA R0, MSG
	PUTS				; Output message
	LD R2, ADDR_1			; R2 <-- ADDR_1 == x4000
	;-------------------------------
	;Prompt the input
	;-------------------------------
	INPUT_LOOP			; Loop for input
		GETC			; Prompt the input
		STR R0, R2, #0		; MEM[R2 + #0] <-- R0
		ADD R2, R2, #1		; R2 <-- R2 + #1
		ADD R0, R0, #-10	; R0 <-- R0 - #10
		BRnp INPUT_LOOP		; if (R1 != 0), INPUT_LOOP

	LD R2, ADDR_1			; R2 <-- ADDR_1 == x4000
	;-------------------------------
	;Output until NEWLINE
	;-------------------------------
	OUTPUT_LOOP			; Loop for output
		LDR R0, R2, #0		; R0 <-- R2 + #0
		ADD R3, R0, #0		; R3 <-- R0 + #0
		ADD R3, R3, #-10	; R3 <-- R3 - #10
		BRz END_OUTPUT_LOOP	; if (R3 == 0) END_OUTPUT_LOOP
		OUT			; Output value stores in R0
		LD R0, SPACE		; R0 <-- ' '
		OUT			; Output SPACE
		ADD R2, R2, #1		; R2 <-- R2 + #1
		ADD R3, R3, #0		; R3 <-- R3 + #0
		BRnp OUTPUT_LOOP	; if (R3 != 0), OUTPUT_LOOP
	END_OUTPUT_LOOP
	
	HALT
	;--------------
	;Local data
	;---------------
	MSG	.STRINGZ	"ENTER no more than 100 characters in console: \n"
	SPACE	.FILL		x20	; " " store here
	ADDR_1	.FILL		x4000	; x4000 store here

.END					;Program ends here
