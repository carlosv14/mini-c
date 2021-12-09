.data

.globl main
.text
li.s $f0, 1.6

s.s $f0, 0($sp)
li.s $f0, 4.78

s.s $f0, 4($sp)
li.s $f0, 6.9

s.s $f0, 8($sp)
li.s $f0, 7.9

s.s $f0, 12($sp)
li.s $f0, 8.7

s.s $f0, 16($sp)

li $t0, 5

sw $t0, 20($sp)

li $t0, 0

sw $t0, 24($sp)

while0: 
lw $t0, 24($sp)

lw $t1, 20($sp)

slt $t0, $t0, $t1

beqz $t0, endWhile1
lw $t1, 24($sp)

li $a0, 4
mult $a0, $t1
mflo $t2
la $t30($sp)
add $t2, $t3, $t2
l.s $f0, 0($t2)


lw $t4, 24($sp)

li $t5, 1

add $t4, $t4, $t5

sw $t4, 24($sp)


j while0
endWhile1: 


