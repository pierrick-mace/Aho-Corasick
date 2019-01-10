#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

#define LOAD_FACTOR 0.75
#define TABLE_SIZE(maxNode) (size_t) ((maxNode - 1) / LOAD_FACTOR + 1)

struct _list {
    int startNode;          /* etat de depart de la transition */
    int targetNode;         /* cible de la transition */
    unsigned char letter;   /* etiquette de la transition */
    struct _list *next;     /* maillon suivant */
};

typedef struct _list *List;

struct _trie {
    int maxNode;        /* Nombre maximal de noeuds du trie */
    int nextNode;       /* Indice du prochain noeud disponible */
    List *transition;   /* listes d’adjacence */
    size_t *finite;       /* etats terminaux */
};

static size_t hashfun(int node_p, unsigned char letter);
static int nextNode(Trie trie, int node, unsigned char letter);
static int newTransition(Trie trie, int startNode, unsigned char letter, int targetNode);
static int isInTrieEx(Trie trie, unsigned char *w, int currentNode);

Trie createTrie(int maxNode) {
    if (maxNode < 1) {
        return NULL;
    }

    Trie newTrie = (Trie) malloc(sizeof(*newTrie));
    if (newTrie == NULL) {
      fprintf(stderr, "Error: failed to allocate memory\n");
      return NULL;
    }

    newTrie -> nextNode = 1;
    newTrie -> maxNode = maxNode;

    List *transition = (List *) malloc((size_t) TABLE_SIZE(maxNode) * sizeof(*transition));
    if (transition == NULL) {
      freeTrie(newTrie);
      return NULL;
    }

    newTrie -> transition = transition;
    for (int i = 0; i < (int) TABLE_SIZE(maxNode); i++) {
      newTrie -> transition[i] = NULL;
    }

    size_t *finite = (size_t *) malloc((size_t) maxNode * sizeof(*finite));
    if (finite == NULL) {
      freeTrie(newTrie);
      return NULL;
    }

    newTrie -> finite = finite;
    memset(newTrie -> finite, 0, (size_t) maxNode * sizeof(newTrie -> finite));

    return newTrie;
}

void insertInTrie(Trie trie, unsigned char *w) {

    int currentNode = 0;
    int next = 0;
    unsigned char *word = w;

    while (*word != '\0' && next != -1) {
        currentNode = next;
        next = nextNode(trie, next, *word);
        word++;
    }

    if (next == -1) {
        next = currentNode;
        word--;

        if (strlen((const char *) word) > (size_t) (trie -> maxNode - trie -> nextNode)) {
            fprintf(stderr, "Error: Cannot insert word (max nodes reached)\n");
            return;
        }
        while (*word != '\0') {
            newTransition(trie, next, *word, trie -> nextNode);
            next = trie -> nextNode;
            trie -> nextNode++;
            word++;
        }
    }

    trie -> finite[next]++;
}

bool isInTrie(Trie trie, unsigned char *w) {
    if (trie == NULL || w == NULL) {
      return 0;
    }

    return isInTrieEx(trie, w, 0);
}

static int isInTrieEx(Trie trie, unsigned char *w, int currentNode) {
  if (strlen((const char *) w) == 0) {
    return 1;
  }

  int idx = (int) hashfun(currentNode, w[0]);
  int found = 0;
  int nextNode;

  List cell = trie -> transition[idx];

  while (cell != NULL) {
    if (cell -> startNode == currentNode && cell -> letter == w[0]) {
      found = 1;
      nextNode = cell -> targetNode;
    }

    cell = cell -> next;
  }

  if (!found) {
    return 0;
  }

  w = w + 1;

  return isInTrieEx(trie, w, nextNode);
}

// Utilities

static size_t hashfun(int node, unsigned char letter) {
      return (size_t) ((node * 33 + letter));
}

static int nextNode(Trie trie, int node, unsigned char letter) {
    size_t idx = hashfun(node, letter) % TABLE_SIZE(trie -> maxNode);
    int next = -1;

    List transition = trie -> transition[idx];

    while (transition != NULL && next == -1) {
        if (transition -> startNode == node && transition -> letter == letter) {
            next = transition -> targetNode;
        }

        transition = transition -> next;
    }

    return next;
}

static int newTransition(Trie trie, int startNode, unsigned char letter, int targetNode) {
    List transition = (List) malloc(sizeof *transition);

    if (transition == NULL) {
        return -1;
    }

    transition -> startNode = startNode;
    transition -> targetNode = targetNode;
    transition -> letter = letter;

    size_t idx = hashfun(startNode, letter) % TABLE_SIZE(trie -> maxNode);

    transition -> next = trie -> transition[idx];
    trie -> transition[idx] = transition;

    return 0;
}

size_t sizeTrie(Trie trie) {
    return (size_t) trie -> nextNode;
}

int nextTrie(Trie trie, int node, unsigned char letter) {
    return nextNode(trie, node, letter);
}

size_t getOccurencesTrie(Trie trie, int node) {
    return trie -> finite[node];
}

void addOccurencesTrie(Trie trie, int node, size_t occurences) {
    trie -> finite[node] += occurences;
}

void initializeTrie(Trie trie) {
    for (size_t c = 0; c <= UCHAR_MAX; c++) {
        if (nextNode(trie, 0, (unsigned char) c) == -1) {
            newTransition(trie, 0, (unsigned char) c, 0);
        }
    }
}

void freeTrie(Trie trie) {
  if (trie -> transition != NULL) {
    for (int i = 0; i < (int) (((trie -> maxNode) - 1) / LOAD_FACTOR + 1); i++) {
      List current = trie -> transition[i];

      while (current != NULL) {
        List tmp = current;
        current = current -> next;
        free(tmp);
      }
    }
  }

  free(trie -> transition);
  free(trie -> finite);
  free(trie);
}
