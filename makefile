.POSIX:

CC=gcc

COMPONENTS = size write

all: image-writer

main.o: main.c size.h write.h
size.o: size.c size.h
write.o: write.c write.h

image-writer: $(COMPONENTS:=.o) $(COMPONENTS:=.h) main.o
	$(CC) -o $@ $(CFLAGS) main.o $(COMPONENTS:=.o) $(LDFLAGS)
