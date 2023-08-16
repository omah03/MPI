PROG = ordering
OBJECTS = ordering.o
CC = mpicc
CFLAGS = -Wall -std=c11
CFLAGS += -I. # add the current directory to the include path

$(PROG): $(OBJECTS) # link the object files into a binary
	$(CC) $(CFLAGS) $^ -o $@

.Phone: run
run: $(PROG) # build and run the program
	mpirun -np 2 ./$(PROG)

$(OBJECTS): %.o: %.c  # compile the source files into object files
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean: # remove the object files and the binary
	rm -f $(OBJECTS) $(PROG)

