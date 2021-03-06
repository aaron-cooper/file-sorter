CC=g++
CFLAGS=-g -std=c++17 -Wall
LIBFLAG=-lstdc++fs
INCFLAG=-I./

OBJS=FileSorter.o
INCLUDES=$(subst .o,.hpp,$(OBJS))

fileSorter: $(OBJS) main.cpp
	$(CC) $(CFLAGS) $(INCFLAG) $^ -o $@ $(LIBFLAG)

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $(INCFLAG) -c -o $@ $< $(LIBFLAG)

clean:
	rm *.o fileSorter


.PHONY: clean