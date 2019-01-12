// #define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "trie/trie.h"
#include "aho-corasick/ac.h"

static int insertWordsInTrie(Trie trie, FILE *file);
static int getFileSize(FILE *file);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "[USAGE]: %s words text\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *words = fopen(argv[1], "r");
    if (words == NULL) {
        fprintf(stderr, "Error: failed to open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    int size = getFileSize(words);
    if (size == -1) {
      fprintf(stderr, "Error: invalid file size\n");
      fclose(words);
      return EXIT_FAILURE;
    }

    Trie trie = createTrie(size);
    if (trie == NULL) {
        fclose(words);
        fprintf(stderr, "Error: couldn't create trie\n");
        return EXIT_FAILURE;
    }

    if (insertWordsInTrie(trie, words) == -1) {
        freeTrie(trie);
        fclose(words);
        fprintf(stderr, "Error: failed to insert words in trie\n");
        return EXIT_FAILURE;
    }

    fclose(words);

    AC ac = createAC(trie);
    if (ac == NULL) {
        freeTrie(trie);
        fprintf(stderr, "Error: failed to initialize Aho-Corasick automaton\n");
        return EXIT_FAILURE;
    }

    FILE *text = fopen(argv[2], "r");
    if (text == NULL) {
        freeTrie(trie);
        freeAC(ac);
        fprintf(stderr, "Error: failed to open file %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    printf("%lu\n", getOccurencesAC(ac, text));
    
    fclose(text);
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
      }

      insertInTrie(trie, (unsigned char *) line);
    }

    free(line);

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
