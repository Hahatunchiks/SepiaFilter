CFLAGS=--std=c17 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
BUILDDIR=build
SRCDIR=src
CC=gcc
ASM=nasm
ASMFLAGS=-felf64 -g

all: $(BUILDDIR)/main.o $(BUILDDIR)/bmp.o $(BUILDDIR)/image.o  $(BUILDDIR)/utils.o $(BUILDDIR)/sepia_asm.o $(BUILDDIR)/sepia-impl.o
	$(CC) -c $(CFLAGS) $(SRCDIR)/execution_time.c -o $(BUILDDIR)/execution_time.o
	$(CC) -o $(BUILDDIR)/execution_time  $(BUILDDIR)/execution_time.o
	$(CC) -o $(BUILDDIR)/main $^

build:
	mkdir -p $(BUILDDIR)


$(BUILDDIR)/sepia_asm.o: $(SRCDIR)/sepia_asm.asm build
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILDDIR)/main.o: $(SRCDIR)/main.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/bmp.o: $(SRCDIR)/bmp.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/image.o: $(SRCDIR)/image.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/utils.o: $(SRCDIR)/utils.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/sepia-impl.o: $(SRCDIR)/sepia-impl.c build $(BUILDDIR)/sepia_asm.o
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/execution_time: $(SRCDIR)/execution_time.c build
	$(CC) -c $(CFLAGS) $< -o $(BUILDDIR)/execution_time.o
	$(CC) -o $(BUILDDIR)/execution_time  $(BUILDDIR)/execution_time.o

clean:
	rm -rf $(BUILDDIR)
