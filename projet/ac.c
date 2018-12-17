#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "ac.h"

// création du module intQueue
QUEUE(int)

struct _ac{
    Trie trie;
    int supp[];
};

void _completeAC(AC ac);

AC newAC(Trie trie) {
    struct _ac *ac = malloc((sizeof *ac) + sizeTrie(trie) * (sizeof (size_t)));
    if (ac == NULL) {
        return NULL;
    }
    createInitialLoopTrie(trie);
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
        nbOcc += nbOccTrie(ac -> trie, node);
    }
    return nbOcc;
}

void disposeAC(AC* ac) {
    free(*ac);
    *ac = NULL;
}

void _completeAC(AC ac) {
    // préparation de la file pour le parcours en largeur
    intQueue f = newintQueue(sizeTrie(ac -> trie));
    if (f == NULL) {
        disposeAC(&ac);
        return;
    }

    for (size_t a = 0; a <= UCHAR_MAX; a++) {
        int p = nextTrie(ac -> trie, 0, (unsigned char) a);
        if (p != 0) {
            addintQueue(f, p);
            ac -> supp[p] = 0;
        }
    }

    while (!isEmptyintQueue(f)) {
        int node = popintQueue(f);

        for (size_t a = 0; a <= UCHAR_MAX; a++) {
            int p = nextTrie(ac -> trie, node, (unsigned char) a);
            if (p != -1) {
                addintQueue(f, p);
                int s = ac -> supp[node];
                while (nextTrie(ac -> trie, s, (unsigned char) a) == -1) {
                    s = ac -> supp[s];
                }
                ac -> supp[p] = nextTrie(ac -> trie, s, (unsigned char) a);
                addOccTrie(ac -> trie, p, nbOccTrie(ac -> trie, ac -> supp[p]));
            }
        }
    }

    disposeintQueue(&f);
}
