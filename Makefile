# Makefile for C basics

#CC = gcc
# -g : allows use of GNU Debugger
# -Wall : show all warnings
FLAGS = -g -Wall

OUT = main
SRC = fork_and_exec.c

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(FLAGS) -o $@ $?

# 'clean' rule for remove non-source files
# To use, call 'make clean'
# Note: you don't have to call this in between every
#       compilation, it's only in case you need to
#       clean out your directory for some reason.
clean:
	@# Using the '@' sign suppresses echoing
	@# the line while the command is run
	@rm -f $(OUT)

test: all
	./$(OUT)
