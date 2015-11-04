# James Bach 11/23/14
# CDA3100 Homework Assignment 8a
# terms and Polish function
terms:
	addi $sp, $sp, -12
	sw $ra, 0($sp)	        #store $ra variable on stack
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	move $t0, $a0 			#to save for function use
	li $t1, 16 				#maxamount to display
	li $t2, 1 				#currentamount displayed
	
	la	$a0, terms_msg		# print "first 16 terms" msg
	li	$v0, 4
	syscall
	
	move $a0, $t0 			#print first number
	li $v0, 1
	syscall 
	
sequence:
	li $a0, 32  			#print space
	li $v0, 11  
	syscall
	
	move $a0, $t0           #update the parameter
	jal Polish              #get next number
	move $t0, $v0           #save the result
	
	
	move $a0, $v0           #display the new number
	li $v0, 1
	syscall
	
	addi $t2, $t2, 1        #update displaycounter
	bne $t1, $t2, sequence  #leave once displaymax is reached
	
	lw $ra, 0($sp)          #load back $ra
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	addi $sp, $sp, 12         
	jr $ra                  #jump back to main

	
Polish:
	addi $sp, $sp, -16
	sw $ra, 0($sp)          #store $ra variable on stack
	sw $t0, 4($sp)
	sw $t1, 8($sp)
	sw $t2, 12($sp)
	
	li $v0, 0 				#initialize the return
	li $t0, 10				#use for remainder/trunc
	
pol_digits:	
	rem $t1, $a0, $t0 		#get digit
	mul $t1, $t1, $t1 		#square it
	add $v0, $v0, $t1 		#update sum
	div $a0, $a0, $t0 		#remove digit
	bne $a0, $0, pol_digits #leave when all digits processed
	
	
	lw $t2, 12($sp)
	lw $t1, 8($sp)
	lw $t0, 4($sp)
	lw $ra, 0($sp)			#load $ra back from stack
	addi $sp, $sp, 16		
	jr $ra                  #jump back to terms
# Driver program provided by Stephen P. Leach -- written 12/15/08
	.text
	.globl main

main:	la	$a0, intro	# print intro
	li	$v0, 4
	syscall

loop:	la	$a0, req	# request value of n
	li	$v0, 4
	syscall

	li	$v0, 5		# read value of n
	syscall

	ble	$v0, $0, out	# if n is not positive, exit

	move	$a0, $v0	# set parameter for terms procedure

	jal	terms		# call terms procedure

	j	loop		# branch back for next value of n

out:	la	$a0, adios	# display closing
	li	$v0, 4
	syscall

	li	$v0, 10	# exit from the program
	syscall

	.data
intro:	.asciiz  "Welcome to the Polish sequence tester!"
req:	.asciiz  "\nEnter an integer (zero or negative to exit): "
adios:	.asciiz  "Come back soon!\n"
terms_msg: .asciiz "First 16 terms: "