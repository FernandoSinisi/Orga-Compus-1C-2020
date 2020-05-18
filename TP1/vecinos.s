.text

.abicalls
.align 2

.globl vecinos # Se puede referenciar desde otros archivos
.set nomips16 # Para que no genere codigo mips16
.ent vecinos
.type vecinos, @function # vecinos es una funcion

vecinos:
	# No se crea stack ya que es funcion hoja y solo se usan registros temporales
	# ".cpload is only needed for functions which reference global data or addresses" --> ¿Es necesario aca?
	.set    noreorder
     .cpload $t9
     .set    reorder
	li $t0, 0 # Contador inicializado en 0
	li $t1, -1 # k = -1
	li $t2, -1 # l = -1
	li $t3, 1 # Extremo superior del for
	

for1:
	ble $t3, $t1, done
	addi $t1, $t1, 1
	li $t2, -1 # Reseteo a l a -1 luego de cada iteracion
	j for2
	
for2:
	ble $t3, $t2, for1
	addi $t4, $t1, -1 # Auxiliar para usar el valor de k correcto para la iteracion actual
	or $t5, $t4, $t2 # Me fijo si k y l son cero
	beqz $t5, for2 # si es asi hago continue
	add $t6, $a1, $a3 # Sumo M + i + k y guardo en $t6 que es X
	add $t6, $t6, $t4
	rem $t6, $t6, $a3 #  Le aplico %M

	# FALTA OBTENER N QUE COMO ES EL QUINTO PARAMETRO ESTA EN EL STACK Y HACER LOS MISMO QUE PARA X
	
	

done:
	li $v0, 0 # Lo seteamos a 0 por la duda
	add $v0, $v0, $t0 #Guardamos el resultado en el registro de retorno($v0)
	jr $ra # Return

.end vecinos
	


