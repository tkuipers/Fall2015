CC=gcc
CFLAGS=-c -Wall
LD=gcc
LDFLAGS=
LDLIBS=
SOURCES=signals.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=signalHandler

all: $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(LD) $(LDFLAGS) $(LDLIBS) $(OBJECTS) signalHandler.o -o $@

.c.o: $(SOURCES) 
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr $(EXECUTABLE) $(OBJECTS)
