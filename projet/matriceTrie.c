#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "trie.h"

struct _trie {
  int maxNode;        /* Nombre maximal de noeuds du trie     */
  int nextNode;       /* Indice du prochain noeud disponible  */
  int **transition;   /* matrice de transition                */
  size_t *finite;        /* etats terminaux                      */
};

void insertInTrieEx(Trie trie, unsigned char *w, int currentNode);
bool isInTrieEx(Trie trie, unsigned char *w, int currentNode);
int isLetterInNode(int **transition, unsigned char *letter, int currentNode, int maxNode, int *nextNode);
int isNodeFinal(Trie trie, int currentNode);

Trie createTrie(int maxNode) {
  if (maxNode < 1) {
    return NULL;
  }

  Trie newTrie = (Trie) malloc(sizeof(*newTrie));
  if (newTrie == NULL) {
    return NULL;
  }

  newTrie -> maxNode = maxNode;
  newTrie -> nextNode = 1;
  newTrie -> transition = NULL;
  newTrie -> finite = (size_t *) malloc((size_t) maxNode * sizeof(*(newTrie -> finite)));

  if (newTrie -> finite == NULL) {
    free(newTrie);
    return NULL;
  }

  for (int i = 0; i < maxNode; i++) {
    newTrie -> finite[i] = 0;
  }

  newTrie -> transition = (int **) malloc((size_t) maxNode * sizeof(*newTrie -> transition));
  if (newTrie -> transition == NULL) {
    free(newTrie -> finite);
    free(newTrie);
    return NULL;
  }

  int error = 0;

  for (int i = 0; i < maxNode; i++) {
    newTrie -> transition[i] = (int *) malloc((UCHAR_MAX + 1) * sizeof(newTrie -> transition[i]));

    if (newTrie -> transition[i] == NULL) {
      error = 1;
      break;
    }

    memset(newTrie -> transition[i], -1, (UCHAR_MAX + 1) * sizeof(newTrie -> transition[i]));
  }

  if (error) {
    fprintf(stderr, "Error while allocating dynamic memory.. (createTrie)\n");
    for (int i = 0; i < maxNode; i++) {
      free(newTrie -> transition[i]);
    }

    free(newTrie -> transition);
    free(newTrie -> finite);
    free(newTrie);

    return NULL;
  }

  return newTrie;
}

size_t sizeTrie(Trie trie) {
  size_t s = (size_t) trie -> nextNode;
  return s;
}

int nextTrie(Trie trie, int node, unsigned char letter) {
  return trie -> transition[node][letter];
}

size_t nbOccTrie(Trie trie, int node) {
  return trie -> finite[node];
}

void addOccTrie(Trie trie, int node, size_t nbOcc) {
  trie -> finite[node] += nbOcc;
}

void createInitialLoopTrie(Trie trie) {
  int *zeroState = trie -> transition[0];
  for (int *p = zeroState; p <= zeroState + UCHAR_MAX; p++) {
    if (*p == -1) {
      *p = 0;
    }
  }
}

void insertInTrie(Trie trie, unsigned char *w) {
  insertInTrieEx(trie, w, 0);
}

void insertInTrieEx(Trie trie, unsigned char *w, int currentNode) {
  if (trie == NULL || trie -> nextNode == trie -> maxNode || w == NULL || strlen((const char *) w) == 0) {
    return;
  }

  int nextNode;

  if (isLetterInNode(trie -> transition, w, currentNode, trie -> maxNode, &nextNode)) {
    w = w + 1;

    if (strlen((const char *) w) == 0) {
      trie -> finite[nextNode] = 1;
    }

    insertInTrieEx(trie, w, nextNode);
  } else {
    trie -> transition[currentNode][w[0]] = trie -> nextNode;
    nextNode = trie -> nextNode;
    trie -> nextNode++;

    w = w + 1;

    if (strlen((const char *) w) == 0) {
      trie -> finite[nextNode] = 1;
    }

    insertInTrieEx(trie, w, nextNode);
  }
}

int isLetterInNode(int **transition, unsigned char *letter, int currentNode, int maxNode, int *nextNode) {
  for (int i = 0; i < maxNode; i++) {
    if (transition[currentNode][*letter] != -1) {
      *nextNode = transition[currentNode][*letter];
      return 1;
    }
  }

  return 0;
}

bool isInTrie(Trie trie, unsigned char *w) {
  return isInTrieEx(trie, w, 0);
}

bool isInTrieEx(Trie trie, unsigned char *w, int currentNode) {
  if (trie == NULL || w == NULL) {
    return 0;
  }

  if (strlen((const char *) w) == 0) {
    if (isNodeFinal(trie, currentNode)) {
      return 1;
    } else {
      return 0;
    }
  }

  if (trie -> transition[currentNode][w[0]] != -1) {
    return isInTrieEx(trie, w + 1, trie -> transition[currentNode][w[0]]);
  } else {
    return 0;
  }
}

int isNodeFinal(Trie trie, int currentNode) {
  if (trie == NULL || currentNode > trie -> maxNode) {
    return 0;
  }

  return (int) trie -> finite[currentNode];
}

// TODO: replace disposeTrie with freeTrie in ac.c
void disposeTrie(Trie *trie) {
  freeTrie(*trie);
}

void freeTrie(Trie trie) {
  if (trie == NULL) {
    return;
  }

  for (int i = 0; i < trie -> maxNode; i++) {
    free(trie -> transition[i]);
  }

  free(trie -> transition);
  free(trie -> finite);

  free(trie);
}
