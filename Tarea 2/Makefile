CC=gcc
LDFLAGS=
CFLAGS=-std=c99
DEPS =
OBJ = main.o
ODIR=..
SRCDIR=src

main: $(SRCDIR)/$(OBJ)
	$(CC) -o $@ $^ $(addprefix $(SRCDIR)/,$(DEPS)) $(CFLAGS) $(LDFLAGS);
