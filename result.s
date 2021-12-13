.data
string0: .asciiz"X= "
string1: .asciiz"\n"
string2: .asciiz"Y= "
string3: .asciiz"\n"
string4: .asciiz"Add: "
string5: .asciiz"\n"
string6: .asciiz"Sub: "
string7: .asciiz"\n"
string8: .asciiz"Mul: "
string9: .asciiz"\n"
string10: .asciiz"Div: "
string11: .asciiz"\n"

.globl main
.text
sum: 
addiu $sp, $sp, -12

sw $ra, 0($sp)

sw $a0, 4($sp)
sw $a1, 8($sp)
l.s $f0, 4($sp)

l.s $f1, 8($sp)

add.s $f0, $f0, $f1

mfc1 $v0, $f0


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra
substr: 
addiu $sp, $sp, -12

sw $ra, 0($sp)

sw $a0, 4($sp)
sw $a1, 8($sp)
l.s $f0, 4($sp)

l.s $f1, 8($sp)

sub.s $f0, $f0, $f1

mfc1 $v0, $f0


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra
multi: 
addiu $sp, $sp, -12

sw $ra, 0($sp)

sw $a0, 4($sp)
sw $a1, 8($sp)
l.s $f0, 4($sp)

l.s $f1, 8($sp)

mul.s $f0, $f0, $f1

mfc1 $v0, $f0


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra
divi: 
addiu $sp, $sp, -12

sw $ra, 0($sp)

sw $a0, 4($sp)
sw $a1, 8($sp)
l.s $f0, 4($sp)

l.s $f1, 8($sp)

div.s $f0, $f0, $f1

mfc1 $v0, $f0


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra
main: 
addiu $sp, $sp, -12

sw $ra, 0($sp)


li.s $f0, 150.56

s.s $f0, 4($sp)

li.s $f0, 10.25

s.s $f0, 8($sp)


la $a0, string0
li $v0, 4
syscall

l.s $f0, 4($sp)

mov.s $f12, $f0
li $v0, 2
syscall


la $a0, string1
li $v0, 4
syscall


la $a0, string2
li $v0, 4
syscall

l.s $f0, 8($sp)

mov.s $f12, $f0
li $v0, 2
syscall


la $a0, string3
li $v0, 4
syscall


la $a0, string4
li $v0, 4
syscall

l.s $f0, 4($sp)

l.s $f1, 8($sp)

mfc1 $a0, $f0
mfc1 $a1, $f1
jal sum
mtc1 $v0, $f0

mov.s $f12, $f0
li $v0, 2
syscall


la $a0, string5
li $v0, 4
syscall


la $a0, string6
li $v0, 4
syscall

l.s $f0, 4($sp)

l.s $f1, 8($sp)

mfc1 $a0, $f0
mfc1 $a1, $f1
jal substr
mtc1 $v0, $f0

mov.s $f12, $f0
li $v0, 2
syscall


la $a0, string7
li $v0, 4
syscall


la $a0, string8
li $v0, 4
syscall

l.s $f0, 4($sp)

l.s $f1, 8($sp)

mfc1 $a0, $f0
mfc1 $a1, $f1
jal multi
mtc1 $v0, $f0

mov.s $f12, $f0
li $v0, 2
syscall


la $a0, string9
li $v0, 4
syscall


la $a0, string10
li $v0, 4
syscall

l.s $f0, 4($sp)

l.s $f1, 8($sp)

mfc1 $a0, $f0
mfc1 $a1, $f1
jal divi
mtc1 $v0, $f0

mov.s $f12, $f0
li $v0, 2
syscall


la $a0, string11
li $v0, 4
syscall


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra

