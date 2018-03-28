;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 5
; Lab section: 023
; TA: Kenneth O'Neal
; 5;=================================================

;
;Output for ex-1
;
.ORIG x3000			; Program starts here
;----------------
;Instruction
;----------------
LD R1, ADDR_1			; R1 <-- MEM[ADDR_1]
LD R0, DEC_0			; R0 <-- #0

;-------------------
;Store 0~9 in array
;-------------------
DO_WHILE_LOOP
	STR R0, R1, #0		; MEM[R1 + #0] <-- R0
	ADD R0, R0, #1		; R0 <-- R0 + #1
	ADD R1, R1, #1		; R1 <-- R1 + #1
	ADD R3, R0, #-10	; R3 <-- R0 - #10
	BRnp DO_WHILE_LOOP	; if (R3 != 0) DO_WHILE_LOOP

;----------------------
;Store the 7th # in R2
;----------------------
LD R1, ADDR_1			; R1 <-- MEM[ADDR_1]
ADD R1, R1, #6			; R1 <-- R1 + #6
LDR R2, R1, #0			; R2 <-- MEM[R1 + #0]

;-----------------
;Output the array
;-----------------
LD R1, ADDR_1			; R1 <-- MEM[ADDR_1]
LD R4, DEC_10			; R4 <-- #10

OUTPUT_LOOP
	LDR R3, R1, #0		; R3 <-- MEM[R1 + #0]
	LD R0, DEC_48		; R0 <-- #48
	ADD R0, R0, R3		; R0 <-- R0 + R3
	OUT			; Output value in R0
	ADD R1, R1, #1		; R1 <-- R1 + #1
	ADD R4, R4, #-1		; R4 <-- R4 - #1
	BRp OUTPUT_LOOP		; if (R4 >0) OUTPUT_LOOP

HALT
;----------------
;Data
;----------------
ADDR_1	.FILL	x4000		; Array address(x4000) stores here
DEC_0	.FILL	#0		; #0 stores here
DEC_48	.FILL	#48		; #48 stores here
DEC_10	.FILL	#10		; #10 stores here

.ORIG x4000
ARRAY_1	.BLKW	#10		; Reserve 10 spaces for ARRAY_1

.END				; Program ends here
