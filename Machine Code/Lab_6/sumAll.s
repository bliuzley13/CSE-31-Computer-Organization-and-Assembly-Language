.data
even_sum: .word 0  # Initialize even_sum to 0
odd_sum:  .word 0  # Initialize odd_sum to 0
oddprompt: .asciiz "Sum of odd numbers is: "
evenprompt: .asciiz "Sum of even numbers is: "
newLine: .asciiz "\n"
prompt:   .asciiz "Please enter a number: "

.text
main:
    # Loop to read and process user input
input_loop:
    li $v0, 4             # Load syscall code 4 for print_str
    la $a0, prompt        # Load address of prompt into $a0
    syscall                # Print prompt
    
    li $v0, 5             # Load syscall code 5 for read integer
    syscall                # Read user input
    move $t0, $v0         # Move user input to register $t0 for comparison

    beq $t0, $zero, exit  # Exit loop if user enters 0

    # Check if the input is even
    andi $t1, $t0, 1      # Perform bitwise AND with 1 to check if LSB is 1 (odd) or 0 (even)
    beq $t1, $zero, is_even  # If LSB is 0, it's even
    j is_odd

is_even:
    add $t2, $t2, $t0     # Add even number to even_sum
    j input_loop

is_odd:
    add $t3, $t3, $t0     # Add odd number to odd_sum
    j input_loop

exit:
    li $v0, 4             # Load syscall code 4 for print_str
    la $a0, evenprompt        # Load address of evenprompt into $a0
    syscall
    # Print the sum of even numbers
    li $v0, 1             # Load syscall code 1 for print integer
    move $a0, $t2         # Load even_sum into $a0
    syscall
    li $v0, 4             # Load syscall code 4 for print str
    la $a0, newLine         # Load address of evenprompt into $a0
    syscall  
    
    li $v0, 4             # Load syscall code 4 for print_str
    la $a0, oddprompt        # Load address of oddprompt into $a0
    syscall
    # Print the sum of odd numbers
    li $v0, 1             # Load syscall code 1 for print integer
    move $a0, $t3         # Load odd_sum into $a0
    syscall
    
    li $v0, 10            # Load syscall code 10 for program exit
    syscall

#PseudoCode:
#Initializes even_sum to 0
#Initializes odd_sum to 0

#Loops until user enters 0:
#    Prompts user for number
#    Reads user's input

#    Checks if input is 0:
#        If yes, exit the loop
#    Checks if input is even:
#        If yes, add input to even_sum
#    Check if input is odd:
#        If yes, add input to odd_sum

#Prints even_sum
#Prints odd_sum