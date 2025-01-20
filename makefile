CC = gcc
FLAGS = -Wall -g

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

# for now make all does a test build, possibly will add dll creation later
all: tests.o $(OBJECTS)
	$(CC) $(FLAGS) -o tests tests.o $(OBJECTS)

tests.o:
	$(CC) $(FLAGS) -c tests.c -o tests.o

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -I$(SRC) -c $< -o $@

clean:
	# if on Linux uncomment next line and remove the Windows one
	# rm -f test obj/*.o
	cmd //C del obj\\*.o
	cmd //C del tests.exe tests.o
