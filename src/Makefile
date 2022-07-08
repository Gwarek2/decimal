KERN := $(shell uname -s)

CC     := gcc
FLAGS  := -Wall -Werror -Wextra -g3
ifdef ASAN
	FLAGS += -fsanitize=address
endif

TEST_FLAGS := -lcheck -lm -lpthread
ifeq ($(KERN),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif
#TEST_FLAGS := $(shell pkg-config --libs check)
COV_FLAGS  := --coverage

INC_DIRS       := ./ core/
TESTS_INC_DIRS := tests/
INC_FLAGS      := $(addprefix -I,$(INC_DIRS))
TEST_INC_FLAGS := $(addprefix -I,$(TESTS_INC_DIRS))

# Static check flags
LINT_DIR   := ../materials/linters/*
LINT       := python3 cpplint.py --extensions=c
LINT_FILES := cpplint.py CPPLINT.cfg
CPPC       := cppcheck --enable=all --suppress=missingIncludeSystem
ALL_C      := $(shell find . -name "*.c")

# Dynamic memory check tool
ifeq ($(KERN),Darwin)
	MEM_TOOL := leaks -atExit --
else
	MEM_TOOL := valgrind --leak-check=full \
                         --show-leak-kinds=all \
                         -q
endif

# Dynamic memory check tool
ifdef LEAKS
	MEM_CHECK := $(MEM_TOOL)
endif

SRCS_H     := decimal_type.h \
              s21_decimal.h \
              core/bit_operations.h \
			  core/core_operations.h
TESTS_H    := tests/test_main.h


SRCS_DIRS     := core/ \
                 arithmetic/ \
		         comparison/ \
                 conversion/
TESTS_DIR     := tests/
COV_DIR       := coverage_info/
OBJ_DIRS      := $(addprefix obj/,$(SRCS_DIRS))
COV_OBJ_DIRS  := $(addprefix $(COV_DIR),$(OBJ_DIRS))


SRCS       := $(addprefix core/,bit_operations.c \
                                core_operations.c) 
CORE_TESTS := $(addprefix $(TESTS_DIR)core/,bit_addition_suite.c \
                                            bit_subtraction_suite.c \
                                            bits_eq_suite.c \
                                            bits_lt_suite.c \
											divide_by_ten_suite.c \
                                            multiply_by_ten_suite.c \
											base_addition_suite.c \
											base_subtraction_suite.c \
                                            base_multiply_suite.c \
                                            base_division_suite.c \
                                            base_fmod_suite.c)
TESTS      := $(TESTS_DIR)test_main.c \
              $(CORE_TESTS)

OBJS       := $(patsubst %.c,obj/%.o,$(SRCS))
COV_OBJS   := $(patsubst %.c,$(COV_DIR)obj/%.o,$(SRCS))


LIB_STATIC := s21_decimal.a
TEST_EXEC  := test_main
TEST_EXEC  := $(TEST_EXEC)
COV_EXEC   := $(COV_DIR)gcov_exec

COV_INFO   := $(COV_DIR)s21_decimal.info
COV_REPORT := $(COV_DIR)index.html

vpath %.c $(SRC_DIRS)

.PHONY: all clean test gcov_report static_analysis

all: test gcov_report

test: $(LIB_STATIC)  $(TESTS_H)
	$(CC) $(FLAGS) $(INC_FLAGS) $(TEST_INC_FLAGS) $(TESTS) $< $(TEST_FLAGS) -o $(TEST_EXEC)
	-$(MEM_CHECK) ./$(TEST_EXEC)

gcov_report: $(COV_OBJS) $(TESTS_H)
	@$(CC) $(FLAGS) $(INC_FLAGS) $(TEST_INC_FLAGS) $(TESTS) $< $(COV_FLAGS) $(TEST_FLAGS) -o $(COV_EXEC)
	-@./$(COV_EXEC)
	@gcov -f $(COV_EXEC) -o $(COV_DIR)
	@lcov -q -c -d $(COV_DIR) -o $(COV_INFO) --exclude "$(TESTS_DIR)*"
	@genhtml -q $(COV_INFO) -o $(COV_DIR)
	@open $(COV_REPORT)

$(LIB_STATIC): $(OBJS)
	@ar -rc $@ $^
	@ranlib $@

# Compile object files for static library
obj/%.o: %.c $(SRCS_H)
	@mkdir -p $(OBJ_DIRS)
	@$(CC) $(FLAGS) $(INC_FLAGS) -c $< -o $@

# Compile object files for gcov_report
$(COV_DIR)obj/%.o: %.c $(SRCS_H)
	@mkdir -p $(COV_OBJ_DIRS)
	@$(CC) $(FLAGS) $(INC_FLAGS) $(COV_FLAGS) -c $< -o $@

static_check:
	@cp ../materials/linters/* .
	-$(LINT) $(ALL_C)
	@-rm $(LINT_FILES)
	-$(CPPC) $(ALL_C)

clean:
	-@rm -rf $(TEST_EXEC) \
             obj \
             $(LIB_STATIC) \
             $(COV_DIR) \
             *.dSYM \
             *.gcda *.gcno
