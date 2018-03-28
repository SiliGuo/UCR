;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Assignment name: Assignment 2
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

;----------------------------------------------
;outputs prompt
;----------------------------------------------	
LEA R0, intro			; 
PUTS				; Invokes BIOS routine to output string

;-------------------------------
;INSERT CODE STARTING FROM HERE
;-------------------------------
;Prompt the input
;-------------------------------
GETC				; aka: Trap x20, prompt the 1st number
ADD R1, R0, #0			; R1 <- R0 + #0
OUT				; Output the number (in R0)
LD R0, NEWLINE			
OUT				; Go to next line
GETC				; Prompt the 2nd number
ADD R2, R0, #0			; R2 <- R0 + #0
OUT				; Output the nubmer (in R0)
LD R0, NEWLINE			
OUT				; Go to next line

;-------------------------------
;Output equation
;-------------------------------
ADD R0, R1, #0			; R0 <- R1 + #0
OUT
LEA R0, MINUS
PUTS				; Output minus sign
ADD R0, R2, #0			; R0 <- R1 + #0
OUT
LEA R0, EQUAL
PUTS				; Output equal sign

;-------------------------------
;Do the calculation
;-------------------------------
LD R4, STR_NUM			;#48 stores here
ADD R1, R1, R4
ADD R2, R2, R4			;Converting strings to real numbers

NOT R2, R2
ADD R2, R2, #1			; 2's complement

ADD R3, R1, R2			; R3 <- R1 + R2
BRn CONVERT			; if (R3 < 0), convert to "+" befroe output

;-------------------------------
;Output
;-------------------------------
LD R4, NUM_STR
ADD R3, R3, R4			; R3 <- R3 + R4 == R3 + #48
				; Converting # to ASCII code
ADD R0, R3, #0			; R0 <- R3 + #0
OUT				; Outpur result
LD R0, NEWLINE
OUT				; Output NEWLINE

HALT
;-------------------------------
;if (R3 < 0)
;-------------------------------
CONVERT
	ADD R3, R3, #-1
	NOT R3, R3		; Back of 2's complement
	LD R0, NEGATIVE
	OUT			; Output negative sign

	LD R4, NUM_STR
	ADD R3, R3, R4		; R3 <- R3 + R4 == R3 + #48
				; Converting # to ASCII code
	ADD R0, R3, #0		; R0 <- R3 + #0
	OUT			; Outpur result
	LD R0, NEWLINE
	OUT			; Output NEWLINE
HALT				; Stop execution of program
;------	
;Data
;------
; String to explain what to input 
intro	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 
NEWLINE	.FILL	 	x0A	; String that holds the newline character
MINUS	.STRINGZ	" - "	; String that holds the minus sign
EQUAL	.STRINGZ	" = "	; String that holds the equal sign
NUM_STR	.FILL		#48	; #48 stores here for conversion
STR_NUM	.FILL		#-48	; #-48 stores here
NEGATIVE	.Fill	x2D	;"-" stores here

;---------------	
;END of PROGRAM
;---------------	
.END

