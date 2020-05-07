GCC_FLAGS = -O0 -mips32 -mlong32 -g -c


atoi_loop_mips: atoi_loop_mips.S
	gcc  $(GCC_FLAGS) atoi_loop_mips.S -o atoi_loop_mips.o

atoi_loop: atoi_loop.c 
	gcc  $(GCC_FLAGS) atoi_loop.c -o atoi_loop.o

clean:
	rm atoi_loop_mips.o atoi_loop.o


