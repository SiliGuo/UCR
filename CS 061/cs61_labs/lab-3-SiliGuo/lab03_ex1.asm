;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 3
; Lab section: 023
; TA: Kenneth O'Neal
; 
;=================================================

;Direct memory addressing mode
;
.orig x3000				;Program starts here
	;-----------------
	;Instructions
	;-----------------
	LD R3, DEC_65			;Put the value #65 into R3
	LD R4, HEX_41			;Put the value x41 into R4

	HALT				;Sotp execution of program
	;-----------------
	;Data
	;-----------------
	DEC_65	.FILL	#65		;Put #65 in memory here
	HEX_41	.FILL	x41		;Put x41 in memory here
.end					;Program ends here
