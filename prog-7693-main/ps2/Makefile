CC=gcc
CFLAGS=-g -std=c11 -Werror -Wall -Wconversion
LDLIBS=-lm
OUTPUT=ps2
VPATH=src:obj
HEADERS=hof.h k.h ui.h

all: $(OUTPUT)

$(OUTPUT): hof.o k.o ui.o main.c
	$(CC) $(CFLAGS) *.o main.c $(LDLIBS) -o $(OUTPUT)

hof.o: hof.c
	$(CC) $(CFLAGS) -c hof.c $(LDLIBS) -o hof.o

k.o: k.c
	$(CC) $(CFLAGS) -c k.c $(LDLIBS) -o k.o

ui.o: ui.c
	$(CC) $(CFLAGS) -c ui.c $(LDLIBS) -o ui.o


clean: 
	rm -rf $(OUTPUT) *.o
