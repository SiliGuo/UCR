;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Assignment name: Assignment 3
; Lab section: 023
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Convert_addr		; R6 <-- Address pointer for Convert
LDR R1, R6, #0			; R1 <-- VARIABLE Convert 
;-------------------------------
;INSERT CODE STARTING FROM HERE
;-------------------------------
LD R2, DEC_16			; R2 <-- #16
LD R3, MSB_SET			; R3 <-- x8000

DO_WHILE_LOOP
	AND R4, R1, R3		; AND with x8000, set all bits to #0,
				; except MSB
	BRz OUTPUT_ZERO		; if (R4 == 0) output a '0'
	BRnp OUTPUT_ONE		; if (R4 != 0) output a '1'
	
	OUTPUT_ZERO		; Output a '0'
		LD R0, ZERO
		OUT
		BRnzp LOOP_1	; Jump back to the loop

	OUTPUT_ONE		; Output a '1'
		LD R0, ONE
		OUT
	
	LOOP_1
	ADD R5, R2, #-13	; Output a ' ' when count to 13
	BRz OUTPUT_SPACE
	ADD R5, R2, #-9		; Output a ' ' when count to 9
	BRz OUTPUT_SPACE
	ADD R5, R2, #-5		; Output a ' ' when count to 5
	BRz OUTPUT_SPACE
	BRnp LOOP_2		; Jump back to loop

	OUTPUT_SPACE		; Output a ' '
		LD R0, SPACE
		OUT
	
	LOOP_2
	ADD R1, R1, R1		; R1 <-- R1 + R1,
				; same as shift to the left
	ADD R2, R2, #-1		; R2 <-- r2 - #1
	BRp DO_WHILE_LOOP	; if (R2 >0) DO_WHILE_LOOP	
	
	LD R0, NEWLINE		; Output a NEWLINE
	OUT
HALT
;---------------	
;Data
;---------------
Convert_addr	.FILL	xD000	; The address of where to find the data
DEC_16		.FILL	#16
MSB_SET		.FILL	x8000
ZERO		.FILL	x30
ONE		.FILL	x31
SPACE		.FILL	x20
NEWLINE		.FILL	x0A
 
.ORIG xD000			; Remote data
Convert .FILL xABCD		; <----!!!NUMBER TO BE CONVERTED TO BINARY!!!
;---------------	
;END of PROGRAM
;---------------	
.END
