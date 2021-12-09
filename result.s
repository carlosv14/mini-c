.data

.globl main
.text
main: 
li $t0, 5

sw $t0, 0($sp)

li $t0, 0

sw $t0, 4($sp)


li.s $f0, 3.5

s.s $f0, 

li.s $f0, 4.5

s.s $f0, 

li.s $f0, 5.5

s.s $f0, 

while0: 
lw $t0, 4($sp)

lw $t1, 0($sp)

slt $t0, $t0, $t1

beqz $t0, endWhile1
lw $t1, 4($sp)

li $a0, 4
mult $a0, $t1
mflo $t2
la $t3, 8($sp)
add $t2, $t3, $t2
l.s $f0, 0($t2)

mov.s $f12, $f0
li $v0, 2
syscall

lw $t4, 4($sp)

li $t5, 1

add $t4, $t4, $t5

sw $t4, 4($sp)


j while0
endWhile1: 


