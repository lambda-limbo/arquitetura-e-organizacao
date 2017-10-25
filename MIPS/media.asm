#
#
# Retornar a média de dois números inseridos pelo usuário
#
#
li $v0, 6 # Número referente a syscall para leitura de dados (ponto flutuante de precisão simples)
syscall

mov.s $f1, $f0 # Move o valor lido em $f0 para $f1
li $v0, 6 # Número referente a syscall para leitura de dados (ponto flutuante de precisão simples)
syscall

mov.s $f2, $f0
add.s $f1, $f1, $f2
l.s $f3, divisor
div.s $f1, $f1, $f3

li $v0, 4
la $a0, mensagem
syscall

li $v0, 2
mov.s $f12, $f1
syscall
li $v0, 10
syscall

.data
	mensagem:.ascii "A média é: "
	divisor:.float 2