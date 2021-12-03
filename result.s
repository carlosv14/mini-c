.data

.globl main
.text
main:
li $t0, 8

sw $t0, 0($sp)

li.s $f0, 5.6

s.s $f0, 4($sp)

lw $t0, 0($sp)
mtc1 $t0, $f2
cvt.s.w $f2, $f2

l.s $f1, 4($sp)

add.s $f1, $f2, $f1

s.s $f1, 8($sp)

l.s $f2, 8($sp)

mov.s $f12, $f2
li $v0, 2
syscall
li $v0, 10
syscall


