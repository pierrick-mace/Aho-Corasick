#ifndef AC_H
#define AC_H

#include <stdio.h>
#include "trie.h"

typedef struct ac {
  Trie trie;
  int supp[];
} *AC;

AC createAC(Trie trie);
size_t nbOccAC(AC ac, FILE *file);
void disposeAC(AC* ac);

#endif // AC_H
