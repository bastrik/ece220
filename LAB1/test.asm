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

; ---------------
; INTRO PARAGRAPH
; ---------------
; My code below prints out a histogram displaying each character in a string alongside it's number of occurences. The main part of my code was developed from the lab1 exercise, which outputs a    
; hexadecimal number from a series of bits. This code is contained within a loop that prints the letter for which the frequency is being displayed. It is also used to keep track of the number of
; iterations through the inner loop so that each time one frequency is printed, the counter increments in order to print and convert the frequency for the next character. The outermost loop is 
; simply used to initialise the counter to zero at the very beginning.

PRINT_HIST

      AND R6, R6, x0000                                 ; initialise the line count to 0 

        PRINT_LOOP

                LD R3, HIST_ADDR                         ; load starting address of frequency count into r3 for conversion 
                ADD R3, R3, R6                           ; add r6, which will keep getting incremented as we loop to give frequencies for a, b...
                LDR R3, R3, x0000     

                LD R0, AT                                ; load decimal value for @ into output register 
                ADD R0, R0, R6                           ; add current line count
                OUT

                LD R0, SPACE                             ; output space to go before frequency is printed
                OUT              

                  ASCII_LOOP

                        AND R4, R4, #0

			LD R4, DIGITS

			AND R0, R0, #0                    ; initialise output register to 0
			AND R5, R5, #0                    ; initialise digit counter to 0 
			AND R1, R1, #0                    ; initialise bit counter to 0
			AND R2, R2, #0                    ; initialise r2 to 0 (will be used to check how many digits we have)

			DIGCHECK      ADD R2, R5, #-4     ; check if we have 4 digits yet by subtracting this from digit counter
				      BRn BITCOUNT        ; move to bitcount if we do not

			FINISHED      BR CONVERTED        ; escape the loop

			BITCOUNT      ADD R1, R1, #-4     ; check if we have all the bits in the same way we checked for digits 
				      BRn SHIFTLEFT       ; shift r4 left if we do not have all bits

			CHECKRANGE    ADD R4, R4, #-10    ; subtract total of 10 from digit to check if it is in range
				      BRn CONVERT
				      ADD R4, R4, #15
				      ADD R4, R4, #15
				      ADD R4, R4, #15
				      ADD R4, R4, #15
				      ADD R4, R4, #5      ; if number is out of range then add 'A' (x0041 or decimal 65)
				      ADD R0, R4, #0      ; copy the output digit to r0 
				      TRAP x21            ; display
				      ADD R5, R5, #1      ; increment digit counter
				      AND R4, R4, #0      ; reset r4 to 0
				      BR DIGCHECK         ; check back for number of digits displayed so far

			CONVERT       ADD R4, R4, #10     ; add back the 10 that was removed earlier before adding offset
				      ADD R4, R4, #15
				      ADD R4, R4, #15
				      ADD R4, R4, #15
				      ADD R4, R4, #3       ; number in range so add '0' (x0030 or decimal 48)
				      ADD R0, R4, #0       
				      TRAP x21
				      ADD R5, R5, #1
				      AND R4, R4, #0           
				      BR DIGCHECK       

			SHIFTLEFT     ADD R1, R1, #4      ; add back the 4 that was subtracted to check if we have correct number of bits
				      ADD R4, R4, R4      ; shift r4 left to make room for incoming bit

			DATAMSB       AND R3, R3, R3      ; check the MSB of r3
				      BRn INCDIGITS       ; if it is a 1, add 1 to r4
				      ADD R4, R4, #0      ; else add zero to r4
				      BR SHIFTDATALEFT    ; shift r3 left
			  
			INCDIGITS     ADD R4, R4, #1        

			SHIFTDATALEFT ADD R3, R3, R3
				      ADD R1, R1, #1      ; increment bit counter
				      BR BITCOUNT         ; go back to check if bitcount is <= 4        


                        CONVERTED                         ; continue through programme
                        

                AND R0, R0, x0000                         
                ADD R0, R0, #10                           ; output new line
                OUT

                ADD R6, R6, #1                            ; increment line count

                AND R1, R1, #0                             
                LD R1, NEG_NUM_BINS                     

                ADD R1, R1, R6                            ; check how many iterations are done
                BRn PRINT_LOOP                            ; if negative, there are still more lines to print so loop back

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
DIGITS          .FILL x0000     ; MSB from r3 will be moved to LSB of this location 
NEG_NUM_BINS    .FILL xFFE5     ; used to count how many iterations have already been done
SPACE           .FILL #32       ; corresponding decimal for space
AT              .FILL #64       ; corresponding decimal for @

; for testing, you can use the lines below to include the string in this program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END