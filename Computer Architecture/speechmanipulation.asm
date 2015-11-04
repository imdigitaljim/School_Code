.data 

dialog	:.asciiz "BEDFORD 
Coward of France! how much he wrongs his fame,
Despairing of his own arm's fortitude,
To join with witches and the help of hell!

BURGUNDY 
Traitors have never other company.
But what's that Pucelle whom they term so pure?TALBOT 
A maid, they say.

BEDFORD 
A maid! and be so martial!

BURGUNDY 
Pray God she prove not masculine ere long,
If underneath the standard of the French
She carry armour as she hath begun.

TALBOT 
Well, let them practise and converse with spirits:
God is our fortress, in whose conquering name
Let us resolve to scale their flinty bulwarks.

BEDFORD 
Ascend, brave Talbot; we will follow thee.

TALBOT 
Not all together: better far, I guess,
That we do make our entrance several ways;
That, if it chance the one of us do fail,
The other yet may rise against their force.

BEDFORD 
Agreed: I'll to yond corner.

BURGUNDY 
And I to this.

TALBOT 
And here will Talbot mount, or make his grave.
Now, Salisbury, for thee, and for the right
Of English Henry, shall this night appear
How much in duty I am bound to both.

Sentinels 
Arm! arm! the enemy doth make assault!

ALENCON 
How now, my lords! what, all unready so?

BASTARD OF ORLEANS 
Unready! ay, and glad we 'scaped so well.

REIGNIER 
'Twas time, I trow, to wake and leave our beds,
Hearing alarums at our chamber-doors.

ALENCON 
Of all exploits since first I follow'd arms,
Ne'er heard I of a warlike enterprise
More venturous or desperate than this.

BASTARD OF ORLEANS 
I think this Talbot be a fiend of hell.

REIGNIER 
If not of hell, the heavens, sure, favour him.

ALENCON 
Here cometh Charles: I marvel how he sped.

BASTARD OF ORLEANS 
Tut, holy Joan was his defensive guard.

Enter CHARLES and JOAN LA PUCELLE

CHARLES 
Is this thy cunning, thou deceitful dame?
Didst thou at first, to flatter us withal,
Make us partakers of a little gain,
That now our loss might be ten times so much?

JOAN LA PUCELLE 
Wherefore is Charles impatient with his friend!
At all times will you have my power alike?
Sleeping or waking must I still prevail,
Or will you blame and lay the fault on me?
Improvident soldiers! had your watch been good,
This sudden mischief never could have fall'n.

CHARLES 
Duke of Alencon, this was your default,
That, being captain of the watch to-night,
Did look no better to that weighty charge.

ALENCON 
Had all your quarters been as safely kept
As that whereof I had the government,
We had not been thus shamefully surprised.

BASTARD OF ORLEANS 
Mine was secure.

REIGNIER 
And so was mine, my lord.

CHARLES 
And, for myself, most part of all this night,
Within her quarter and mine own precinct
I was employ'd in passing to and fro,
About relieving of the sentinels:
Then how or which way should they first break in?

JOAN LA PUCELLE 
Question, my lords, no further of the case,
How or which way: 'tis sure they found some place
But weakly guarded, where the breach was made.
And now there rests no other shift but this;
To gather our soldiers, scatter'd and dispersed,
And lay new platforms to endamage them.

Soldier 
I'll be so bold to take what they have left.
The cry of Talbot serves me for a sword;
For I have loaden me with many spoils,
Using no other weapon but his name.

Exit

SCENE II. Orleans. Within the town.

Enter TALBOT, BEDFORD, BURGUNDY, a Captain, and others 

BEDFORD 
The day begins to break, and night is fled,
Whose pitchy mantle over-veil'd the earth.
Here sound retreat, and cease our hot pursuit.

Retreat sounded

TALBOT 
Bring forth the body of old Salisbury,
And here advance it in the market-place,
The middle centre of this cursed town.
Now have I paid my vow unto his soul;
For every drop of blood was drawn from him,
There hath at least five Frenchmen died tonight.
And that hereafter ages may behold
What ruin happen'd in revenge of him,
Within their chiefest temple I'll erect
A tomb, wherein his corpse shall be interr'd:
Upon the which, that every one may read,
Shall be engraved the sack of Orleans,
The treacherous manner of his mournful death
And what a terror he had been to France.
But, lords, in all our bloody massacre,
I muse we met not with the Dauphin's grace,
His new-come champion, virtuous Joan of Arc,
Nor any of his false confederates.

BEDFORD 
'Tis thought, Lord Talbot, when the fight began,
Roused on the sudden from their drowsy beds,
They did amongst the troops of armed men
Leap o'er the walls for refuge in the field.

BURGUNDY 
Myself, as far as I could well discern
For smoke and dusky vapours of the night,
Am sure I scared the Dauphin and his trull,
When arm in arm they both came swiftly running,
Like to a pair of loving turtle-doves
That could not live asunder day or night.
After that things are set in order here,
We'll follow them with all the power we have.

Enter a Messenger

Messenger 
All hail, my lords! which of this princely train
Call ye the warlike Talbot, for his acts
So much applauded through the realm of France?

TALBOT 
Here is the Talbot: who would speak with him?

Messenger 
The virtuous lady, Countess of Auvergne,
With modesty admiring thy renown,
By me entreats, great lord, thou wouldst vouchsafe
To visit her poor castle where she lies,
That she may boast she hath beheld the man
Whose glory fills the world with loud report.

BURGUNDY 
Is it even so? Nay, then, I see our wars
Will turn unto a peaceful comic sport,
When ladies crave to be encounter'd with.
You may not, my lord, despise her gentle suit.

TALBOT 
Ne'er trust me then; for when a world of men
Could not prevail with all their oratory,
Yet hath a woman's kindness over-ruled:
And therefore tell her I return great thanks,
And in submission will attend on her.
Will not your honours bear me company?

BEDFORD 
No, truly; it is more than manners will:
And I have heard it said, unbidden guests
Are often welcomest when they are gone.

TALBOT 
Well then, alone, since there's no remedy,
I mean to prove this lady's courtesy.
Come hither, captain.

\n\n"

opening:.asciiz "TALBOT"

	.text
	.globl main

main:	
	la $a0, dialog
	li $v0, 4
	syscall

	la $a0, dialog		#Load Speech Address
	la $a1, opening		#Load Name Address
	jal cov_longest

	beq $v0, $0, done

	la $a0, dialog
	li $v0, 4
	syscall

done:	li $v0, 10		# Exit
	syscall

#------------------------------------------------
cov_longest:
	addi $sp, $sp, -4
	sw $ra, 0($sp)					#save the return address on the stack
	li $s0, 0						#value of longest length of Speech
	li $s2, 10						#newline byte
iterate_speech:
	la $a1, opening
	jal find_next_sentence			#returns	$v0 with address of first byte of the name
	beq $v0, $0, end_function
	ori $a0, $v0, 0
adjust_start:
	lb $t0, 0($a0)
	beq $s2, $t0, next_function
	addi $a0, $a0, 1
	j adjust_start
next_function:
	addi $a0, $a0, 1
	ori $s1, $a0, 0					#save the address of the v0 (start address of speech)	
	jal get_to_end
	
	sub $t1, $v0, $s0 				#  t1 =  newValue - oldValue
	bltz $t1, iterate_speech		#  branch if newValue < oldValue
	add $s0, $v0, $0
	ori $s3, $s1, 0					#save the address of the longest speech
	j iterate_speech
end_function:
	beq $s0, $0, quit		      	#end if no speech was found 
	addi $v0, $0, 1		 			#set v0 = 1 
	add $a1, $0, $s0
	ori $a0, $s3, 0
	jal cov_str						 #convert the speech to caps
quit:
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra				
#------------------------------------------------
#------------------------------------------------
find_next_sentence:
	addi $sp, $sp, -4
	sw $a1, 0($sp)				#	save the begin address on the stack.
	ori $v0, $a0, 0
	lb $t0, 0($a0)
	lb $t1, 0($a1)
loop:
	bne $t0, $t1, not_speech
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	lb $t0, 0($a0)
	lb $t1, 0($a1)
	beq $t1, $0, check_speech
	j loop
check_speech:
	addi $a0, $a0, 1
	lb $t0, 0($a0)
	beq $t0, $s2, end_next_sentence
	j loop
not_speech:
	lw $a1, 0($sp)					# 	reset name
	lb $t1, 0($a1)
	addi $a0, $a0, 1
	lb $t0, 0($a0)
	ori $v0, $a0, 0
	beq $t0, $0, nofind_end
	j loop
nofind_end: 
	add $v0, $0, $0
end_next_sentence:
	lw $a1, 0($sp)
	addi $sp, $sp, 4
jr $ra 		
#------------------------------------------------
#------------------------------------------------
get_to_end:
	li $v0, 0					#	initialize return variable
	li $t3, 2					#	init counter
	lb $t0, 0($a0)
end_check:
	bne $t0, $s2, not_end	
	addi $t3, $t3, -1
	beq $t3, $0, end_get_to		#	checks the carriage counter
not_end:
	addi $a0, $a0, 1
	addi $v0, $v0, 1
	lb $t0, 0($a0)
	beq $t0, $s2, end_check
	li $t3, 2					#	reset counter
	j not_end
end_get_to:	
jr $ra
#------------------------------------------------
#------------------------------------------------
cov_str:
	li $t0, 97 				#a
	li $t1, 122 			#z
	lb $t2, 0($a0)
cov_str_loop:
	sub $t3, $t2, $t0		# 	14-97a check if lowercase
	bltz $t3, not_lower		#branch on ISNT lowercase
	sub $t3, $t1, $t2		#	122z-155 check if lowercase 
	bltz $t3, not_lower		#branch on ISNT lowercase
	sub $t2, $t2, 32
	sb $t2, 0($a0)
not_lower:
	addi $a0, $a0, 1
	lb $t2, 0($a0)
	bne $t2, $s2, cov_str_loop
	addi $a0, $a0, 1
	lb $t2, 0($a0)
	bne $t2, $s2, cov_str_loop
	jr $ra				
#------------------------------------------------
