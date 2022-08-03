

.data

	matrizA: .word32 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 ; Matriz A

	matrizB: .word32 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 ; Matriz B

	matrizProduto: .word32 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ; Matriz Produto




.code

	ADDI	R16, R0, matrizProduto
	ADDI	R17, R0, matrizA
	ADDI	R18, R0, matrizB

	ADDI	R23, R0, 10   	; Dimensao da matriz

	ADDI 	R10, R0, 0 		; iterador i
	ADDI 	R9, R0, 0 		; iterador j
	ADDI 	R8, R0, 0 		; iterador k
	

	ADDI    R11, R0, 0 		; Guarda soma/multiplicação
	ADDI 	R12, R0, 0 		; iterador auxiliar
	ADDI 	R13, R0, 0 		; Soma auxiliar
	ADDI 	R14, R0, 0 		; Guarda a soma auxiliar de m1
	ADDI 	R15, R0, 0 		; Guarda a soma auxiliar de m2
	ADDI	R19, R0, 0 	    ; Iterador da matriz produto





FOR:								; laço mais externo
	BEQ 	R10, R23, DONE 		

FOR_2:								; laço do meio
	BEQ 	R8, R23, POINT_2
	ADDI    R11, R0, 0

FOR_3:								; laço mais interno
	BEQ 	R9, R23, POINT

ACESS_M1: 							; Acessar a matriz 1
	BEQ 	R12, R23, WHILE3_1
	ADD 	R13, R13, R10
	ADDI 	R12, R12, 1
	J 		ACESS_M1

WHILE3_1: 
	ADD 	R12, R13, R9
	SLL 	R12, R12, 2
	LB 		R14, matrizA(R12)
	ADDI 	R12, R0, 0
	ADDI 	R13, R0, 0 

ACESS_M2: 								; Acessar a matriz 2
	BEQ 	R12, R23, WHILE3_2
	ADD 	R13, R13, R9
	ADDI 	R12, R12, 1
	J 		ACESS_M2

WHILE3_2:
	ADD 	R12, R13, R8
	SLL 	R12, R12, 2
	LB 		R15, matrizB(R12)
	ADDI 	R12, R0, 0
	ADDI 	R13, R0, 0

MULTIPLY: 								; Multiplica as matrizes
	BEQ 	R13, R14, CONT_FOR3
	ADD 	R12, R12, R15
	ADDI 	R13, R13, 1
	J 		MULTIPLY

CONT_FOR3:
	ADD 	R11, R11, R12
	ADDI 	R9, R9, 1
	ADDI 	R12, R0, 0
	ADDI 	R13, R0, 0
	J 		FOR_3

POINT:
	ADDI 	R8, R8, 1
	SB 		R11, matrizProduto(R19)
	ADDI 	R19, R19, 4
	ADDI 	R9, R0, 0
	J 		FOR_2

POINT_2:
	ADDI 	R10, R10, 1
	ADDI 	R8, R0, 0
	J		FOR

DONE:
	syscall 0

