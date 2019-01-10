#ifndef __AC_H__
#define __AC_H__

#include <stdio.h>
#include "trie.h"

typedef struct aho_corasick {
  Trie trie;
  int sup[];
} *AC;

AC createAC(Trie trie);
size_t getOccurencesAC(AC ac, FILE *file);
void freeAC(AC ac);

#endif
