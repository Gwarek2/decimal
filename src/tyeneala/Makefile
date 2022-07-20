NAME = "s21_decimal"
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

ASNT = #-fsanitize=address -g

COV = --coverage
CHE = -lcheck -lm -lpthread

#MAIN = main.c
MAIN = test_float.c

LIB = ./s21*.c general.c
LOBCT = $(LIB: .c=.o)

SOURCES = $(MAIN) $(LIB) #out_decimal.c
OBJECTS = $(SOURCES: .c=.o)

EXEFILE = main

all: check main
#all: main

check:
	checkmk clean_mode=1 float_test.check > test_float.c

main: $(OBJECTS)
	$(CC) $(ASNT) $(COV) $(CHE) $(OBJECTS)  -o ./$(EXEFILE)

.c.o:
	$(CC) $(ASNT) $(COV) $(CFLAGS) $(SOURCES)

report:
	gcov $(SOURCES) -m -k -f
	lcov -t $(NAME) -o $(NAME).info -c -d .
	genhtml -o report $(NAME).info
	open ./report/index.html

leaks:
	  leaks -atExit -- ./$(EXEFILE)

cpp:
	cppcheck $(SOURCES) ./dev_decimal.h

lint:
	cp /Users/tyeneala/Desktop/my_project/test_C/CPPLINT.cfg ./
	python3 /Users/tyeneala/Desktop/my_project/test_C/cpplint.py --extensions=c $(SOURCES) ./dev_decimal.h

clean:
	rm -rf *.o *.a $(EXEFILE)
	rm -rf *.cfg *.gcno *.gcda *.dSYM *.gcov *.info
	rm -rf ./report


rebuild: clean all

