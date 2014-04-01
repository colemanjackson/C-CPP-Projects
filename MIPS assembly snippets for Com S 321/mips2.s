#Assembler Directives
.data
.word 7
.word 3
.word 1
.word 12
.word 10
.word 2
.word 5
.word 9
.word 16
.word 11
.text
.globl main

main:
add $s0, $zero, $zero
add $t0, $zero, $zero
#$s0 contains the address of the first element of the first array
lui $s0, 0x1001
ori $s0,$s0,0
#$t0 contains the address of the first element of the second array
lui $t0, 0x1001
ori $t0, $t0, 0x0040
addi $t1, $zero, 0 # loop count
Loop: beq $t1, 10, Exit # if i == 10 GOTO Exit, end program
lw $t2 0($s0) #get first element from first array
sw $t2 0($t0) # store in second array
addi $s0, $s0, 4 #increase the offset of 1st array by 1
addi $t0, $t0, 4 #increase the offset of second array by 1
addi $t1, $t1, 1 #increment loop count
j Loop
Exit: li $v0, 10
      syscall
