CC = gcc
FLAGS = -Wall -Werror -Wextra
C11 = -std=c11

all: build

build: clean
	$(CC) $(FLAGS) $(C11) grep.c -o grep

clean:
	rm -rf grep
