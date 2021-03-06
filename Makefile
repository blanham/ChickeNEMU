CC=gcc

SOURCES=audio.c video.c util.c blip-buf/blip_buf.c 
EXECUTABLE=libchicken.a

OBJDIR = obj
OBJECTS=$(addprefix $(OBJDIR)/,$(SOURCES:.c=.o) )

CFLAGS = -fPIC -Wall -std=gnu99 
SDLFLAGS=`sdl-config --cflags --libs`

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
SDLFLAGS +=  -framework OpenGL -framework Cocoa 
CFLAGS +=  
endif


all: $(SOURCES) $(EXECUTABLE)

#.c.o:
#	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR) obj/%.o: %.c 
	$(CC) -c $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	libtool -o $(EXECUTABLE) -static $(OBJECTS)
#	$(CC) $(OBJECTS) $(SDLFLAGS) -o $@

test:
	$(CC) -c $(CFLAGS) main.c -o main.o;\
	$(CC)  $(CFLAGS) -lz libchicken.a main.o -o test


depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend

clean:
	rm -rf *.o $(EXECUTABLE)
