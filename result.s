.data
string4: .asciiz"NOOOO!"

.globl main
.text
    main:
    li $t0, 8

    sw $t0, 0($sp)

    li.s $f0, 5.6

    s.s $f0, 4($sp)

    lw $t0, 0($sp)
    mtc1 $t0, $f1
    cvt.s.w $f1, $f1

    l.s $f0, 4($sp)

    add.s $f0, $f1, $f0

    s.s $f0, 8($sp)

    l.s $f0, 8($sp)

    li $t0, 50
    mtc1 $t0, $f1
    cvt.s.w $f1, $f1

    c.lt.s $f0, $f1

    bc1f else0
    l.s $f0, 8($sp)

    mov.s $f12, $f0
    li $v0, 2
    syscall

    j endif1
    else0: 

    la $a0, string4
    li $v0, 4
    syscall

    endif1 :
    li $v0, 10
    syscall

