# File: utils.asm
# Purpose: To define utilities which will be used in MIPS programs.
# Author: Josh T
#
# Subprograms Index:
# AllocateArray - Allocates space for an array
# ArraySwap - Swap values in an array of integers
# AverageArray - Calculates the mean average of all elements in an integer array
# BubbleSort - Sort data using a Bubble Sort algorithm
# DetermineMedian - Asks for three integers determines the median of them
# Exit - Call syscall with a server 10 to exit the program
# IsPrime - Determines if a positive integer is prime
# LeftCircularShift - Calculates an integer circular shifted left by 1 bit
# Mult4 - Calculate the product of 4 and some integer
# Mult10 - Calculate the product of 10 and some integer
# NAND - Calculate the NAND of two integers
# NOR - Calculate the NOR of two integers
# NOT - Calculate the NOT of an integer
# PrintInt - Print a string with an integer to the console
# PrintIntArray - Print all the elements in an array of integers, in the order they are stored in memory
# PrintIntArrayReverse - Print all the elements in an array of integers, reversed from how they are stored in memory
# PrintNewLine - Print a new line character (\n) to the console
# PrintString - Print a string to the console
# PromptInt - Prompt the user to enter an integer, and return it to the calling program.
# PromptString - Prompt the user to enter a string, and return that input
# RightCircularShift - Calculates an integer circular shifted right by 1 bit
# SumArray - Calculates the sum of all elements in an integer array
# Swap - Swaps the contents of two registers.
# ToLower - Convert a 3 character string to all lowercase characters.
# ToUpper - Convert a 3 character string to all uppercase characters.
# 



# Subprogram: AllocateArray
# Purpose: To allocate an array of $a0 items,
# each of size $a1.
# Parameters: $a0 - the number of items in the array
# $a1 - the size of each item
# Returns: $v0 - Address of the array allocated
# Side Effects: none
.text
AllocateArray:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a0, 4($sp)

	mul $a0, $a0, $a1
	li $v0, 9
	syscall

	lw $ra, 0($sp)
	lw $a0, 4($sp)
	addi $sp, $sp, 8
	jr $ra

# Subprogram: ArraySwap
# Purpose: to swap values in an array of integers
# Parameters: $a0 - the array containing elements to swap
# $a1 - index of element 1
# $a2 - index of elelemnt 2
# Returns: none
# Side Effects: none
ArraySwap:
	
	sll $t0, $a1, 2 # calcualate address of element 1
	add $t0, $a0, $t0  #get element 1 memory address
	sll $t1, $a2, 2 # calculate address of element 2
	add $t1, $a0, $t1 #get element 2 memory address
	
	#swap elements
	lw $t2, 0($t0) #get element 1
	lw $t3, 0($t1) #get element 2
	sw $t2, 0($t1) #store element 2 in element 1's memory
	sw $t3, 0($t0) #store element 1 in element 2's memory
	jr $ra
	


# Subprogram Name:  averageArray
# Purpose:  To find the mean average of all elements in an integer array
# Parameters: $a0 - the number of items in the array
# Returns:  $v0 - the average of all array elements
# Side Effects: none
.text
averageArray:

	addi $sp, $sp, -24 # Stack record
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $a0, 16($sp)
	sw $a1, 20($sp)

	# get the sum of all array elements
	jal sumArray
	
	# divide that element by the length of the array
	div $v0, $v0, $a1
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp) # restore stack and return
	lw $a0, 16($sp)
	lw $a1, 20($sp)
	addi $sp, $sp, 24
	jr $ra	
	
	
.text
# Subproram: Bubble Sort
# Purpose: Sort data using a Bubble Sort algorithm
# Parameters: $a0 - array
# $a1 - array size
# Returns: none
# Side Effects: none
BubbleSort:

	# Register conventions:
	# $s0 - array base
	# $s1 - array size
	# $s2 - outer loop counter
	# $s3 - inner loop counter

	addi $sp, $sp -20 # save stack information
	sw $ra, 0($sp)
	sw $s0, 4($sp) # need to keep and restore save registers
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	
	#store the array in $s0
	move $s0, $a0
	#store the  array size in $s1
	move $s1, $a1
	addi $s2, $zero, 0 #outer loop counter i = 0
	
	OuterLoop:
		#decrement the last index we loop to in the array
		addi $t1, $s1, -1
		
		#break if i > the last index we want to loop to
		slt $t0, $s2, $t1
		beqz $t0, EndOuterLoop
		
		addi $s3, $zero, 0 #inner loop counter j = 0
		InnerLoop:
			#decrement the last index we loop to in the array
			# this will always be 1 less than the last index of the outer loop
			addi $t1, $s1, -1
			
			#subtract i from the last index of the inner loop 
			sub $t1, $t1, $s2
			
			# break if j > the last index of the inner loop
			slt $t0, $s3, $t1
			beqz $t0, EndInnerLoop
			
			#find the memory offset of array[j]
			sll $t4, $s3, 2 # load data[j]. Note offset is 4 bytes
			
			#find the memory address by adding the offset to the
			add $t5, $s0, $t4
			
			#get array[j]
			lw $t2, 0($t5)
			
			#find the memory offest of array[j+1]
			addi $t6, $t5, 4 # load data[j+1]
			lw $t3, 0($t6)
			
			sgt $t0, $t2, $t3
			beqz $t0, NotGreater
			
			move $a0, $s0
			move $a1, $s3
			addi $t0, $s3, 1
			move $a2, $t0
			
			jal ArraySwap # t5 is &data[j], t6 is &data[j=1]
			
			NotGreater:
			#j++
			addi $s3, $s3, 1
			b InnerLoop
			
		EndInnerLoop:
		
		#i++
		addi $s2, $s2, 1
		b OuterLoop
		
	EndOuterLoop:
	lw $ra, 0($sp) #restore stack information
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	addi $sp, $sp 20
	jr $ra	
	

# Subprogram Name:  determineMedian
# Purpose:  Ask for three integers and to determine the median of them
# Parameters:  None
# Returns:  $v0 - the median of the three inputs
# Side Effects: none
.text
determineMedian:
	
	#push the stack
	addi $sp, $sp, -28
	
	#store $ra and the used variables
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	sw $a2, 12($sp)

	#get the first integer and store it on the stack
	la $a0, findMedianPrompt1
	jal PromptInt
	sw $v0, 16($sp)
	
	#get the second integer and store it on the stack
	la $a0, findMedianPrompt2
	jal PromptInt
	sw $v0, 20($sp)
	
	#get the thrid integer and store it on the stack
	la $a0, findMedianPrompt3
	jal PromptInt
	sw $v0, 24($sp)
	
	
	#load all the inputed numbers from the stack
	lw $a0, 16($sp)
	lw $a1, 20($sp)
	lw $a2, 24($sp)

	#determine which of the inputs is the median
	
	#if ($a0 < $a1)
	bge $a0, $a1, else1
		
		#if ($a0 < $a1) && ($a1 < $a2)
		bge $a1, $a2, else2
		
			#this means $a0 < $a1 < $a2
			#$a1 is the median
			move $v0, $a1
			j findMedianEnd
		
		#if ($a0 < $a1) && ($a1 >= $a2)
		else2:
		
		#if ($a0 < $a1) && ($a1 >= $a2) && ($a0 < $a2)
		bge $a0, $a2, else3
			#this means $a0 < $a2 <= $a1
			#$a2 is the median
			move $v0, $a2
			j findMedianEnd
		
			#if ($a0 < $a1) && ($a1 >= $a2) && ($a0 >= $a2)
			else3:
				#this means $a2 < $a0 < $a1
				#$a0 is the median
				move $v0, $a0
				j findMedianEnd
		
			
	#if ($a0 >= $a1)
	else1:
		#if ($a0 >= $a1) && ($a1 < $a2)
		bge $a1, $a2, else4
			
			#if ($a0 >= $a1) && ($a1 < $a2) && ($a0 < $a2)
			bge $a0, $a2, else5
			
				#this means $a1 < $a0 < $a2
				#$a0 is the median
				move $v0, $a0
				j findMedianEnd
		
			#if ($a0 >= $a1) && ($a1 < $a2) && ($a0 >= $a2)
			else5:
				#this means $a1 < $a2 < $a0
				#$a2 is the median
				move $v0, $a2
				j findMedianEnd
		
		#if ($a0 >= $a1) && ($a1 >= $a2)
		else4:
			#this means $a2 < $a1 < $a0
			#$a1 is the median
			move $v0, $a1
			j findMedianEnd
	

	findMedianEnd:
	#restore the used registers and $ra
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	lw $a1, 8($sp)
	lw $a2, 12($sp)
	
	#pop the stack
	addi $sp, $sp, 28
	
	#return
	jr $ra
	
.data
findMedianPrompt1: .asciiz "Please enter the first integer.\n"
findMedianPrompt2: .asciiz "Please enter the second integer.\n"
findMedianPrompt3: .asciiz "Please enter the third integer.\n"
	



# Subprogram Name:  Exit
# Purpose: exits the program
# Parameters:  none
# Returns:  none
# Side Effects: none
.text
Exit:
addi $v0, $zero, 10
syscall



#Subprogram Name:  IsPrime
# Purpose: takes a positive integer and determines if it is prime
# Parameters:  $a0 - the integer 
# Returns:  $v0 - 1 if the number is prime, 0 if it is not
# Side Effects: Will replace the values in $s7 and $s6
.text
IsPrime:

	#we will determine if the number is prime by dividing it by every number between 1 and itself
	#if any of those numbers goes in evenly, the number is not prime

	#start a counter at 2
	addi $s7, $zero, 2

	startCheckLoop:
	#if the counter equals the input, we've gone through all the numbers and the input is prime
	#otherwise, we should continue iterating through the loop
	beq $s7, $a0, Prime
	
		#take the modulus of the counter and the input
    		div $a0, $s7
    		mfhi $s6
    
    		#if the modulus is 0, the counter divides the input evenly and the input is not prime
    		#we can break from the loop
    		beq $s6, 0, notPrime
    
    		#if the modulus is not 0, the counter does not divide the input evenly
    		#increment the counter and reiterate through the loop
    		addi $s7, $s7, 1
    j startCheckLoop


	notPrime:
	#if the number is not prime, set $v0 to 0
	addi $v0, $zero, 0
	j isPrimeReturn

	Prime:
	#if the number is prime, set $v0 to 1
	addi $v0, $zero, 1

	#return
	isPrimeReturn: jr $ra
	
# Subprogram Name:  LeftCircularShift
# Purpose: takes an input parameter and return that parameter left circular shifted by one bit and the bit that was moved
# Parameters:  $a0 - the integer to shift
# Returns:  $v0 - the integer after it has been left circular shifted
# $v1 - the bit that was shifted to the back of the number
# Side Effects: Will replace the contents of $s7
.text
LeftCircularShift:
	
	#determine if the leftmost digit is a 0 or a 1
	#if the leftmost digit is a 1, $v1 will become 1 followed by 31 0's in binary
	#if the leftmost digit is a 0, $v1 will become 0 in binary
	addi $s7, $zero, 2147483648
	and $v1, $a0, $s7
	
	#if the leftmost digit is 1
	bne $v1, $s7, firstBitIsZero
		#make $v1 a 1
		addi $v1, $zero, 1

	#if the leftmost digit is 0, we will leave $v1 as a 0
	
	firstBitIsZero:
	#shift the input left one bit, store that in $v0
	sll $v0, $a0, 1
	
	#make the rightmost digit of $v0 a 0 if the input began with a zero
	#make it a 1 if the input began with a one
	add $v0, $v0, $v1
	
	#return
	jr $ra	

	
# Subprogram Name:  largestAndAverage
# Purpose:  To determine the largest integer out of the four parameters and to calculate the average of these integers
# Parameters:  $a0 - the first integer
#  $a1 - the second integer
#  $a2 - the third integer
#  $a3 - the fourth integer
# Returns:  $v0 - the largest integer out of the four parameters
#  $v1 - the average of the four parameters
.text
largestAndAverage:

	#int var0 = $a0, var1 = $a1, var2 = $a2, var3 = $a3;
	addi $sp, $sp -20 # push the stack
	sw $ra, 0($sp) # Save the $ra
	sw $a0, 4($sp) # Save $a0
	sw $a1, 8($sp) # Save $a1
	sw $a2, 12($sp) # Save $a2
	sw $a3, 16($sp) # Save $a3
	
	#$s0 = getLarger($a0, $a1)
	jal getLarger
	move $s0, $v0
	
	#$s0 = getLarger($s0, $a2)
	move $a0, $s0
	move $a1, $a2
	jal getLarger
	move $s0, $v0
	
	#$v0 = getLarger($s0, $a3)
	move $a0, $s0
	move $a1, $a3
	jal getLarger
	
		
	lw $a0, 4($sp)  #set $a0 back to var0
	lw $a1, 8($sp)  #set $a1 back to var1
	lw $a2, 12($sp) #set $a2 back to var2
	lw $a3, 16($sp) #set $a3 back to var3
	
	#$v1 = (var0 + var1 + var2 + var3)/ 4;
	add $v1, $a0, $a1
	add $v1, $v1, $a2
	add $v1, $v1, $a3
	div $v1, $v1, 4

	#Return
	lw $ra, 0($sp) # restore the $ra
	addi $sp, $sp, 20  # pop the stack
	jr $ra
	


# Subprogram Name:  getLarger
# Purpose:  To determine which of the two parameters is larger
# Parameters:  $a0 - the first integer
#  $a1 - the second integer
# Returns:  $v0 - the largest integer out of the two parameters
.text
getLarger:
	#$v0 = $a0
	move $v0, $a0
	
	#if ($a1 > $a0)
	bge $a0, $a1, getLargerEnd
	
		#$v0 = $a1
		move $v0, $a1
	
	#return
	getLargerEnd:
	jr $ra




# Subprogram Name:  Mult4
# Purpose: takes an input parameter and returns that parameter multiplied by 4 using only shift and add operations.
# Parameters:  $a0 - the integer to multiply by 4
# Returns:  $v0 - the product of 4 and the parameter
# Side Effects: none
.text
Mult4:
	#set $v0 to the input shifted left by 2 bits
	sll $v0, $a0, 2
	
	#return
	jr $ra

# Subprogram Name:  Mult10
# Purpose: takes an input parameter, and return that parameter multiplied by 10 using only shift and add operations.
# Parameters:  $a0 - the integer to multiply by 10
# Returns:  $v0 - the product of 10 and the parameter
# Side Effects: will replace the value in $s7
.text
Mult10:
	#set $s7 to the input shifted left by 1 bit
	#this is the input multiplied by 2
	sll $s7, $a0, 1
	
	#set $v0 to the input shifted left by 3 bits
	#this is the input multiplied by 8
	sll $v0, $a0, 3
	
	#adding these two results will get the input multiplied by 10
	add $v0, $v0, $s7
	
	#return
	jr $ra

# Subprogram Name:  NAND
# Purpose: takes two input parameters, and return the NAND operation on those two parameter.
# Parameters:  $a0 - the value to nand with the second parameter
# $a1 -  the value to nand with the first parameter
# Returns:  $v0 - the nand of the two parameters
# Side Effects: none
.text
NAND:
	#and the two inputs, then negate that result
	and $v0, $a0, $a1
	not $v0, $v0
	
	#return
	jr $ra

# Subprogram Name:  NOR
# Purpose: takes two input parameters, and return the NOR operation on those two parameter.
# Parameters:  $a0 - the value to nor with the second parameter
# $a1 -  the value to nor with the first parameter
# Returns:  $v0 - the nor of the two parameters
# Side Effects: none
.text
NOR:
	#or the two inputs, then negate that result
	or $v0, $a0, $a1
	not $v0, $v0
	
	#return
	jr $ra

# Subprogram Name:  NOT
# Purpose: take one input parameters, and return the NOT operation on that parameter.
# Parameters:  $a0 - the value to get the not of
# Returns:  $v0 - the not of the parameters
# Side Effects: will replace the value in $s7
.text
NOT:
addi $s7, $zero, 4294967295
xor $v0, $a0, $s7
jr $ra

# Subprogram Name:  PrintInt
# Purpose: To print a string to the console
# Parameters: $a0 - The value of the int to print
# Returns: None
# Side Effects: The String is printed followed by the integer value.
.text
PrintInt:

	#push stack
	addi $sp, $sp, -4
	
	#store used variables
	sw $v0, 0($sp)

	# Print integer.
	addi $v0, $zero, 1
	syscall
	
	#restore used variables
	lw $v0, 0($sp)
	
	#pop stack
	addi $sp, $sp, 4
	
	#return
	jr $ra
	
	
# Subprogram: PrintIntArray
# Purpose: print an array of ints
# Parameters: $a0 - the base address of the array
# $a1 - the size of the array
# Returns: none
# Side Effects: will replace the contents of $s0, $s1 and $s2
.text
PrintIntArray:
	addi $sp, $sp, -24 # Stack record
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $a0, 16($sp)
	sw $a1, 20($sp)
	move $s0, $a0 # save the base of the array to $s0
	
	# initialization for counter loop
	# $s1 is the ending index of the loop
	# $s2 is the loop counter
	move $s1, $a1
	move $s2, $zero
	
	# set $a1 to the final index in the array
	addi $a1, $a1, -1
	
	la $a0 open_bracket # print open bracket
	jal PrintString
	
	loop:
		# check ending condition
		sge $t0, $s2, $s1
		bnez $t0, end_loop
		
		# Multiply the loop counter by 4 to get offset (each element
		# is 4 big).
		
		sll $t0, $s2, 2		

		add $t0, $t0, $s0 # address of next array element
		lw $a0, 0($t0) # Next array element
		jal PrintInt # print the integer from array
		
		# print comma after this number, unless it is the last element in the array
		beq $s2, $a1, incrementAndLoop
			li $v0, 4 # print comma
			la $a0, comma
			syscall
		
		incrementAndLoop:
		addi $s2, $s2, 1 #increment $s2
		b loop
		
		
	end_loop:
	li $v0, 4 # print close bracket
	la $a0, close_bracket
	syscall
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp) # restore stack and return
	lw $a0, 16($sp)
	lw $a1, 20($sp)
	addi $sp, $sp, 24
	jr $ra
	
.data
open_bracket: .asciiz "["
close_bracket: .asciiz "]"
comma: .asciiz ", "

# Subprogram: PrintIntArrayReverse
# Purpose: print an array of ints in reverse
# inputs: $a0 - the base address of the array
# $a1 - the size of the array
# Side Effects: will replace the contents of $s0, $s1 and $s2
.text
PrintIntArrayReverse:
	addi $sp, $sp, -16 # Stack record
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	move $s0, $a0 # save the base of the array to $s0
	
	# initialization for counter loop
	# $s1 is -1
	# $s2 is the loop counter that starts with the last element
	addi $s1, $zero, -1
	addi $s2, $a1, -1

	la $a0 open_bracket2 # print open bracket
	jal PrintString
	
	reverseLoop:
		# check ending condition
		sle $t0, $s2, $s1
		bnez $t0, end_loop2
		
		# Multiply the loop counter by 4 to get offset (each element
		# is 4 big).
		
		sll $t0, $s2, 2
		
		add $t0, $t0, $s0 # address of next array element
		lw $a0, 0($t0) # Next array element
		jal PrintInt # print the integer from array
		
		# print comma after this number, unless it is the first element in the array
		beq $s2, $zero, decrementAndLoop
			li $v0, 4
			la $a0, comma2
			syscall
		
		decrementAndLoop:
		addi $s2, $s2, -1 #decrement $s2
		b reverseLoop
		
		
	end_loop2:
	li $v0, 4 # print close bracket
	la $a0, close_bracket2
	syscall
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)

	lw $s1, 8($sp)
	lw $s2, 12($sp) # restore stack and return
	addi $sp, $sp, 16
	jr $ra
	
.data
open_bracket2: .asciiz "["
close_bracket2: .asciiz "]"
comma2: .asciiz ", "	


# Subprogram Name:  PrintNewLine
# Purpose: takes two input parameters, and return the NOR operation on those two parameter.
# Parameters: none
# Returns:  none
# Side Effects: A new line character is printed to the user's console
.text
PrintNewLine:
	
	#push stack
	addi $sp, $sp, -8
	
	#store used variables
	sw $v0, 0($sp)
	sw $a0, 4($sp)
	
	li $v0, 4
	la $a0, __PNL_newline
	syscall
	
	#restore used variables
	lw $v0, 0($sp)
	lw $a0, 4($sp)
	
	#pop stack
	addi $sp, $sp, 8
	
	jr $ra

.data
	__PNL_newline: .asciiz "\n"

# Subprogram Name:  PrintString
# Purpose: To print a string to the console
# Parameters: $a0 - The address of the string to print.
# Returns: None
# Side Effects: The String is printed to the console.
.text
PrintString:

	#push stack
	addi $sp, $sp, -4
	
	#store used variables
	sw $v0, 0($sp)

	# Print string
	addi $v0, $zero, 4
	syscall
	
	#restore used variables
	lw $v0, 0($sp)
	
	#pop stack
	addi $sp, $sp, 4
	
	#return
	jr $ra

# Subprogram Name:  PromptInt
# Purpose: To print the user for an integer input, and
# to return that input value to the caller.
# Parameters: $a0 - The address of the string to print.
# Returns: $v0 - The value the user entered
# Side Effects: The String is printed followed by the integer value.
.text
PromptInt:
	# Print the prompt, which is already in $a0
	li $v0, 4
	syscall

	# Read the integer value. Note that at the end of the
	# syscall the value is already in $v0, so there is no
	# need to move it anywhere.
	li $v0, 5
	syscall

	#return
	jr $ra
	
# Subprogram: PromptString
# Purpose: To prompt for a string, allocate the string
# and return the string to the calling subprogram.
# Parameters: $a0 - The prompt
# $a1 - The maximum size of the string
# Returns: $v0 - The address of the user entered string
# Side Effects: none
PromptString:
	addi $sp, $sp, -12 # Push stack
	sw $ra, 0($sp)
	sw $a1, 4($sp)
	sw $s0, 8($sp)
	
	li $v0, 4 # Print the prompt
	syscall # in the function, so we know $a0 still has
	
	# the pointer to the prompt.
	li $v0, 9 # Allocate memory
	lw $a0, 4($sp)
	syscall
	move $s0, $v0
	
	move $a0, $s0 # Read the string
	li $v0, 8
	lw $a1, 4($sp)
	syscall
	
	move $v0, $s0 # Save string address to return
	
	lw $ra, 0($sp) # Pop stack
	lw $s0, 8($sp)
	
	addi $sp, $sp, 12
	jr $ra

# Subprogram Name:  RightCircularShift
# Purpose: takes an input parameter, and return that parameter right circular shifted by one bit and the bit that was moved
# Parameters:  $a0 - the integer to shift
# Returns:  $v0 - the integer after it has been right circular shifted
# $v1 - the bit that was shifted to the front of the number
# Side Effects: May replace the contents of $s7
.text
RightCircularShift:

srl $v0, $a0, 1
and $v1, $a0, 1
bne $v1, 1, lastBitIsZero
	addi $s7, $zero, 2147483648
	or $v0, $v0, $s7

lastBitIsZero: 
jr $ra


# Subprogram Name:  sumArray
# Purpose:  To find the largest element in an integer array
# Parameters: $a0 - the number of items in the array
# Returns:  $v0 - the largest element
# Side Effects: none
.text
sumArray:
	# Stack record
	addi $sp, $sp, -24
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $a0, 16($sp)
	sw $a1, 20($sp)
	
	move $s0, $a0 # save the base of the array to $s0
	
	# initialization for counter loop
	# $s1 is the ending index of the loop
	# $s2 is the loop counter
	move $s1, $a1
	move $s2, $zero	
	addi $v0, $zero, 0

	sumArrayLoop:
		# check ending condition
		bge $s2, $s1, afterLoop
		
		# Multiply the loop counter by 4 to get offset (each element
		# is 4 big).
		sll $t0, $s2, 2		

		add $t0, $t0, $s0 # address of next array element
		lw $a0, 0($t0) # Next array element
		add $v0, $v0, $a0
		
		addi $s2, $s2, 1 #increment $s2
		j sumArrayLoop
		
		
	afterLoop:
	
	# restore stack and return
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $a0, 16($sp)
	lw $a1, 20($sp)
	addi $sp, $sp, 24
	
	jr $ra	


# Subprogram Name:  Swap
# Purpose: take two input parameters, swap them using only the XOR operation.
# Parameters:  $a0 - the value to swap with $a1
# $a1 -  the value to swap with $a0
# Returns:  none
# Side Effects: will replace the contents of $s7
.text
Swap:
xor $s7, $a0, $a1
xor $a0, $a0, $s7
xor $a1, $a1, $s7
jr $ra

# Subprogram Name:  ToLower
# Purpose: take a 32 bit input which is 3 characters and a null, or a 3 character string.
#          Convert the 3 characters to lower case if they are upper case, or do nothing if they are already lower case.
# Parameters:  $a0 - the 3 character string
# Returns:  $a0 - the lowercase version of the parameter string
# Side Effects: will replace the contents of $s6 and $s7
.text
ToLower:
	#$s7 will be our "index" for this loop
	#start it at zero initially
	addi $s7, $zero, 0
	
	#loop body
	startToLowerLoop:
	#get the character at the index in the string
	# $s6 = $a0[$s7]
    	lb $s6, ($a0)
    	
    	#if we've looped through all three characters, return
    	beq $s7, 3, toLowerReturn
 
    	#if we still have more characters,
    	
    	#convert the current character in $s6 to lowercase by taking the or of it and 01000000
    	or  $s6, $s6, 32
	
	#add the current character to the result string called allLow
	sb $s6, allLow($s7)
	
	#increment the $s7 index and adjust the $a0 input string
	addi $a0, $a0, 1
	addi $s7, $s7, 1
	
	#loop again
    	j startToLowerLoop

	toLowerReturn:
	la $a0, allLow
    	jr $ra
.data
allLow: .asciiz "---"

# Subprogram Name:  ToUpper
# Purpose: take a 32 bit input which is 3 characters and a null, or a 3 character string.
#          Convert the 3 characters to upper case if they are lower case, or do nothing if they are already upper case.
# Parameters:  $a0 - the 3 character string
# Returns:  $a0 - the uppercase version of the parameter string
# Side Effects: will replace the contents of $s6 and $s7
.text
ToUpper:
	#$s7 will be our "index" for this loop
	#start it at zero initially
	addi $s7, $zero, 0
	
	#loop body
	startToUpperLoop:
	#get the character at the index in the string
	# $s6 = $a0[$s7]
    	lb $s6, ($a0)
    	
    	#if we've looped through all three characters, return
    	beq $s7, 3, toUpperReturn
 
    	#if we still have more characters,
    	
    	#convert the current character in $s6 to uppercase by taking the and of it and 10111111
    	and  $s6, $s6, 95
	
	#add the current character to the result string called allCap
	sb $s6, allCap($s7)
	
	#increment the $s7 index and adjust the $a0 input string
	addi $a0, $a0, 1
	addi $s7, $s7, 1

	#loop again
    	j startToUpperLoop

	toUpperReturn:
	la $a0, allCap
    	jr $ra
.data
allCap: .asciiz "---"

