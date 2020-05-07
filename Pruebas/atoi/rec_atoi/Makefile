GCC_FLAGS = -O0 -mips32 -mlong32 -g -c


rec_atoi_mips: ratoi.S 
	gcc  $(GCC_FLAGS) ratoi.S -o rec_atoi_mips.o

rec_atoi: ratoi.c 
	gcc  $(GCC_FLAGS) ratoi.c -o rec_atoi.o

clean:
	rm *.o


