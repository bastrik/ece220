.ORIG x3000

LD R2, STRSTART

LDR R0, R2, #0
AND R1, R1, #0
ADD R1, R1, #1
JSR BITSWAP
ADD R6, R0, #0
LD R2, GRADEMASK_ONE
AND R3, R6, R2
LD R2, GRADEMASK_TWO
AND R4, R6, R2
LD R2, GRADEMASK_THREE
AND R5, R6, R2
HALT
GRADEMASK_ONE 
.FILL x007E
GRADEMASK_TWO
.FILL x0001
GRADEMASK_THREE
.FILL x0080
; x3000

LD R2, STRSTART

LOOP
LDR R0, R2, #0
BRz FINISH		; We are done when we hit NULL
LD R1, BITMASK
JSR BITSWAP		; Do the bitswap
STR R0, R2, #0		; Writes back to the original location
ADD R2, R2, #1
BRnzp LOOP 
FINISH 
HALT

STRSTART .FILL x4000
BITMASK .FILL x0003	; set n = 3

;Do not touch or change and code above this line
;---------------------------------------------
;You must not change the separation line above
;Please write ALL your code for BITSWAP in between the separations lines,
;including all the labels, code, and .FILL commands


;Subroutine to swap bits
;Input:
;R0: the ascii that to be swapped
;R1: the number of bits to be swapped
; You can assume R1 is always 0, 1, 2, 3, or 4
;Output: R0, the swapped ascii
BITSWAP
;;YOUR CODE STARTS HERE

;HOW DO YOU FUCK UP THIS BADLY WITH YOUR PROGRAM DESIGN? WINDOWS NEWLINES?
;Extract n least significant bits with 8-R1 bitshits left
	ST R0,INIT_VALUE_R0
	ST R2,SWAP_R2
	ST R3,SWAP_R3
	ST R4,SWAP_R4
	ST R7,SWAP_R7

	NOT R2,R1
	ADD R2,R2,#1 ;R2 <- -R1
	ADD R2,R2,#8 ;R2 = number of shits to give
	;Number of shits will always be at least 4

	TOP_LOOP
		ADD R0,R0,R0 ;Do a single bit shit
		ADD R2,R2,#-1 ;Do R2 bit shits
		BRp TOP_LOOP

	LD R2,CLEAR_0
	AND R3,R0,R2 ;Wipe out higher bits, store result in R3
	;R1 has not been modified up to this point
	;Figure out which value (0-4) and load appropriate clear mask
	LEA R2,CLEAR_0
	ADD R2,R2,R1 ;R2 contains correct address
	LDR R2,R2,#0 ;R2 now contains actual mask
	
	LD R0,INIT_VALUE_R0
	AND R4,R0,R2 ;Store central bits in R4
	JSR EXTRACT ;Using original values of R0 and R1
	
	;R0 now contains the last part of the encrypted pattern
	;Combine R0,R3,R4 with straight addition (all only have intended bits)
	;Store result in R0
	ADD R0,R0,R3
	ADD R0,R0,R4

	;R1 never modified
	LD R2,SWAP_R2
	LD R3,SWAP_R3
	LD R4,SWAP_R4
	LD R7,SWAP_R7
	ret

SWAP_R2 .FILL #0
SWAP_R3 .FILL #0
SWAP_R4 .FILL #0
SWAP_R7 .FILL #0
INIT_VALUE_R0 .FILL #0
CLEAR_0 .FILL x00FF
CLEAR_1 .FILL x007E
CLEAR_2 .FILL x003C
CLEAR_3 .FILL x0018
CLEAR_4 .FILL x0000

;You must not change the separation line below.
;Write all your code for BITSWAP above this line
;=============================================


;DO NOT CHANGE THE GIVEN CODE BELOW
;=============================================
;;EXTRACT Subroutine (Given Code) 
;;Input: R0 - ASCII value
;;       R1 - n (between 0 and 4) bits to be extracted
;;Output:R0 - value of the n most significant bits of input

EXTRACT
ST R1, SAVER1
ST R2, SAVER2
ST R3, SAVER3
NOT R1, R1 
ADD R1, R1, #9
ETOP
ADD R1, R1, #0 
BRz EBOT
ADD R1, R1, #-1
LD R3, MASK
AND R0, R0, R3
AND R2, R2, #0

EINNER 
ADD R3, R2, R2
NOT R3, R3
ADD R3, R3, #1
ADD R3, R3, R0
BRz EINNERBOT
ADD R2, R2, #1
BRnzp EINNER

EINNERBOT
ADD R0, R2, #0
BRnzp ETOP

EBOT
LD R1, SAVER1
LD R2, SAVER2
LD R3, SAVER3
RET
MASK .FILL x00FE
SAVER1 .FILL #0
SAVER2 .FILL #0
SAVER3 .FILL #0

.END
