;
;
;
.ORIG x3000
	AND R0, R0, #0
	AND R1, R1, #0
	AND R6, R6, #0

GETCHAR
	GETC
	OUT
CHKLINE
	LD R1, SEMICOLON
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POP_LINE 		; if semicolon, validate expression
CHKSPACE
	LD R1, SPACE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		
	BRz GETCHAR			; if space, loop back
EVALOP
	LD R1, PLUSASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POP_PLUS 		; + found
	LD R1, MINUSASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POP_MINUS 		; - found
	LD R1, MULTIASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POP_MULTI 		; * found
	LD R1, DIVASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POP_DIV 		; / found
	LD R1, EXPASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POP_EXP 		; ^ found
EVALNUM
	LD R1, ZERO
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 0 found
	LD R1, ONE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 1 found
	LD R1, TWO
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 2 found
	LD R1, THREE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 3 found
	LD R1, FOUR
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 4 found
	LD R1, FIVE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 5 found
	LD R1, SIX
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 6 found
	LD R1, SEVEN
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 7 found
	LD R1, EIGHT
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 8 found
	LD R1, NINE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz PUSHNUM 		; 9 found
	JSR INVALID 		; not a number

PUSHNUM
	LD R1, OFFSET
	ADD R0, R0, R1
	JSR PUSH
	JSR GETCHAR

OFFSET .FILL xFFD0   	; -48 in 2's complement

POP_PLUS
	JSR POP
	ADD R4, R0, #0 		; R4 <- R0
	JSR POP
	ADD R3, R0, #0 		; R3 <- R0
	ADD R1, R5, #0
	BRp INVALID 		; pop failed
	JSR PLUS
POP_MINUS
	JSR POP
	ADD R4, R0, #0 		; R4 <- R0
	JSR POP
	ADD R3, R0, #0 		; R3 <- R0
	ADD R1, R5, #0
	BRp INVALID
	JSR MIN
POP_MULTI
	JSR POP
	ADD R4, R0, #0 		; R4 <- R0
	JSR POP
	ADD R3, R0, #0 		; R3 <- R0
	ADD R1, R5, #0
	BRp INVALID
	JSR MUL
POP_DIV
	JSR POP
	ADD R4, R0, #0 		; R4 <- R0
	JSR POP
	ADD R3, R0, #0 		; R3 <- R0
	ADD R1, R5, #0
	BRp INVALID
	JSR DIV
POP_EXP
	JSR POP
	ADD R4, R0, #0 		; R4 <- R0
	JSR POP
	ADD R3, R0, #0 		; R3 <- R0
	ADD R1, R5, #0
	BRp INVALID
	JSR EXP
POP_LINE
	JSR POP
	ADD R1, R5, #0
	BRp INVALID
FINISHED
	ADD R5, R0, #0
	JSR PRINT_HEX
	JSR DONE

INVALID
	LEA R0, ERR
	PUTS
	JSR DONE


PLUSASCII 	.FILL x002B
MINUSASCII 	.FILL x002D
MULTIASCII  .FILL x002A
DIVASCII 	.FILL x002F
EXPASCII 	.FILL x005E
ERR 		.STRINGZ "Invalid Expression"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
; R1 bit counter
; R2 line counter
; R4 temp
; R5 digit
; R6 digit counter
PRINT_HEX
	ST  R5, SOLN
	ADD R3, R5, #0
	AND R6, R6, #0 		; reset digit counter
HEX_LOOP
	ADD R4, R6, #-4		; printed < 4 digits?
	BRzp DONE
	AND R1, R1, #0		; reset bit counter
	AND R5, R5, #0		; reset digit
HEX_BITCOUNT
	ADD R4, R1, #-4		; got < 4 bits from R1?
	BRzp HEX_OUTPUT
	ADD R5, R5, R5		; shift digit left
	ADD R3, R3, #0		; R3 < 0? (MSB = 1)
	BRzp HEX_LEFTSHIFT
	ADD R5, R5, #1 		; add one to digit

HEX_LEFTSHIFT
	ADD R3, R3, R3		; shift R3 left
	ADD R1, R1, #1 		; incr bit counter
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
DONE	
	LD 	R5, SOLN
	HALT			; done

SOLN  		.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4
	JSR PUSH
	JSR GETCHAR	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	NOT R4, R4
	ADD R4, R4, #1
	ADD R0, R3, R4
	JSR PUSH
	JSR GETCHAR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ADD R0, R4, #0
	BRz MULZERO
	AND R0, R0, #0
MULLOOP
		ADD R0, R0, R3
		ADD R4, R4, #-1
		BRp MULLOOP
MULZERO
	JSR PUSH
	jsr GETCHAR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	AND R0, R0, #0
	NOT R4, R4
	ADD R4, R4, #1
DIVLOOP
	ADD R0, R0, #1
	ADD R3, R3, R4
	BRzp DIVLOOP
	ADD R0, R0, #-1
	JSR PUSH
	JSR GETCHAR	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ADD R3, R3, #0
	BRz EXPZERO
	ADD R4, R4, #0
	BRz EXPONE
	AND R0, R0, #0
	ADD R5, R4, #-1		; R5 exploop counter
	BRz EXPBASE
	ST 	R3, ORIGR3 		
EXPLOOP
	LD  R6, ORIGR3		; R6 inner multiply loop counter
EXPLOOP2		
		ADD R0, R0, R3
		ADD R6, R6, #-1
		BRp EXPLOOP2
	ADD R5, R5, #-1
	BRp EXPLOOP	
	JSR PUSH
	JSR GETCHAR
EXPZERO
	AND R0, R0, #0
	JSR PUSH
	JSR GETCHAR
EXPONE
	AND R0, R0, #0
	ADD R0, R0, #1
	JSR PUSH
	JSR GETCHAR
EXPBASE
	ADD R0, R3, #0
	JSR PUSH
	JSR GETCHAR
ORIGR3 		.BLKW #1

A 			.FILL x0041
ZERO 		.FILL x0030
ONE 		.FILL x0031
TWO 		.FILL x0032
THREE 		.FILL x0033
FOUR 		.FILL x0034
FIVE 		.FILL x0035
SIX 		.FILL x0036
SEVEN 		.FILL x0037
EIGHT 		.FILL x0038
NINE 		.FILL x0039
SPACE 		.FILL x0020
SEMICOLON 	.FILL x003B

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
;;;;;;;;;;;;;;;;;;;;;;;;; User defined var



.END
