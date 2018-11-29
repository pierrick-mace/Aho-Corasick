#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:../4/

SHELL= /bin/bash
prefix= .
exec_prefix= $(prefix)
bindir= $(prefix)/bin
libdir= $(prefix)/lib
MKDIR= mkdir
RM= rm
CC= gcc
CFLAGS= -pedantic -Wconversion -Wextra -Werror -Wall -std=c11
LDFLAGS= 

LDLIBS= 
OBJECTS= genere-texte genere-mots 

all : $(OBJECTS)

genere-texte : genere-texte.o
	$(CC) $^ $(LDFLAGS) -o $@

genere-texte.o : genere-texte.c
	$(CC) -c $(CFLAGS) $^ -o $@

genere-mots : genere-mots.o
	$(CC) $^ $(LDFLAGS) -o $@

genere-mots.o : genere-mots.c
	$(CC) -c $(CFLAGS) $^ -o $@

ac-matrice : ac-matrice.o
	$(CC) $^ $(LDFLAGS) -o $@

ac-matrice.o : ac-matrice.c
	$(CC) -c $(CFLAGS) $^ -o $@

ac-hachage : ac-hachage.o
	$(CC) $^ $(LDFLAGS) -o $@

ac-hachage.o : ac-hachage.c
	$(CC) -c $(CFLAGS) $^ -o $@

matriceTrie.o : matriceTrie.c
	$(CC) -c $(CFLAGS) $^ -o $@

tableTrie.o : tableTrie.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean :
	$(RM) -f *.a *.so *.o $(OBJECTS)
