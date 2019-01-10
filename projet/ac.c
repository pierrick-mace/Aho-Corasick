#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "queue.h"
#include "ac.h"

void _completeAC(AC ac);

AC createAC(Trie trie) {
  AC ac = (AC) malloc((sizeof *ac) + sizeTrie(trie) * (sizeof (size_t)));

  if (ac == NULL) {
    return NULL;
  }

  initializeTrie(trie);
  ac -> trie = trie;
  _completeAC(ac);
  return ac;
}

size_t nbOccAC(AC ac, FILE *file) {
  size_t nbOcc = 0;
  int node = 0;
  for (int c = fgetc(file); c != EOF; c = fgetc(file)) {
    while (nextTrie(ac -> trie, node, (unsigned char) c) == -1) {
      node = ac -> supp[node];
    }
    node = nextTrie(ac -> trie, node, (unsigned char) c);
    nbOcc += getOccurencesTrie(ac -> trie, node);
  }
  return nbOcc;
}

void disposeAC(AC* ac) {
  free(*ac);
  *ac = NULL;
}

void _completeAC(AC ac) {
  Queue f = newQueue(sizeTrie(ac -> trie));
  if (f == NULL) {
    disposeAC(&ac);
    return;
  }

  for (size_t a = 0; a <= UCHAR_MAX; a++) {
    int p = nextTrie(ac -> trie, 0, (unsigned char) a);
    if (p != 0) {
      enQueue(f, (void*)(uintptr_t)(p));
      ac -> supp[p] = 0;
    }
  }

  while (!isQueueEmpty(f)) {
    int r = (int) ((long) deQueue(f));

    for (size_t a = 0; a <= UCHAR_MAX; a++) {
      int p = nextTrie(ac -> trie, r, (unsigned char) a);

      if (p != -1) {
        enQueue(f, (void *) (uintptr_t) p);
        int s = ac -> supp[r];

        while (nextTrie(ac -> trie, s, (unsigned char) a) == -1) {
          s = ac -> supp[s];
        }

        ac -> supp[p] = nextTrie(ac -> trie, s, (unsigned char) a);

        addOccurencesTrie(ac -> trie, p, getOccurencesTrie(ac -> trie, ac -> supp[p]));
      }
    }
  }

  freeQueue(f);
}
