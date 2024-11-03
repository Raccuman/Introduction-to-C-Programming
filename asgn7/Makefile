CC=clang
CFLAGS=-Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -g -gdwarf-4
OBJS=bitreader.o bitwriter.o node.o pq.o
HEAD=bitreader.h bitwriter.h node.h pq.h
EXEC=tsp  # change this later, this is the main execuatble

.PHONY: clean format scan-build

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

%.o: %.c $(HEADERS) # Might work, not sure what is should be, borrowed from other make file
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) *.o *.in bwtest brtest bitreader *.out pqtest testbr node huff dehuff


scan-build: clean
	scan-build --use-cc=clang make

format:
	clang-format -i -style=file *.[ch]

pqtest: node.o pq.o pqtest.o
	$(CC) $^ $(LFLAGS) -o $@

brtest: bitreader.o brtest.o 
	$(CC) $^ $(LFLAGS) -o $@

bwtest: bitwriter.o bwtest.o
	$(CC) $^ $(LFLAGS) -o $@

nodetest: node.o nodetest.o
	$(CC) $^ $(LFLAGS) -o $@

huff: node.o pq.o bitreader.o bitwriter.o huff.o #everything huff needs to run
	$(CC) $^ $(LFLAGS) -o $@

dehuff: node.o pq.o bitreader.o bitwriter.o dehuff.o #everything huff needs to run
	$(CC) $^ $(LFLAGS) -o $@






