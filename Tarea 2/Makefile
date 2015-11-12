CC=gcc
LDFLAGS=
CFLAGS=-std=c99
DEPS = MemMgr.c test.c BTree.c EHash.c LHash.c
OBJ = main.o
ODIR=..
SRCDIR=src

main: $(SRCDIR)/$(OBJ)
	$(CC) -o $@ $^ $(addprefix $(SRCDIR)/,$(DEPS)) $(CFLAGS) $(LDFLAGS);
	
clean:
	rm main
	find . -type f -name '*.bin' -delete
	find . -type f -name '*.o' -delete
