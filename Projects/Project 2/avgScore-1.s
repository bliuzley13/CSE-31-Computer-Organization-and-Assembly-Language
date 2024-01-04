.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "

newline: .asciiz "\n"
space: .asciiz " "

.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Your code here to compute average and print it
	
	#Own code
	move $t0, $v0    # Move the value in $v0 to $t0
	li $v0, 4        # Load immediate value 4 into register $v0 (syscall for print_string)
	la $a0, str5     # Load address of the string labeled "str5" into $a0
	syscall          # Perform syscall (print_string)

	div $t0, $a1     # Divide the value in $t0 by the value in $a1
	mflo $a0         # Move the quotient of the division into $a0
	li $v0, 1        # Load immediate value 1 into register $v0 (syscall for print_integer)
	syscall          # Perform syscall (print_integer)

	
	#Own code end
	
	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
    	# Your implementation of printList here
    	li $t0, 0                 # Load immediate value 0 into register $t0 (counter initialization)
print_loop:
   	beq $t0, $a1, print_end   # Branch if $t0 equals $a1 to print_end (check if counter reached array size)
    	sll $t1, $t0, 2           # $t1 = $t0 * 4 (calculate the offset for indexing the array)
    	add $t1, $t1, $a0         # $t1 = $t1 + $a0 (calculate the memory address of array element)
   	lw $t2, 0($t1)            # Load word from memory address ($t1) into $t2 (get array element)
	li $v0, 1                 # Load immediate value 1 into $v0 (syscall for print_integer)
 	move $t5, $a0             # Copy $a0 (base address) to $t5 for later use
 	move $a0, $t2             # Move array element value to $a0 for printing
 	syscall                   # Print the integer in $a0
 	li $v0, 4                 # Load immediate value 4 into $v0 (syscall for print_string)
 	la $a0, space             # Load address of string "space" into $a0
    	syscall                   # Print a space
        move $a0, $t5             # Restore the base address to $a0 for array indexing
   	addi $t0, $t0, 1          # Increment counter by 1
   	j print_loop              # Jump back to print_loop
print_end:
    	li $v0, 4                 # Load immediate value 4 into $v0 (syscall for print_string)
    	la $a0, newline           # Load address of string "newline" into $a0
    	syscall                   # Print a newline
    	jr $ra                    # Jump back to the calling function (return address)

	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# Your implementation of selSort here
	li $t0, 0			# int i = 0
	la $t5, orig
	la $t6, sorted
copy_loop:
	beq $t0, $a0, end_copy_loop	# check if i is equal to num scores
	sll $t1, $t0, 2			# j = i * 4
	add $t2, $t5, $t1		# orig += j
	add $t3, $t6, $t1		# sorted += j
	lw $t4, 0($t2)			# int temp = *(orig)
	sw $t4, 0($t3)			# *(sorted) = temp
	addi $t0, $t0, 1		# i += 1
	j copy_loop
end_copy_loop:
	li $t0, 0			# i = 0
	addi $t9, $a0, -1		# int lent = len - 1
nested_loop_outer:
	beq $t0, $t9, end_nested_loop_outer
	move $t1, $t0			# int maxIndex = i
	li $t2, 1
	add $t2, $t2, $t0		# int j = i + 1
nested_loop_inner:
	beq $t2, $a0, end_nested_loop_inner
	sll $t3, $t2, 2			# int h = j * 4
	sll $t4, $t1, 2			# int k = maxIndex * 4
	add $t3, $t3, $t6 		#Bith traverse through sorted array
	add $t4, $t4, $t6
	lw $t3, 0($t3)
	lw $t4 0($t4)
	slt $t7, $t4, $t3
	beq $t7, $0, check_less_than	# if sorted[j] > sorted[maxIndex]
	move $t1, $t2			# maxindex = j
check_less_than:
	addi $t2, $t2, 1
	j nested_loop_inner
end_nested_loop_inner:
	sll $t3, $t1, 2			# int m = maxIndex * 4
	add $t3, $t3, $t6		# m = (sorted + m)
	lw $t2, 0($t3)			# m = sorted[maxIndex]
	sll $t4, $t0, 2			# int n = i * 4
	add $t4, $t4, $t6		# n = sorted + n
	lw $t7, 0($t4)
	sw $t7, 0($t3)
	sw $t2, 0($t4)

	addi $t0, $t0, 1
	j nested_loop_outer
end_nested_loop_outer:
	jr $ra
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
    	# Your implementation of calcSum here
    	bgt $a1, 0, recursive_add  # Branch if $a1 > 0, jump to recursive_add
    	li $v0 , 0                # If $a1 <= 0, load immediate value 0 into $v0 and return
    	jr $ra                    # Return to the calling function
recursive_add:
    	sub $sp, $sp, 12          # Allocate space on the stack for three words
    	sw $ra, 0($sp)            # Save $ra (return address) onto the stack
    	sw $a1, 4($sp)            # Save $a1 onto the stack
    	sw $a0, 8($sp)            # Save $a0 onto the stack
    	sub $a1, $a1, 1           # Decrement $a1 (the counter for recursion)
    	jal calcSum               # Jump and link to calcSum (recursive call)
    	lw $ra, 0($sp)            # Restore $ra from the stack
    	lw $a1, 4($sp)            # Restore $a1 from the stack
    	lw $a0, 8($sp)            # Restore $a0 from the stack
    	addi $sp, $sp, 12         # Restore the stack pointer

    	sub $t0, $a1, 1           # Calculate offset for accessing array element
    	sll $t0, $t0, 2
    	add $t0, $a0, $t0         # Calculate memory address of current array element
    	lw $t0, 0($t0)            # Load the value at the memory address into $t0
    	add $v0, $v0, $t0         # Add the loaded value to $v0 (accumulate sum)
    	jr $ra                    # Return to the calling function