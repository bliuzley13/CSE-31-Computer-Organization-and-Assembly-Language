.data

# TPS 2 #3 (input prompt to be displayed)
prompt: .asciiz "Please enter a number: "

.text
main: 	addi $sp, $sp, -4 # Moves stack pointer to make room for storing local variables (push the stack frame)
	# TPS 2 #3 (displays input prompt)
	li $v0, 4			
	la $a0, prompt	
	syscall					
	# TPS 2 #4 (reads user input)
	li $v0, 5			
	syscall				
	add $a0, $v0, $zero
	jal recursion	# Calls recursion(x)
	# TPS 2 #6 (prints out returned value)
	sw $v0, 0($sp)
	li $v0, 1
	lw $a0, 0($sp)					
	syscall
	j end		# Jumps to end of program

# Implements recursion
recursion: addi $sp, $sp, -12	# Pushes stack frame for local storage
	# TPS 2 #7 
	sw $ra, 0($sp)		
	addi $t0, $a0, 1
	bne $t0, $zero, not_minus_one
	# TPS 2 #8 (updates returned value)
	addi $v0, $zero, 1
	j end_recur
		
not_minus_one:	bne $a0, $zero, not_zero
	# TPS 2 #9 (updates returned value)
	addi $v0, $zero, 3
	j end_recur		

not_zero: sw $a0, 4($sp) 	
	# TPS 2 #11 (Prepares new input argument, i.e. m - 2)
	addi $a0, $a0, -2
	jal recursion	# Calls recursion(m - 2)
	# TPS 2 #12 
	sw $v0, 8($sp)
	lw $a0, 4($sp)	
	# TPS 2 #13 (Prepares new input argument, i.e. m - 1)
	addi $a0, $a0, -1
	jal recursion	# Calls recursion(m - 1)
	# TPS 2 #14 (updates returned value)
	lw $a0, 4($sp) # Original input same as line 57
	lw $t0, 8($sp) # Previous value from m - 2
	add $v0, $t0, $v0 # Adds m - 1 and then m - 2, recursion	
	j end_recur
		
# End of recursion function	
end_recur: # TPS 2 #15 
	lw $ra, 0($sp)		# Pops stack frame 
	addi $sp, $sp, 12 
	jr $ra	
	
# Terminating the program
end:	addi $sp, $sp, 4	# Moves stack pointer back (pop the stack frame)
	li $v0, 10 
	syscall
