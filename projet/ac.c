#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "queue.h"
#include "ac.h"

static void complete(AC ac);

AC createAC(Trie trie) {
  AC ac = (AC) malloc((sizeof *ac) + sizeTrie(trie) * (sizeof (size_t)));

  if (ac == NULL) {
    return NULL;
  }

  initializeTrie(trie);
  ac -> trie = trie;
  complete(ac);
  return ac;
}

size_t getOccurencesAC(AC ac, FILE *file) {
  size_t occ = 0;
  int node = 0;

  int c;
  while ((c = fgetc(file)) != EOF) {
    while (nextTrie(ac -> trie, node, (unsigned char) c) == -1) {
      node = ac -> sup[node];
    }

    node = nextTrie(ac -> trie, node, (unsigned char) c);
    occ += getOccurencesTrie(ac -> trie, node);
  }

  return occ;
}

static void complete(AC ac) {
  Queue f = newQueue(sizeTrie(ac -> trie));
  if (f == NULL) {
    freeAC(ac);
    return;
  }

  for (size_t a = 0; a <= UCHAR_MAX; a++) {
    int p = nextTrie(ac -> trie, 0, (unsigned char) a);
    if (p != 0) {
      enQueue(f, (void*) (uintptr_t) p);
      ac -> sup[p] = 0;
    }
  }

  while (!isQueueEmpty(f)) {
    int r = (int) ((long) deQueue(f));

    for (size_t a = 0; a <= UCHAR_MAX; a++) {
      int p = nextTrie(ac -> trie, r, (unsigned char) a);

      if (p != -1) {
        enQueue(f, (void *) (uintptr_t) p);
        int s = ac -> sup[r];

        while (nextTrie(ac -> trie, s, (unsigned char) a) == -1) {
          s = ac -> sup[s];
        }

        ac -> sup[p] = nextTrie(ac -> trie, s, (unsigned char) a);

        addOccurencesTrie(ac -> trie, p, getOccurencesTrie(ac -> trie, ac -> sup[p]));
      }
    }
  }

  freeQueue(f);
}

void freeAC(AC ac) {
  free(ac);
  ac = NULL;
}
