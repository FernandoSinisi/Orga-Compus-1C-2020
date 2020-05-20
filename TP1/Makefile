RM_FLAGS := -f -v

CFLAGS := $(flags)
CFLAGS += -Wall -mips32 -mlong32 -g -O0

ifndef $(cc)
	CC := gcc
else
	CC := $(cc)
endif

ifndef name
	name = out
endif

ifndef path
	path := bin
endif

conway-asm: conway.c matrix.c vecinos.S
	$(CC) $(CFLAGS) -o $(path)/$@ $^

conway: *.c
	$(CC) $(CFLAGS) -o $(path)/$@ $^

help:
	@cat help.txt

video:
	@ffmpeg -f image2 -r 1 -pattern_type glob -i '*.pbm' $(name).avi

.PHONY clean:
	@rm $(RM_FLAGS) *.pbm
	@rm $(RM_FLAGS) $(path)/*
	@rm $(RM_FLAGS) *.avi