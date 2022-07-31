include config.mk

.PHONY: all clean test gcov_report static_check

all: build test gcov_report

test: build $(TESTS_H)
	$(CC) $(FLAGS) $(INC_FLAGS) $(TEST_INC_FLAGS) $(TESTS) -L. -l$(BUILD_NAME) $(TEST_FLAGS) -o $(TEST_EXEC)
	-$(MEM_CHECK) ./$(TEST_EXEC)

gcov_report: $(COV_OBJS)
	mkdir -p $(COV_DIR)
	gcovr -b -p -d --html-details $(COV_REPORT) -e $(TESTS_DIR)/* $(OBJ_DIRS)
	@open $(COV_REPORT)

build: $(BUILD_FILE) 

$(BUILD_FILE): $(OBJS)
	@ar -rc $@ $^
	@ranlib $@

# Compile object files for static library
obj/%.o: %.c $(SRCS_H)
	@mkdir -p $(OBJ_DIRS)
	@$(CC) $(FLAGS) $(INC_FLAGS) -c $< -o $@

static_check:
	-$(CPPC) $(ALL_C)

clean:
	-@rm -rf $(TEST_EXEC) \
             obj \
             $(BUILD_FILE) \
             $(COV_DIR) \
             *.dSYM \
             *.gcda *.gcno
