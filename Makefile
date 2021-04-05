CC = gcc
CFLAGS = -c -Wall
LDFLAGS = 
SOURCES = main.c
HEADERS = symbol.h file_work.h
OBJECTS = $(SOURCES:.c=.o) $(HEADERS:.h=.o)
EXECUTABLE = archiver

all: $(SOURCES) $(HEADERS)  $(EXECUTABLES)
	
$(EXECUTABLES): $(OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@	

.h.o:
	$(CC) $(CFLAGS) $< -o $@ 

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean: 
	rm -rf *.o
