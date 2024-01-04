		.data
x:		.word 1	
y:		.word 2
z:		.word 3
m:		.word 15
b:		.word 2
str1:		.asciiz "p+q: "
str2:		.asciiz "\n"

		.text

MAIN:		la $t0, x
		lw $s0, 0($t0) 	#s0=x
		la $t0, y
		Lw $s1, 0($t0)  #s1=y
		la $t0, z
		lw $s2, 0($t0)	#s1=y

		#Calls sum x
		add $s4, $s0, $zero # Set a0 as input argument for SUM
		
		add $s5, $s1, $zero # Set a0 as input argument for SUM
		add $s6, $s2, $zero # Set a0 as input argument for SUM
		
		add $t3, $t0, $s1
		add $t3, $t3, $t2
		
		jal SUM
		add $v0, $t3, $v0
		add $s7, $s7, $v0
		addi $a0, $s7, 0
		li $v0, 1
		syscall
		j END

SUM:		addi $sp, $sp, -12
		sw $ra, 8($sp)
		sw $s0, 4($sp)
		sw $s1, 0($sp)
		
		add $a0, $s0, $s2
		add $a1, $s1, $s2
		add $a2, $s0, $s1
		jal SUB
		addi $t2, $v0, 0
		lw $s1, 0($sp)
		lw $s0, 4($sp)
		lw $ra,	8($sp)
		addi $sp, $sp, 12
		
		addi $sp, $sp, -12
		sw $ra,	8($sp)
		sw $s0, 4($sp)
		sw $s1, 0($sp)
		sub $a0, $s0, $s2
		sub $a1, $s1, $s0
		add $a2, $s1, $s1
		jal SUB
		add $v0, $v0, $t2
		lw $s1, 0($sp)
		lw $s0, 4($sp)
		lw $ra, 8($sp)
		addi $sp, $sp, 12
		addi $t4, $v0, 0
		
		li $v0, 4
		la $a0, str1
		syscall
		
		addi $v0, $t4, 0
		
		addi $a0, $v0, 0
		li $v0, 1
		syscall
		
		addi $v0, $t4, 0
		
		li $v0, 4
		la $a0, str2
		syscall
		
		addi $v0, $t4, 0
		
		jr $ra
		
SUB:		addi $sp, $sp, -4
		sub $t1, $a1, $a0
		sllv $v0, $t1, $a2
		addi $sp, $sp, 4
		jr $ra
		
		
END:
