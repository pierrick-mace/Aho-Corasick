CC=gcc
CFLAGS= -std=c11 -pedantic -Wall -Wextra -Wconversion -Werror -g
LDFLAGS=

all: gen_texte gen_mots ac-matrice ac-hachage

gen_texte: gen_texte.o
	$(CC) -o $@ $^ $(LDFLAGS)

gen_texte.o: gen_texte.c gen_texte.h
	$(CC) -o $@ -c $< $(CFLAGS)

gen_mots: gen_mots.o
	$(CC) -o $@ $^ $(LDFLAGS)

gen_mots.o: gen_mots.c gen_mots.h gen_texte.h
	$(CC) -o $@ -c $< $(CFLAGS)

ac-matrice: main-ac.o ac.o matriceTrie.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS)

ac-hachage: main-ac.o ac.o tableTrie.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS)

main-ac.o: main-ac.c
	$(CC) -o $@ -c $< $(CFLAGS)

ac.o: ac.c
	$(CC) -o $@ -c $< $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -o $@ -c $< $(CFLAGS)

matriceTrie.o: matriceTrie.c
	$(CC) -o $@ -c $< $(CFLAGS)

tableTrie.o: tableTrie.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o gen_texte gen_mots ac-matrice ac-hachage texte3.txt mots3.txt res-ac-hachage res-ac-matrice
