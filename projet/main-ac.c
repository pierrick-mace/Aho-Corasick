#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "ac.h"

#define BUFFSIZE_INIT 64

int _insertWords(Trie trie, FILE *file);
int _readLine(FILE *file, char **buff, size_t *buffSize);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s mots.txt texte.txt\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *mots = fopen(argv[1], "r");
    if (mots == NULL) {
        fprintf(stderr, "impossible d'ouvrir le fichier \"%s\""
            " en lecture\n", argv[1]);
        return EXIT_FAILURE;
    }

    fseek(mots, 0, SEEK_END);
    int taille_mots = (int) ftell(mots);
    rewind(mots);

    Trie trie = createTrie(taille_mots);
    if (trie == NULL) {
        fclose(mots);
        fprintf(stderr, "erreur lors de la création du Trie\n");
        return EXIT_FAILURE;
    }

    if (_insertWords(trie, mots) == -1) {
        disposeTrie(&trie);
        fclose(mots);
        fprintf(stderr, "erreur lors de l'insertion des mots dans le Trie\n");
        return EXIT_FAILURE;
    }

    fclose(mots);

    AC ac = newAC(trie);
    if (ac == NULL) {
        disposeTrie(&trie);
        fprintf(stderr, "erreur lors de la préparation de Aho-Corasick\n");
        return EXIT_FAILURE;
    }

    FILE *texte = fopen(argv[2], "r");
    if (mots == NULL) {
        disposeTrie(&trie);
        disposeAC(&ac);
        fprintf(stderr, "impossible d'ouvrir le fichier \"%s\""
            " en lecture\n", argv[2]);
        return EXIT_FAILURE;
    }

    printf("%lu\n", nbOccAC(ac, texte));

    fclose(texte);
    disposeTrie(&trie);
    disposeAC(&ac);
    return EXIT_SUCCESS;
}

int _insertWords(Trie trie, FILE *file) {
    size_t buffSize = BUFFSIZE_INIT;
    char *buff = malloc(BUFFSIZE_INIT);
    if (buff == NULL) {
        return -1;
    }

    while (_readLine(file, &buff, &buffSize) != -1) {
        insertInTrie(trie, (unsigned char *) buff);
    }

    free(buff);
    return 0;
}

int _readLine(FILE *file, char **buff, size_t *buffSize) {
    char *s = fgets(*buff, (int) *buffSize, file);
    if (s == NULL) {
        return -1;
    }
    size_t len = strlen(*buff);
    char end = (*buff)[len - 1];
    while (end != '\n') {
        *buffSize *= 2;
        s = realloc(*buff, *buffSize);
        if (s == NULL) {
            return -1;
        }

        s = fgets(*buff + len, (int) *buffSize / 2, file);
        if (s == NULL) {
            return *(*buff + len) == '\0' ? -1 : 0;
        }

        len = strlen(*buff);
        end = (*buff)[len - 1];
    }

    (*buff)[len - 1] = '\0';

    return 0;
}
