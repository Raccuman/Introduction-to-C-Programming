CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -g
LFLAGS = -lm

# Define the main program target and the test program target
MAIN_TARGET = calc
TEST_TARGET = test

# Source files for the main program and the test program
MAIN_SRCS = calc.c stack.c mathlib.c operators.c
TEST_SRCS = tests.c stack.c mathlib.c operators.c

# Object files for the main program and the test program
MAIN_OBJS = $(MAIN_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Default target builds both the main program and the test program
all: $(MAIN_TARGET) $(TEST_TARGET)

# Rule to build the main program
$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(LFLAGS) -o $@ $^

# Rule to build the test program
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(LFLAGS) -o $@ $^

# Generic rule for compiling object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(MAIN_TARGET) $(TEST_TARGET) $(MAIN_OBJS) $(TEST_OBJS)

# Format source code
format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
