;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 4
; Lab section: 023
; TA: Kenneth O'Neal
; 
;=================================================

;Indirect memory addressing mode
;
.ORIG x3000				; Program starts here
	;-----------------
	;Instructions
	;-----------------
	LD R5, DATA_PTR			; R5 <-- x4000

	LDR R3, R5, #0			; R3 <-- MEM[R5 + #0] == #65
	LDR R4, R5, #1			; R4 <-- MEM[R6 + #1] == x41

	ADD R3, R3, #1			; R3 <-- R3 + #1
	ADD R4, R4, #1			; R4 <-- R4 + #1

	STR R3, R5, #0			; MEM[R5 + #0] == MEM[x4000] <-- R3
	STR R4, R5, #1			; MEM[R6 + #0] == MEM[x4001] <-- R4

	HALT				; Sotp execution of program
	;-----------------
	;Data
	;-----------------
	DATA_PTR	.FILL	x4000	; Put x4000 in memory here
	;-----------------
	;Remote data
	;-----------------
.ORIG x4000
	NEW_DEC_65	.FILL	#65	; Put #65 in memory here
	NEW_HEX_41	.FILL	x41	; Put x41 in memory here
.END					; Program ends here