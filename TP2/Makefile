
RM_FLAGS := -f -v

CFLAGS := $(flags)
CFLAGS += -Wall -g -O0

ifndef $(cc)
	CC := gcc
else
	CC := $(cc)
endif

ifndef $(path)
	path := bin
endif

cache: *.c
	@mkdir -p $(path)
	$(CC) $(CFLAGS) -o $(path)/$@ $^

run:
	@./$(path)/cache $(file)

help:
	@cat help.txt

clean:
	@rm $(RM_FLAGS) $(path)/*

.PHONY: clean help