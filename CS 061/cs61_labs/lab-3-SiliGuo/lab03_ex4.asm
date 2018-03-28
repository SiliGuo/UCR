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
	LD R0, HEX_61			;R0 <-- x61
	LD R1, HEX_1A			;R1 <-- x1A

	DO_WHILE_LOOP
		TRAP x21		;aka: OUT, output the contents of R0
		ADD R0, R0, #1		;R0 <-- R0 + #1
		ADD R1, R1, #-1		;R1 <-- R1 - #1
		BRp DO_WHILE_LOOP	;if (R1 > 0): goto DO_WHILE_LOOP
	END_DO_WHILE_LOOP

	HALT				;Sotp execution of program
	;-----------------
	;Data
	;-----------------
	HEX_61	.FILL	x61		;Put x61 in memory here
	HEX_1A	.FILL	x1A		;Put x1A in memory here
.end					;Program ends here
