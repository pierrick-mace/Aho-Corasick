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

ac-matrice : main-ac.o ac.o matriceTrie.o
	$(CC) $^ $(LDFLAGS) -o $@

ac-hachage : main-ac.o ac.o tableTrie.o
	$(CC) $^ $(LDFLAGS) -o $@

main-ac.o : main-ac.c
	$(CC) -c $(CFLAGS) $^ -o $@

ac.o : ac.c
	$(CC) -c $(CFLAGS) $^ -o $@

matriceTrie.o : matriceTrie.c
	$(CC) -c $(CFLAGS) $^ -o $@

tableTrie.o : tableTrie.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf */*.o gen_texte gen_mots
