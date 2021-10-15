TARGET=TEA

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    main.o    save.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
save.o: src/save.c src/save.h
	$(CC) -c src/save.c

main.o: src/main.c src/save.h
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o
		    
clean:
	rm -f *.o $(TARGET)
