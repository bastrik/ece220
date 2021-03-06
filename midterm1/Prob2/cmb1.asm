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
; You can assume R1 is always 0, 1, 2, or 3
;Output: R0, the swapped ascii
;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Local register usage
; R1 - n
; R2 - low n bits
; R3 - middle 8-(2n) bits
; R4 - high n bits
; R5 - 8-n

BITSWAP
	ST  R0, storeR0
	ADD R1, R1, #0
	BRz SKIP
	JSR EXTRACT
	ADD R2, R0, #0
	LD R0, storeR0
	ADD R5, R1, #0
	NOT R5, R5
	ADD R5, R5, #1
	ADD R5, R5, #8 		;R5 = -n + 8

LEFTSHIFTLOOP
	ADD R0, R0, R0
	ADD R5, R5, #-1
	BRp LEFTSHIFTLOOP

	ADD R4, R0, #0
	AND R0, R0, #0
	ADD R0, R2, R4
	ADD R0, R0, R3
	BR  BITDONE

SKIP
	LD R0, storeR0
BITDONE
	RET

storeR0		.BLKW #1

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
