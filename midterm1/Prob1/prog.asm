; Implement a program to find the nearest smaller (or equal) perfect square of a given positive number
; The input will be stored in R2 and output (the nearest perfect square) should be stored in R3
; TODO: Write a subroutine called "PSquare" which returns the nearest perfect square of a given input and 
;       you must invoke this subroutine in the main part.
; Note : R2, R4, R5 and R6 must be left unchanged in PSquare.
;
; 
; PSquare :  input is stored in R2
;            output is stored in R3

.ORIG	x3000		; starting address is x3000

;;YOUR CODE STARTS HERE

; register use:
; R2 - input
; R3 - the nearest perfect square
; R4 - 2s complement of R2
; R0 - counter "n"
; R1 - n^2
PSquare
	ST  R4, saveR4
	ST  R5, saveR5
	ST  R6, saveR6
	AND R0, R0, #0
	AND R1, R1, #0
	AND R3, R3, #0
	AND R5, R5, #0
	AND R6, R6, #0
	ADD R4, R2, #0
	NOT R4, R4
	ADD R4, R4, #1

LOOP
	ADD R0, R0, #1		; n=n+1
	AND R1, R1, #0
MULT
	ADD R5, R0, #0		; r5 = n
	ADD R6, R0, #0		; r6 = n
MULTLOOP
	ADD R1, R1, R5
	ADD R6, R6, #-1
	BRp MULTLOOP
COND
	ADD R3, R2, #0		; R3 copy of R2
	NOT R1, R1
	ADD R1, R1, #1
	ADD R3, R3, R1		; R3 - R1
	BRzp LOOP
N_1	
	ADD R5, R0, #-1
	ADD R6, R0, #-1
	AND R3, R3, #0
LOOP2
	ADD R3, R3, R5
	ADD R6, R6, #-1
	BRp LOOP2
	
DONE
	LD R4, saveR4
	LD R5, saveR5
	LD R6, saveR6
	HALT


saveR4 	.BLKW #1
saveR5 	.BLKW #1
saveR6 	.BLKW #1

.END



