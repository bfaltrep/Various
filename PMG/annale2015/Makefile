SRC = $(wildcard *.c)
BIN = $(SRC:.c=)

CFLAGS = -fopenmp -g -Wall -Wextra -Werror

all : $(BIN)

$(BIN) : % : %.c ndames.h
