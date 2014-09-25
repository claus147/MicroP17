	
	;R1 : Generator stored here
	;R2	: The data to test (backwards)
	;R3	: single ASCII char to be manipulated
	;R4 : scratch register, decremented at every single char taken in
	;R5	: scratch register, to check if xor with generator should be performed or not
	;R6	: scratch register, counter for end of single char manipulation loop
	;R7	: scratch register, to check for end of single char manipulation loop
	
	AREA text, CODE, READONLY
	EXPORT lab1code
lab1code
	;first push all registers to use onto stack
	PUSH {R1-R7}
	
	LDR R1, =0x8408	 	;putting generator into R1
	LDR R2, =0x34313032	;putting 4102 into R2
	MOV R4, #4			;length of the string to do crc
	
nextchar	
	CBZ R4, toend		;check to see if last char
	SUB R4, R4, #1		;decrement number of chars to use
	AND R8, R2, #0xFF	;take the first 8 bits to be manipulated (lsb)
	EOR R3, R8, R3
	LSR R2, R2, #8		;shift the number right for prep to take in next number
	MOV R6, #8			;have a counter to count down from 8 to 0
singlecharcompare
	AND R5, R3, #0x1	;check if last bit is a 1
	LSR R3, R3, #1		;regardless if last bit is 1 we shift right
	CBZ	R5, nocompare	;compare and branch if 0
compare
	EOR R3, R3, R1		;xor what we have with generator
nocompare
	SUB R6, R6, #1		;decrement counter
	;SUB R7, R6, #8		;check if 8th time (end of ASCII char)
	CMP R6, #0
	BEQ nextchar
	;CBZ R7, nextchar	;bring the next ASCII char in 
	B	singlecharcompare	;if not time to bring the next char in keep going
toend	
	POP {R1,R2,R4-R7}	;cleanup, not R3 
	BX LR ;
	END