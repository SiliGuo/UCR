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
;Lab 03 Riview
;
.orig x3000				;Program starts here
	;--------------
	;Instructions
	;--------------
	TRAP x20			;aka: GETC, R0 <-- ASCII[input char]
	TRAP x21			;aka: OUT, Echo the char just typed
					;to the console
	HALT
.end					;Program ends here
