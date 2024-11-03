CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -g
LFLAGS = 
EXEC = xd 
HEADERS = 

all: $(EXEC) tests

tests: runner.sh
	./runner.sh
##############################################################################################
xd: xd.o 
	$(CC) -o $@ $^

###############################################################################################

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]


.PHONY: all clean format tests test_functionality


