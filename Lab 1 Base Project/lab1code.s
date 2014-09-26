	
	;R2 : Generator stored here
	;R9	: The data to test (backwards)
	;R7	: single ASCII char to be manipulated
	;R1 : scratch register, decremented at every single char taken in
	;R5	: scratch register, to check if xor with generator should be performed or not
	;R6	: scratch register, counter for end of single char manipulation loop
	;R7	: scratch register, to check for end of single char manipulation loop
	
	AREA text, CODE, READONLY
	EXPORT lab1code
lab1code FUNCTION
	;first push all registers to use onto stack
	PUSH {R2-R9}
						;R0 has the pointer to data
						;R2 has length of data
	LDR R2, =0x8408	 	;putting generator into R2
	;LDR R9, =0x34313032	;putting 4102 into R9
	;MOV R1, #4			;length of the string to do crc
	MOV R9, #0
	MOV R7, #0
nextchar	
	CBZ R1, toend		;check to see if last char
	SUB R1, R1, #1		;decrement number of chars to use
	LDR R8, [R0, R9]	
	ADD R9, #1
	AND R8, R8, #0xFF	;take the first 8 bits to be manipulated (lsb)
	EOR R7, R8, R7
	;LSR R9, R9, #8		;shift the number right for prep to take in next number
	MOV R6, #8			;have a counter to count down from 8 to 0
singlecharcompare
	AND R5, R7, #0x1	;check if last bit is a 1
	LSR R7, R7, #1		;regardless if last bit is 1 we shift right
	CBZ	R5, nocompare	;compare and branch if 0
compare
	EOR R7, R7, R2		;xor what we have with generator
nocompare
	SUB R6, R6, #1		;decrement counter
	;SUB R7, R6, #8		;check if 8th time (end of ASCII char)
	CMP R6, #0
	BEQ nextchar
	;CBZ R7, nextchar	;bring the next ASCII char in 
	B	singlecharcompare	;if not time to bring the next char in keep going
toend	
	MOV R0, R7
	;POP {R2,R9,R1-R7}	;cleanup, not R7 
	BX LR ;
	ENDFUNC
	;END