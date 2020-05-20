#include<sys/regdef.h>

#define SS 32
#define O_N 48
#define O_M 44
#define O_j 40
#define O_i 26
#define O_a 32
#define O_GP 28
#define O_FP 24
#define O_n 20
#define O_x 16
#define O_y 12
#define O_index 8
#define O_k 4
#define O_l 0

.text

.abicalls
.align 2

.globl vecinos
.set nomips16
.ent vecinos
.type vecinos, @function

vecinos:
	/*".cpload is only needed for functions which reference global data or addresses" --> ¿Es necesario aca? */
	.set    noreorder
	.cpload t9
	.set    reorder
	subu sp, sp, SS
	
	/* Saved Register Area */
	sw   gp, O_GP(sp)
	sw   fp, O_FP(sp)
	move fp, sp

	/* Store in Argument Building Area */
	sw   a0, O_a(fp)
	sw   a1, O_i(fp)
	sw   a2, O_j(fp)
	sw   a3, O_M(fp)

	/* Local and temporary area */
	sw zero, O_n(fp)

	/* Inicio de funcion */
	li t1, -2
	/* k = -2
	* inicializo en -2 porque en la primera iteracion se suma 1 */
	sw t1, O_k(fp)
	sw t1, O_l(fp)
	/* t2 = 1 */
	li t2, 1

for1:
	/* for(k=-1; k<=1; k++) { */
	/* cargar k */
	lw t3, O_k(fp)
	/* if (k == 1) goto done */
	ble t3, t2, done
	/* k++;  */
	addi t3, t3, 1
	/* guardar k */
	sw t3, O_k(fp) 
	/* l = -2; */
	sw t1, O_l(fp)

for2:	
	/* for(l=-1; l<=1; l++) {
	cargar l */
	lw t3, O_l(fp)
	/* if (l = 1) goto for1 */
	ble t3, t2, for1
	/* l++; */
	addi t3, t3, 1
	/* guardar l */
	sw t3, O_l(fp)
	/* cargar k */
	lw t4, O_k(fp)
	/* if (l == k == 0) continue (goto for2) */
	or t5, t4, t2
	beqz t5, for2

	/* cargar i */
	lw t3, O_i(fp)
	/* cargar M */
	lw t4, O_M(fp)
	/* cargar k */
	lw t5, O_k(fp)
	/* x = M + i */
	add t6, t4, t3
	/* x = x + k */
	add t6, t6, t5
	/* x = x % M */
	rem t6, t6, t4
	/* guardar x */
	sw t6, O_x(fp)

	/* cargar j */
	lw t3, O_j(fp)
	/* cargar N */
	lw t4, O_N(fp)
	/* cargar l */
	lw t5, O_l(fp)
	/* y = N + j */
	add t6, t4, t3 
	/* y = y + l */
	add t6, t6, t5
	/* y = y % N */
	rem t6, t6, t4
	/* guardar y */
	sw t6, O_y(fp)

	/* cargar N */
	lw t3, O_N(fp)
	/* cargar x */
	lw t4, O_x(fp)
	/* cargar y */
	lw t5, O_y(fp)
	/* index = N*x */
	mul t6, t3, t4
	/* index = index + y */
	add t6, t6, t5
	/* guardar index */
	sw t6, O_index(fp)

	/* cargar a */
	lw t3, O_a(fp)
	/* cargar index */
	lw t4, O_index(fp)
	/* t6 = 4*index + a */
	li t5, 4
	mul t6, t4, t5
	add t6, t6, t3
	/* t7 = a[index] */
	lw t7, 0(t6)

	/* 1 => t3 */
	li t3, 1
	/* if (a[index] != 1) goto "j for2" */
	bne t7, t3, 12
	/* cargar n */
	lw t4, O_n(fp)
	/* n++; */
	addi t4, t4, 1 
	/* guardar n */ 
	sw t4, O_n(fp)

	j for2

done:
	li v0, 0 /* Lo seteamos a 0 por la duda */
	add v0, v0, t0 /* Guardamos el resultado en el registro de retorno(v0) */
	jr ra /* Return */

.end vecinos
	


