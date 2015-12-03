CC=gcc
LDFLAGS=
CFLAGS=-std=c99
DEPS = ABB.c AVL.c STree.c VEB.c
OBJ = main.o
ODIR=..
SRCDIR=src

main: $(SRCDIR)/$(OBJ)
	$(CC) -o $@ $^ $(addprefix $(SRCDIR)/,$(DEPS)) $(CFLAGS) $(LDFLAGS);
	
clean:
	rm main
	find . -type f -name '*.bin' -delete
	find . -type f -name '*.o' -delete
