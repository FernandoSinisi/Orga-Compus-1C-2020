RM_FLAGS := -f -v

ifndef $(CFLAGS)
CFLAGS := -Wall
endif

ifndef $(CC)
CC := gcc
endif

ifndef $(NAME)
NAME = out
endif

HELP_MSG := "\nCompilar: \n	make conway		-Compila el programa version C \n	make conway-asm 	-Compila el programa version MIPS Assembly \n\nCorrer:\n	./bin/conway <iteraciones> <filas> <columnas> <entrada> [-o <output_prefix>]\n\nEjemplo:\n	./bin/conway 5 10 10 glider -o estado\n	Correra el programa con 5 iteraciones, indicando que la matriz es de 10x10\n	el archivo de entrada glider y las salidas deben tener el nombre 'estado_nnn.pbm'\n\nCrear video:\n	make video NAME=<nombre_video>	-El parametro NAME se puede omitir en cuyo caso se usara 'out'\n\nPara usar otro compilador (por defecto gcc) agregar el parametro CC, ejemplo:\n	make conway CC=clang\n"

conway-asm: conway.c matrix.c vecinos.S
	$(CC) $(CFLAGS) -o bin/$@ $^

conway: *.c
	$(CC) $(CFLAGS) -o bin/$@ $^

help:
	@echo $(HELP_MSG)

video:
	@ffmpeg -f image2 -r 1 -pattern_type glob -i '*.pbm' $(NAME).avi

.PHONY clean:
	@rm $(RM_FLAGS) *.pbm
	@rm $(RM_FLAGS) bin/*
	@rm $(RM_FLAGS) *.avi