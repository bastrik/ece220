;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here
; Registers I am going to use;
; R1 value to print in hex
; R2 line counter
; R3 bit counter
; R4 temp
; R5 digit
; R6 digit counter

	AND	R2, R2, #0 	; init the line counter to 0

ALPHABET_LOOP
	LD 	R1, HIST_ADDR 	; load frequency
	ADD R1, R1, R2		; offset by line to get each letter frequency
	LDR R1, R1, x0000

	LD 	R0, AT		; @ = 40 in ASCII
	ADD R0, R0, R2		; offset by line to get each letter ASCII
	OUT

	LD 	R0, SPACE		; space = 20 in ASCII
	OUT

	AND R6, R6, #0 		; reset digit counter

HEX_LOOP
	ADD R4, R6, #-4		; printed < 4 digits?
	BRzp PRINT_NUM

	AND R3, R3, #0		; reset bit counter
	AND R5, R5, #0		; reset digit
HEX_BITCOUNT
	ADD R4, R3, #-4		; got < 4 bits from R1?
	BRzp HEX_OUTPUT
	ADD R5, R5, R5		; shift digit left
	ADD R1, R1, #0		; R1 < 0? (MSB = 1)
	BRzp HEX_LEFTSHIFT
	ADD R5, R5, #1 		; add one to digit

HEX_LEFTSHIFT
	ADD R1, R1, R1		; shift R1 left
	ADD R3, R3, #1 		; incr bit counter
	BR 	HEX_BITCOUNT	; check if bit is 4 yet

HEX_OUTPUT
	ADD R4, R5, #-9		; digit <= 9?
	BRnz HEX_NUM
	LD 	R4, A 			; add A
	ADD R0, R4, R5 		; put the correct ascii value in R0 for letter
	ADD R0, R0, #-10
	BRnzp PRINT

HEX_NUM
	LD R4, ZERO 		; add 0
	ADD R0, R4, R5		; put the correct ascii value in R0 for number
PRINT
	OUT
	ADD R6, R6, #1
	BRnzp HEX_LOOP

PRINT_NUM
	;;;;;;;;;;;;;;;;;;;;;;;
	AND R0, R0, #0
	ADD R0, R0, #10 	; print new line
	OUT

	ADD R2, R2, #1 		; incr

	AND R1, R1, #0
	ADD R1, R2, #0
	NOT R1, R1
	ADD R1, R1, #1
	LD  R5, NUM_BINS
	ADD R5, R5, R1		; check how many iterations are done
	BRp ALPHABET_LOOP



DONE	HALT			; done

SPACE 		.FILL x0020	; ASCII for space
AT 			.FILL x0040 ; ASCII for @
ZERO 		.FILL x0030 ; ASCII for 0
A 			.FILL x0041 ; ASCII for A
; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
