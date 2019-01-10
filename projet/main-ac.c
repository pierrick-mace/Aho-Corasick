// #define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "trie.h"
#include "ac.h"

#define BUFFSIZE_INIT 64

static int insertWordsInTrie(Trie trie, FILE *file);
int _readLine(FILE *file, char **buff, size_t *buffSize);
static int getFileSize(FILE *file);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "[USAGE]: %s words text\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *words = fopen(argv[1], "r");
    if (words == NULL) {
        fprintf(stderr, "Error: failed to open file %s", argv[1]);
        return EXIT_FAILURE;
    }

    int size = getFileSize(words);

    Trie trie = createTrie(size);
    if (trie == NULL) {
        fclose(words);
        fprintf(stderr, "Error: couldn't create trie\n");
        return EXIT_FAILURE;
    }

    if (insertWordsInTrie(trie, words) == -1) {
        freeTrie(trie);
        fclose(words);
        fprintf(stderr, "erreur lors de l'insertion des mots dans le Trie\n");
        return EXIT_FAILURE;
    }

    fclose(words);

    AC ac = createAC(trie);
    if (ac == NULL) {
        freeTrie(trie);
        fprintf(stderr, "erreur lors de la préparation de Aho-Corasick\n");
        return EXIT_FAILURE;
    }

    FILE *texte = fopen(argv[2], "r");
    if (texte == NULL) {
        freeTrie(trie);
        freeAC(ac);
        fprintf(stderr, "impossible d'ouvrir le fichier \"%s\""
            " en lecture\n", argv[2]);
        return EXIT_FAILURE;
    }

    printf("%lu\n", getOccurencesAC(ac, texte));

    fclose(texte);
    freeTrie(trie);
    freeAC(ac);
    return EXIT_SUCCESS;
}

static int insertWordsInTrie(Trie trie, FILE *file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
      if ((line)[read - 1] == '\n') {
          (line)[read - 1] = '\0';
          --read;
      }

      insertInTrie(trie, (unsigned char *) line);
    }

    return 0;
}

static int getFileSize(FILE *file) {
  if (file == NULL) {
    return -1;
  }

  fseek(file, 0, SEEK_END);
  int size = (int) ftell(file);
  rewind(file);

  return size;
}
