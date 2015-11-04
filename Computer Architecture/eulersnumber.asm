# James Bach 11/23/14
# CDA3100 Homework Assignment 8b
#
# Register use:
#       $a0     syscall parameter
#       $v0     syscall parameter
#       $f0     exp and syscall return value
#       $f12    exp and syscall parameter

	.text
	.globl main
main:
	la $a0, msg_intro 		#print intro message
	li $v0, 4
	syscall
	
	li.s $f1, 999.0			#quit condition single-p 
	
loop: 
	la $a0, msg_prompt 		#prompt request
	li $v0, 4
	syscall
	
	li $v0, 6 				#read as single-prec into $f0
	syscall
	
	c.eq.s $f0, $f1			#
	bc1t exit				#exit if entered number = 999.0   	
	
	la $a0, msg_response 	#prompt response
	li $v0, 4
	syscall
	
	mov.s $f12, $f0			#move to be displayed
	li	$v0, 2				#single precision number selected
	syscall
	
	la $a0, msg_response2 	#display " is "
	li $v0, 4
	syscall	
	
	
	jal exp					#process number in $f12 as parameter
	mov.s $f12, $f0			#move returned $f0 to be displayed
	li	$v0, 2				#single precision number calculated
	syscall
	
	j loop

exit:
	la $a0, msg_done
	li $v0, 4
	syscall


#################################################################
exp:
	addi $sp, $sp, -28   
	swc1 $f1, 0($sp)
	swc1 $f2, 4($sp)
	swc1 $f3, 8($sp)
	swc1 $f4, 12($sp)
	swc1 $f5, 16($sp)
	swc1 $f30, 20($sp)  
	swc1 $f31, 24($sp)       	#saving variables to the stack
	
	# initialization 
	li $t0, 0               	#  is negative flag, 0 = false
	li.s $f0, 1.0               #  sum total
	li.s $f1, 1.0				#  const 1
	li.s $f2, 1.0               #  MAIN COUNTER	
	li.s $f30, 0.0           	#  const 0
	li.s $f31, 0.000000000000001#  const 1e-15

	# leave and set if e^0
	c.eq.s $f30, $f12            # return from 0 entry
	bc1t end_func
	
	 # test parameter for negative
	c.lt.s $f30, $f12          
	bc1t next_term
	li $t0, 1                   #flagged negative
	abs.s $f12, $f12            #process as positive

next_term:
	mov.s $f3, $f1				#reset temp counter
	mov.s $f4, $f12             #reset container for next term
start_loop:                     #loop for x^n/n!
	c.eq.s $f3, $f2             #is counter at current
	bc1t end_loop
	add.s $f3, $f3, $f1         #counter++
	mul.s $f4, $f4, $f12        #x^n
    div.s $f4, $f4, $f3         #divide next term by current to process x/n
	j start_loop	
end_loop:
	div.s $f5, $f4, $f0         #next term / sum	
	c.lt.s $f5, $f31            #test if next too small
	bc1t check_neg              #next is too small
	add.s $f0, $f0, $f4         #update sum  
	add.s $f2, $f2, $f1         #update maincounter
	j next_term

check_neg:
	beq $t0, $0, end_func
	div.s $f0, $f1, $f0         #apply inverse if negative
end_func:
	lwc1 $f1, 0($sp) 			#return variables from the stack
	lwc1 $f2, 4($sp)
	lwc1 $f3, 8($sp)
	lwc1 $f4, 12($sp)
	lwc1 $f5, 16($sp)
	lwc1 $f30, 20($sp)
	lwc1 $f31, 24($sp)
	addi $sp, $sp, 28
	jr $ra 
#################################################################

	     
.data
msg_done:  		.asciiz "Come back soon!\n"
msg_intro: 		.asciiz "Let's test our exponential function!"
msg_prompt:		.asciiz "\nEnter a value for x (or 999 to exit): "
msg_response: 	.asciiz "Our approximation for e^"
msg_response2: 	.asciiz " is "
