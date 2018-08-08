;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 3
; Lab section: 023
; TA: Kenneth O'Neal
; 
;=================================================

;Indirect memory addressing mode
;
.orig x3000				;Program starts here
	;-----------------
	;Instructions
	;-----------------
	LDI R3, DEC_65_PTR		;R3 <-- MEM[MEM[DEC_65_PTR]]
	LDI R4, HEX_41_PTR		;R4 <-- MEM[MEM[HEX_41_PTR]]

	ADD R3, R3, #1			;R3 <-- R3 + #1
	ADD R4, R4, #1			;R4 <-- R4 + #1

	STI R3, DEC_65_PTR		;MEM[DEC_65_PTR] <-- R3
	STI R4, HEX_41_PTR		;MEM[HEX_41_PTR] <-- R4

	HALT				;Sotp execution of program
	;-----------------
	;Data
	;-----------------
	DEC_65_PTR	.FILL	x4000	;Put x4000 in memory here
	HEX_41_PTR	.FILL	x4001	;Put x4001 in memory here

	;-----------------
	;Remote data
	;-----------------
.orig x4000
	NEW_DEC_65	.FILL	#65	;Put #65 in memory here
	NEW_HEX_41	.FILL	x41	;Put x41 in memory here
.end					;Program ends here