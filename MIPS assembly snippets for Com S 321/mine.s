#Programming Assignment 2: Finding the minimum of a set of elements

#Assembler Directives
.data
.word 7
.word 3
.word 17
.word 12
.word 30
.word 2
.word 5
.word 1
.word 16
.word 11
.text
.globl main

#$s0 contains the address of the first
#of the data
main:
lui $s0, 0x1001
ori $s0,$s0,0
addi $t1, $zero, 0    # the count index for the loop stored in t1
addi $t2, $zero, 0    # the index to be incremented to move the array index, set at 0
lw $t5, 0($s0)        # stores the first value of the array into t5
loop: beq $t1, 9 Exit #Exit if Loop is at 9, since we grabbed the first element already
addi $t2, $t2, 4      #increment the array index by 1
add $t3, $s0, $t2     # set t3= baseIndex + 4i
lw $t4, 0($t3)        # loads the element at a[i] into t4
blt $t5, $t4, UpdateHighest     # if currentHigh < a[i]
UpdateLoop: addi $t1, $t1, 1 # loop++
j loop #jump to top of loop
UpdateHighest: lw $t5, 0($t3) #branch here is currentHigh <a[i], update currentHigh ($t5)
j UpdateLoop # go back to update loop to finish the loop out
Exit: li $v0, 1 # print the highest number
add $a0, $zero, $t5
syscall
