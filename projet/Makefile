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

ac-matrice: main.o ac.o transition_matrix_trie.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS)

ac-hachage: main.o ac.o hashtable_trie.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)

ac.o: aho-corasick/ac.c
	$(CC) -o $@ -c $< $(CFLAGS)

queue.o: queue/queue.c queue/queue.h
	$(CC) -o $@ -c $< $(CFLAGS)

transition_matrix_trie.o: trie/transition_matrix_trie.c
	$(CC) -o $@ -c $< $(CFLAGS)

hashtable_trie.o: trie/hashtable_trie.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o *.gch vgcore.* genere-texte genere-mots ac-matrice ac-hachage texte3.txt mots3.txt res-ac-hachage res-ac-matrice
