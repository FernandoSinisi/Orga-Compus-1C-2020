## Scope
Se propone codificar una versión reducida de la función ``` int atoi(char *)```, implementando la conversión
en MIPS32. Se implementan dos funciones
* `int my_atoi(char *)`
* `int loop_atoi(char *) / int rec_atoi(int, char*) `

## Construcción
`$ make` 

* latoi : Implementa atoi mediante un loop
* latoi_mips : Implementa el loop en Mips32

* ratoi: Implementa atoi mediante una función recursiva
* ratoi_mips: Implementa la función recursiva en Mips32


* atoi_mips_loop_wrapper 
* atoi_mips_rec_wrapper

## Próximos pasos
Queda como ejercicio implementar mas casos de prueba. Por ejemplo
* Filtrar espacios
* Retornar si se encuentra un caracter que no corresponde a un dígito
