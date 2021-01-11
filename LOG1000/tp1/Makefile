
CC=gcc
EXEC=newton
LDFLAGS=-lm


# default command, builds an executable called "newton".
# executable can be called with ./newton 49 4
all: $(EXEC)

# link the object files into the executable.
# the -lm option is to tell the linker to include math libraries.
$(EXEC): main.o newton.o comparison.o
	$(CC) -o $@ $^ $(LDFLAGS)

# compile the main.c file into the main.o object file.
main.o: main.c newton.h comparison.h
	$(CC) -o $@ -c $<

# compile the newton.c file into the newton.o object file.
newton.o: newton.c newton.h
	$(CC) -o $@ -c $<

comparaison.o: comparaison.c
	$(CC) -o $@ -c $<
# remove the executable and intermediary object files.
clean:
	rm -rf newton main.o newton.o comparison.o install
install:
	mkdir install
	make
	cp newton install

