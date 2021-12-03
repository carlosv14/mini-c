.data

.globl main
.text
li $t0, 8

sw $t0, 0($sp)

li $t0, 0

sw $t0, 4($sp)

while0: 

beqz , endWhile1



j while0
endWhile1: 


