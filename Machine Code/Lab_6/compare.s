.data
n:      .word 25         # Declares variable n set to 25
str1:   .asciiz "Less than\n"                 # Declares str1
str2:   .asciiz "Less than or equal to\n"     # Declares str2
str3:   .asciiz "Greater than\n"              # Declares str3
str4:   .asciiz "Greater than or equal to\n"  # Declares str4

.text
main:
    # Reads integer from user
    li $v0, 5           # Syscall code 5 to read integer
    syscall             # Makes syscall to read integer
    move $t0, $v0       # Moves user input to register $t0 for comparison

    # Code compares user input with n (25)
    lw $t1, n           # Loads n into $t1
    slt $t2, $t0, $t1   # Sets $t2 to 1 if $t0 < $t1, else 0

    # Compares user input less than n
    beq $t2, $zero, greater_equal   # If not less than, jumps to greater_equal
    li $v0, 4           # Load syscall code 4 for print_str
    la $a0, str1        # Load address of str1 into $a0
    syscall             # Make the syscall to print "Less than"
    j end_program       # Jumps to end of program

greater_equal:
    # Compares user input greater than or equal to n
    bge $t0, $t1, greater        # If greater or equal, jumps to greater
    li $v0, 4           # Load syscall code 4 for print_str
    la $a0, str4        # Load address of str2 into $a0
    syscall             # Make the syscall to print "Greater than or equal to"
    j end_program       # Jumps to end of program

greater:
    # Compare if the user input is greater than n
    bgt $t0, $t1, less_equal     # If greater, jump to less_equal
    li $v0, 4           # Load syscall code 4 for print_str
    la $a0, str4        # Load address of str3 into $a0
    syscall             # Make the syscall to print "Greater than"
    j end_program       # Jumps to end of program

less_equal: #(Greater than or equal to??)
    # Compare if the user input is less than or equal to n
    li $v0, 4           # Load syscall code 4 for print_str
    la $a0, str3        # Load address of str4 into $a0
    syscall             # Make the syscall to print "Greater than or equal to"

end_program:
    li $v0, 10          # Load syscall code 10 for program exit
    syscall             # Make the syscall to exit program