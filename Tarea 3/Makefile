CC=gcc
LDFLAGS=
CFLAGS=-std=c99 -g
DEPS = #BST.c AVL.c #STree.c VEB.c
OBJ = main.o
ODIR=..
SRCDIR=src

main: $(SRCDIR)/$(OBJ)
	$(CC) -o $@ $^ $(addprefix $(SRCDIR)/,$(DEPS)) $(CFLAGS) $(LDFLAGS);

clean:
	find . -type f -name '*.bin' -delete
	find . -type f -name '*.o' -delete
	rm main
