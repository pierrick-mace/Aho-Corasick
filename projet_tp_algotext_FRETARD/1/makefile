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

# table|matrice
struct=table

LDLIBS= lib$(struct)trie.a
OBJECTS= trieTest

all : $(OBJECTS)

trieTest : trieTest.o pref-suff-fact.o
	$(CC) $^ $(LDFLAGS) -o $@ $(LDLIBS)

trieTest.o : trieTest.c
	$(CC) -c $(CFLAGS) $^ -o $@

pref-suff-fact.o : pref-suff-fact.c
	$(CC) -c $(CFLAGS) $^ -o $@

libmatricetrie.a : libmatricetrie.o trie.h
	ar cr $@ $<
	ranlib $@

libtabletrie.a : libtabletrie.o trie.h
	ar cr $@ $<
	ranlib $@

libmatricetrie.o : matriceTrie.c
	$(CC) -c $(CFLAGS) $^ -o $@

libtabletrie.o : tableTrie.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean :
	$(RM) -f *.a *.so *.o $(OBJECTS)
