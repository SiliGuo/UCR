;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 5
; Lab section: 023
; TA: Kenneth O'Neal
; 5;=================================================

;
;Power of 2 Calculation
;
.ORIG x3000				; Program starts here
;----------------
;Instruction
;----------------
LD R1, ADDR_1				; R1 <-- MEM[ADDR_1]
LD R0, DEC_1				; R0 <-- #0
LD R3, DEC_10				; R3 <-- #10

;-------------------------
;Store 2^0 ~ 2^9 in array
;-------------------------
DO_WHILE_LOOP
	STR R0, R1, #0			; MEM[R1 + #0] <-- R0
	ADD R0, R0, R0			; R0 <-- R0 + R0
	ADD R1, R1, #1			; R1 <-- R1 + #1
	ADD R3, R3, #-1			; R3 <-- R3 - #1
	BRp DO_WHILE_LOOP		; if (R3 > 0) DO_WHILE_LOOP

;----------------------------------------
;Output each elements in array in binary
;----------------------------------------
LD R1, ADDR_1				; R1 <-- MEM[ADDR_1]
LD R3, DEC_10				; R3 <-- #10

ARRAY_LOOP
	LD R4, DEC_16			; R4 <-- #16
	LDR R2, R1, #0			; R2 <-- MEM[R1 + #0]
	LD R0, ASC_b			; R0 <-- 'b'
	OUT				; Output value in R0

	OUTPUT_LOOP
		ADD R2, R2, #0		; R2 <-- R2 + #0
		BRp OUTPUT_ZERO		; if (R2 > 0) Output '0'
		BRn OUTPUT_ONE		; if (R2 < 0) Output '1'

		OUTPUT_ZERO		; Output '0'
			LD R0, ZERO
			OUT
			BRnzp LOOP_1

		OUTPUT_ONE		; Output '1'
			LD R0, ONE
			OUT
		LOOP_1
		ADD R5, R4, #-13	; Output a ' ' when count to 13
		BRz OUTPUT_SPACE
		ADD R5, R4, #-9		; Output a ' ' when count to 9
		BRz OUTPUT_SPACE
		ADD R5, R4, #-5		; Output a ' ' when count to 5
		BRz OUTPUT_SPACE
		BRnp LOOP_2		; Jump back to loop
	
		OUTPUT_SPACE		; Output a ' '
			LD R0, SPACE
			OUT	
		
		LOOP_2
		ADD R2, R2, R2		; R2 <-- R2 + R2
		ADD R4, R4, #-1		; R4 <-- R4 - #1
		BRp OUTPUT_LOOP		; if(R4 > 0) OUTPUT_LOOP
	
	ADD R6, R3, #-1			; R6 <-- R3 - #1
	BRz END_ARRAY_LOOP		; if (R6 == 0) END_ARRAY_LOOP
	
	ADD R1, R1, #1			; R1 <-- R1 + #1
	LD R0, NEWLINE			; R0 <-- NEWLINE
	OUT				; Output NEWLINE

	ADD R3, R3, #-1			; R3 <-- R3 -#1
	BRp ARRAY_LOOP			; if (R3 > 0) ARRAY_LOOP
END_ARRAY_LOOP
		
HALT
;----------------
;Data
;----------------
ADDR_1	.FILL	x4000			; Array address(x4000) stores here
DEC_1	.FILL	#1			; 2^0 == #1 stores here
DEC_10	.FILL	#10			; #10 stores here
ZERO	.FILL	x30			; '0' stores here
ONE	.FILL	x31			; '1' stores here
DEC_16	.FILL	#16			; #16 stores here
ASC_b	.FILL	x62			; 'b' stores here
SPACE	.FILL	x20			; ' ' stores here
NEWLINE	.FILL	x0A			; '\n' stores here

.ORIG x4000
ARRAY_1	.BLKW	#10			; Reserve 10 spaces for ARRAY_1

.END					; Program ends here
