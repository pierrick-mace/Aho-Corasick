#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:../4/

SHELL= /bin/bash
prefix= .
exec_prefix= $(prefix)
bindir= $(prefix)/bin
libdir= $(prefix)/lib
MKDIR= mkdir
RM= rm
CC= gcc
CFLAGS= -pedantic -Wconversion -Wextra -Werror -Wall -std=c11 -D_XOPEN_SOURCE=700
LDFLAGS= 
LDLIBS= libsearch.a
OBJECTS= searchTest

all : $(OBJECTS)

searchTest : searchTest.o libsearch.a
	$(CC) $< $(LDFLAGS) -o $@ $(LDLIBS)

searchTest.o : searchTest.c
	$(CC) -c $(CFLAGS) $^ -o $@

libsearch.a : libsearch.o search.h
	ar cr $@ $<
	ranlib $@

libsearch.o : search.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean :
	$(RM) -f *.a *.so *.o $(OBJECTS)
