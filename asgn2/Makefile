CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -g
LFLAGS = 
EXEC = hangman 
HEADERS = hangman_helpers.h

all: $(EXEC)

$(EXEC): hangman.o hangman_helpers.o
	$(CC) $^ $(LFLAGS) -o  $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

##############################################################################################
tests: test_functionality test_helpers

test_functionality: test_functionality.sh
	./test_functionality.sh

test_helpers: test_helpers.o hangman_helpers.o
	$(CC) test_helpers.o hangman_helpers.o -o test_helpers
	./test_helpers

###############################################################################################

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]


.PHONY: all clean format tests test_helpers test_functionality


