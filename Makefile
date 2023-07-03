SOURCES = $(shell find src -name '*.cc')
HEADERS = $(shell find include/ -name '*.h')
OBJECTS = $(SOURCES:.cc=.o)

CC = g++ -std=c++14 -stdlib=libc++ 
CFLAGS = -g -O3 -I ./include

.PHONY: main

main: main.cc $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@

clean:
	rm -rf main $(OBJECTS)

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@