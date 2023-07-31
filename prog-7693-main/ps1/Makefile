CC=gcc
CFLAGS=-g -std=c11 -Werror -Wall
LDLIBS=-lm
OUTPUT=ps1
VPATH=src:obj
HEADERS=playfair.h bmp.h

all: $(OUTPUT)

$(OUTPUT): playfair.o bmp.o main.c
	$(CC) $(CFLAGS) *.o main.c $(LDLIBS) -o $(OUTPUT)

playfair.o: playfair.c
	$(CC) $(CFLAGS) -c playfair.c $(LDLIBS) -o playfair.o

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c bmp.c $(LDLIBS) -o bmp.o

clean: 
	rm -rf $(OUTPUT) *.o
