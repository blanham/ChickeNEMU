CC=gcc
SOURCES=video.c util.c blip-buf/blip_buf.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=libchicken.a

CFLAGS = -fPIC -c -Wall -std=gnu99
SDLFLAGS=`sdl-config --cflags --libs`

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
SDLFLAGS += -arch i386 -framework OpenGL -framework Cocoa 
CFLAGS += -arch i386
endif


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	libtool -o $(EXECUTABLE) -static $(OBJECTS)
#	$(CC) $(OBJECTS) $(SDLFLAGS) -o $@
	

.c.o:
	$(CC) $(CFLAGS) $< -o $@

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend

clean:
	rm -rf *.o $(EXECUTABLE)
