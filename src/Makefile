include config.mk

.PHONY: all clean test gcov_report static_check

all: test gcov_report

test: build $(TESTS_H)
	$(CC) $(FLAGS) $(INC_FLAGS) $(TEST_INC_FLAGS) $(TESTS) -L. -l$(BUILD_NAME) $(TEST_FLAGS) -o $(TEST_EXEC)
	-$(MEM_CHECK) ./$(TEST_EXEC)

gcov_report: $(COV_OBJS)
	@$(CC) $(FLAGS) $(INC_FLAGS) $(TEST_INC_FLAGS) $(COV_FLAGS) $(TESTS) $^ $(TEST_FLAGS) -o $(COV_EXEC)
	-@./$(COV_EXEC)
	@gcov -f $(COV_EXEC) -o $(COV_DIR)
	@lcov -q -c -d $(COV_DIR) -o $(COV_INFO) --exclude "$(TESTS_DIR)*"
	@genhtml -q $(COV_INFO) -o $(COV_DIR)
	@open $(COV_REPORT)

build: $(BUILD_FILE) 

$(BUILD_FILE): $(OBJS)
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
	-$(CPPC) $(ALL_C)

clean:
	-@rm -rf $(TEST_EXEC) \
             obj \
             $(BUILD_FILE) \
             $(COV_DIR) \
             *.dSYM \
             *.gcda *.gcno
