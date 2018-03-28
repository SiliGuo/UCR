;=================================================
; Name: Sili Guo
; Email: sguo006@ucr.edu
; 
; Lab: lab 7
; Lab section: 023
; TA: Kenneth O'Neal
;=================================================

.ORIG x3000
;------------
;Instruciton
;------------
GETC
ADD R1, R0, #0
LD R2, SUB_COUNT_ONE_3200
JSRR R2

HALT

;-----------
;Local data
;-----------
SUB_COUNT_ONE_3200	.FILL	x3200

;------------------------------------------------------------------------
;Subroutine: SUB_READ_DECIMAL_3200
;Parameter (R0): Print the count number
;	   (R1): Hold the ASCII digit input
;	   (R4): Count for 16 digits
;Postcondition: The subroutine count the number of 1's in binary of the 
;		value stored in R1, and store and print the count number 
;		in R3
;Return Value: R3
;------------------------------------------------------------------------

.ORIG x3200				; Subroutine begins here
;------------------------
;Subroutine instructions
;------------------------
;(1) Backup registers
	ST R0, BACKUP_R0_3200		; Backup R0
	ST R1, BACKUP_R1_3200		; Backup R1
	ST R4, BACKUP_R4_3200		; Backup R4
	ST R7, BACKUP_R7_3200		; Backup R7

;(2) Algorithm
AND R3, R3, #0				; R3 <-- #0
LD R4, DEC_16				; R4 <-- #16

COUNT_LOOP
	ADD R1, R1, #0
	BRzp NOT_COUNT			; if (R1 < 0) NOT_COUNT

	ADD R3, R3, #1			; R3 <-- R3 + #1; (counting process)
NOT_COUNT
	
	ADD R1, R1, R1			; R1 <-- R1 + R1; (left shift)
	ADD R4, R4, #-1			; R4 <-- R4 - #1
	BRp COUNT_LOOP			; if (R4 >0) COUNT_LOOP

LEA R0, MSG				; Print message
PUTS

LD R4, DEC_48				; Print value store in R3
ADD R0, R3, R4
OUT

;(3) Restore registers
	LD R0, BACKUP_R0_3200		; Restore R0
	LD R1, BACKUP_R1_3200		; Restore R1
	LD R4, BACKUP_R4_3200		; Restore R4
	LD R7, BACKUP_R7_3200		; Restore R7

;(4) Return
	RET

;----------------
;Subroutine data
;----------------
BACKUP_R0_3200	.BLKW	#1
BACKUP_R1_3200	.BLKW	#1
BACKUP_R4_3200	.BLKW	#1
BACKUP_R7_3200	.BLKW	#1
DEC_16		.FILL	#16
DEC_48		.FILL	#48
MSG	.STRINGZ	"The number of 1's is: "

.END
