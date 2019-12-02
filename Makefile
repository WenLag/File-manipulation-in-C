CC=gcc
CFLAGS=-I.
DEPS = p1.h
OBJ = subProject1-1.c
OBJ2 = subProject1-2.c
OBJ3 = subProject1-3.c


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


sub_project1-1: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

sub_project1-2: $(OBJ2)
		$(CC) -o $@ $^ $(CFLAGS)

sub_project1-3: $(OBJ3)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm sub_project1-1
	rm sub_project1-2
