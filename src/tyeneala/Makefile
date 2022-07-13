NAME = "s21_decimal"
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

ASNT = #-fsanitize=address -g
# $(ASNT)

COV = #--coverage
CHE = #-lcheck -lm -lpthread

MAIN = main.c

#LIB = ./s21*.c general.c
LIB = out_decimal.c
LOBCT = $(LIB: .c=.o)

SOURCES = $(MAIN) $(LIB)
OBJECTS = $(SOURCES: .c=.o)

EXEFILE = main

all: main
		
main: $(OBJECTS)
	$(CC) $(ASNT) $(COV) $(CHE) $(OBJECTS)  -o ./$(EXEFILE)

.c.o:
	$(CC) $(ASNT) $(COV) $(CFLAGS) $(SOURCES)

clean:
	rm -rf *.o *.a $(EXEFILE)


rebuild: clean all

