CFLAGS=--std=c17 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
BUILDDIR=build
SRCDIR=src
CC=gcc

all: $(BUILDDIR)/main.o $(BUILDDIR)/bmp.o $(BUILDDIR)/image.o $(BUILDDIR)/sepia-impl.o $(BUILDDIR)/utils.o
	$(CC) -o $(BUILDDIR)/main $^

build:
	mkdir -p $(BUILDDIR)


$(BUILDDIR)/main.o: $(SRCDIR)/main.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/bmp.o: $(SRCDIR)/bmp.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/image.o: $(SRCDIR)/image.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/utils.o: $(SRCDIR)/utils.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/sepia-impl.o: $(SRCDIR)/sepia-impl.c build
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(BUILDDIR)
