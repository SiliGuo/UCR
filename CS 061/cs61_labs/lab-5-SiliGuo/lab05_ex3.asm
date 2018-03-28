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
.ORIG x3000			; Program starts here
;----------------
;Instruction
;----------------
LD R1, ADDR_1			; R1 <-- MEM[ADDR_1]
LD R0, DEC_1			; R0 <-- #0
LD R3, DEC_10			; R3 <-- #10

;-------------------------
;Store 2^0 ~ 2^9 in array
;-------------------------
DO_WHILE_LOOP
	STR R0, R1, #0		; MEM[R1 + #0] <-- R0
	ADD R0, R0, R0		; R0 <-- R0 + R0
	ADD R1, R1, #1		; R1 <-- R1 + #1
	ADD R3, R3, #-1		; R3 <-- R3 - #1
	BRp DO_WHILE_LOOP	; if (R3 > 0) DO_WHILE_LOOP

;----------------------
;Store the 7th # in R2
;----------------------
LD R1, ADDR_1			; R1 <-- MEM[ADDR_1]
ADD R1, R1, #6			; R1 <-- R1 + #6
LDR R2, R1, #0			; R2 <-- MEM[R1 + #0]

HALT
;----------------
;Data
;----------------
ADDR_1	.FILL	x4000		; Array address(x4000) stores here
DEC_1	.FILL	#1		; 2^0 == #1 stores here
DEC_10	.FILL	#10		; #10 stores here

.ORIG x4000
ARRAY_1	.BLKW	#10		; Reserve 10 spaces for ARRAY_1

.END				; Program ends here
