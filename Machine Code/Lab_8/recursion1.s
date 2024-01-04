.data
prompt: .asciiz "Please enter a number: "
.text

.text
main:
    addi $sp, $sp, -4 	 #Allocates space for local variables (pushes the stack frame)
    li $v0, 4 
    la $a0, prompt 
    syscall	     	 #Displays input prompt

    li $v0, 5
    syscall	     	 #Reads user input
    add  $a0, $zero, $v0 #Nices user input to $a0 register
    jal  recursion	 #Calls the recursion function with user input as argument
    sw $v0, 0($sp)       #Stores return value on stack
    li $v0, 1
    lw $a0, 0($sp)
    syscall		#Prints out returned value
    j end_program	#Jumps to end of program


recursion:
    addi $sp, $sp, -12 #Allocates space for local variables (pushes the stack frame)
    sw   $ra, 0($sp)   #Saves return address on stack
    addi $t0, $zero, -1
    bne  $a0, $t0, not_minus_one
    addi $v0, $zero, 3 #If input is -1, set return value to 3
    j end_recursion

not_minus_one:
    addi $t0, $zero, -2
    bgt  $a0, $t0, not_minus_two
    beq $a0, $t0, equal_minus_two
    addi $v0, $zero, 2 #If input is -1, set return value to 2
    j end_recursion

equal_minus_two:
    addi $v0, $zero, 1 #If input is -1, set return value to 1
    j end_recursion

not_minus_two:
    sw $a0, 4($sp)    #Save current input argument on stack
    addi $a0, $a0, -3 #Prepare new input argument (m-3)
    jal recursion     #Call recursion (m-3)
    sw $v0, 8($sp)    #Save the result from m-3
    lw $a0, 4($sp)    #Restore original input argument (m)
    addi $a0, $a0, -2 #Prepare new input argument (m-2)
    jal recursion     #Call recursion(m-2)
    lw $a0, 4($sp)    #Restore original input argument (m)
    lw $t0, 8($sp)    #Retrieve the result from m - 3
    add $v0, $t0, $v0 #Add the result from m-2 and m-3
    add $v0, $v0, $a0 #Add m to the result
    j end_recursion

end_recursion:
    lw    $ra, 0($sp)#Restore the return address
    addi  $sp, $sp, 12 #Deallocate space for local variable in recursion (pop the stack frame)
    jr    $ra        #Return to the calling function

end_program:
    addi $sp, $sp, 4 #Deallocate space for local variables in main (pop the stack frame)
    li   $v0, 10
    syscall	     #Exit the program
