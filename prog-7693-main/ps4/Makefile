CC=gcc
FLAGS=-g -Werror -std=c11 -Wall
LIBS=-lm
OUTPUT=bmp

all: $(OUTPUT)


$(OUTPUT): bmp.o transformations.o main.o
	$(CC) $(FLAGS) bmp.o transformations.o main.o $(LIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(FLAGS) -c main.c $(LIBS) -o main.o

bmp.o: bmp.c
	$(CC) $(FLAGS) -c bmp.c $(LIBS) -o bmp.o

transformations.o: transformations.c
	$(CC) $(FLAGS) -c transformations.c $(LIBS) -o transformations.o


clean: 
	rm *.o bmp
