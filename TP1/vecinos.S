#include <regdef.h>

#define SS 32
#define O_N 48
#define O_M 44
#define O_j 40
#define O_i 36
#define O_a 32
#define O_GP 28
#define O_FP 24
#define O_n 20
#define O_x 16
#define O_y 12
#define O_index 8
#define O_k 4
#define O_l 0

		.data
		.align 2

		.text
		.align 2
		.globl vecinos
		.ent vecinos

vecinos:
		.frame  fp, SS, ra
		.set    noreorder
		.cpload t9
		.set    reorder
		subu sp, sp, SS

		sw   gp, O_GP(sp)  	# salvo gp
		sw   fp, O_FP(sp)   # salvo fp
		move fp, sp
		
		sw   a0, O_a(fp)
		sw   a1, O_i(fp)
		sw   a2, O_j(fp)
		sw   a3, O_M(fp)
		
		sw zero, O_n(fp)

		
		li t1, -2 			# t1 es el registro que usaremos de auxiliar para la carga de constantes
		sw t1, O_k(fp)		# guardo el -2 en el stack frame posicion 4 (k = iterador del primer for)
		sw t1, O_l(fp)		# guardo el -2 en el stack frame posicion 0 (l = iterador del segundo for)
		li t1, 1			# t1 = 1 -> es la condicion de corte de ambos for for k<=1 o l<=1

for1:
		lw t2, O_k(fp)  	# cargo en t2 el valor actual de k
		addi t2, t2, 1		# aumento el iterador t2 en 1
		bgt t2, t1, done 	# si el iterador t2 es menor o igual a 1 (t1), salto a etiqueta done
		sw t2, O_k(fp) 		# guardo el nuevo valor de k (aumentado) en el stack frame en posicion 4
		li t1, -2 			# aux = -2
		sw t1, O_l(fp)		# al terminar un ciclo del primer for vuelvo a poner en el valor inicial al iterador del segundo for 

for2:	
		lw t3, O_l(fp)		# cargo en t2 el valor actual de l
		li t1, 1			# t1 = 1
		addi t3, t3, 1		# aumento el iterador t3 en 1
		bgt t3, t1, for1	# si el iterador t3 es menor o igual a 1 (t1), salto a etiqueta for1
		sw t3, O_l(fp)		# guardo el nuevo valor de l (aumentado) en el stack frame en posicion 0
	
		or t1, t3, t2		# k o l = t1
		beqz t1, for2		# si el resultado de k y l es 0 salto a la rtiqueta for2 (continue)

		add t1, a3, a1 		# sumo M + i
		add t1, t1, t2		# sumo (M+i) + k
		rem t1, t1, a3		# resto de (M+i+k) / M = x
		sw t1, O_x(fp)		# guardo el valor de x (t1) en el stack frame posicion 16

		lw t4, O_N(fp)		# recupero el valor de N en t4
		add t1, t4, a2		# sumo N + j
		add t1, t1, t3		# sumo (N+j) + l
		rem t1, t1, t4		# resto de (N+j+l) / N
		sw t1, O_y(fp)		# guardo el valor de y (t1) en el stack frame posicion 12

		lw t1, O_x(fp)		# recupero el valor de x en t1
		mul t4, t4, t1		# multiplico  N * x
		lw t1, O_y(fp)		# recupero el valor de y en t1
 		add t4, t4, t1		# sumo (x*N) + y (t4 = index)
		
		addu t5, a0, t4 	# a la direccion de comienzo del array (a0) le sumo index (unsigned char = 1 byte)
        lb t5, 0(t5)		# t5 es el byte del array en la posicion index
		li t1, 1			# cargo el primer byte de la direccion guardada en t1 (la direccion del string "1")
		bne t5, t1, for2	# salto a la etiqueta for si el caracter "1" es diferente al valor de array[index]
		
		lw t1, O_n(fp)		# recupero el valor de n actual
		addi t1, t1, 1 		# aumento el valor de n
		sw t1, O_n(fp)		# guardo valor de n actual en el stack frame en la posicion 20
		b for2				# salto a la etiqueta for2

done:
		lw v0, O_n(fp)		# obtengo el valor actual de n y lo guardo en el registro de retorno v0
	
        lw fp, O_FP(sp)	# Destruimos el frame.
        addu    sp, sp, SS

        # Retorno
        j ra
        
		.end vecinos
		.align 2
	


