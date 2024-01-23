
# Variables
CC = gcc
CPP = g++

CFLAGS = -I include

C_SRC = $(wildcard src/*.c)
CPP_SRC = $(wildcard src/*.cpp)
C_OBJ = $(patsubst src/%.c,int/%.o,$(C_SRC))
CPP_OBJ = $(patsubst src/%.cpp,int/%.o,$(CPP_SRC))

PROGRAM_NAME = primes

BIN = bin/$(PROGRAM_NAME)

# Default target
all: directories $(BIN)

$(BIN): $(C_OBJ) $(CPP_OBJ)
	$(CPP) $(CFLAGS) -O2 -o $@ $^

int/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

int/%.o: src/%.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

# Phony targets
.PHONY: clean directories

clean:
	rm -rf int bin

directories: int bin

int:
	mkdir -p int

bin:
	mkdir -p bin
