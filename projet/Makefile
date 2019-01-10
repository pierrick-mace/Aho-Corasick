CC=gcc
CFLAGS= -std=c11 -pedantic -Wall -Wextra -Wconversion -Werror -O2 -g
LDFLAGS=

all: genere-texte genere-mots ac-matrice ac-hachage

genere-texte: gen_texte.o
	$(CC) -o $@ $^ $(LDFLAGS)

gen_texte.o: generators/gen_texte.c generators/gen_texte.h
	$(CC) -o $@ -c $< $(CFLAGS)

genere-mots: gen_mots.o
	$(CC) -o $@ $^ $(LDFLAGS)

gen_mots.o: generators/gen_mots.c generators/gen_mots.h generators/gen_texte.h
	$(CC) -o $@ -c $< $(CFLAGS)

ac-matrice: main-ac.o ac.o matriceTrie.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS)

ac-hachage: main-ac.o ac.o tableTrie.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS)

main-ac.o: main-ac.c
	$(CC) -o $@ -c $< $(CFLAGS)

ac.o: aho-corasick/ac.c
	$(CC) -o $@ -c $< $(CFLAGS)

queue.o: utils/queue.c utils/queue.h
	$(CC) -o $@ -c $< $(CFLAGS)

matriceTrie.o: trie/matriceTrie.c
	$(CC) -o $@ -c $< $(CFLAGS)

tableTrie.o: trie/tableTrie.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o *.gch vgcore.* genere-texte genere-mots ac-matrice ac-hachage texte3.txt mots3.txt res-ac-hachage res-ac-matrice
