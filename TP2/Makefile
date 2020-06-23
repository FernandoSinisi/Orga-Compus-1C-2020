
RM_FLAGS := -f -v

CFLAGS := $(flags)
CFLAGS += -Wall -g -O0

ifndef $(cc)
	cc := gcc
endif

ifndef $(path)
	path := bin
endif

cache: *.c
	@mkdir -p $(path)
	$(cc) $(CFLAGS) -o $(path)/$@ $^

run:
	@./$(path)/cache $(file)

help:
	@cat help.txt

clean:
	@rm $(RM_FLAGS) $(path)/*

.PHONY: clean help run