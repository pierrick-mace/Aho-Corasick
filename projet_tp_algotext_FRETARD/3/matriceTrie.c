#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> // strlen()
#include "trie.h"

static void _disposeTrie(struct _trie** trie);

struct _trie {
    int maxNode;        /* Nombre maximal de noeuds du trie     */
    int nextNode;       /* Indice du prochain noeud disponible  */
    int **transition;   /* matrice de transition                */
    int *finite;        /* etats terminaux                      */
    int *sup;           /* suppleance pour Aho-Corasick         */
};

Trie createTrie(int maxNode) {
    if (maxNode < 1) {
        return NULL;
    }
    struct _trie *newTrie = malloc(sizeof *newTrie);
    if (newTrie == NULL) {
        return NULL;
    }
    newTrie -> maxNode = maxNode;
    newTrie -> nextNode = 1;    // implicitement, la racine du trie est 0
    newTrie -> transition = NULL;
    newTrie -> finite = NULL;
    newTrie -> sup = NULL;
    
    newTrie -> transition = malloc(
        (size_t)maxNode  * sizeof (*newTrie -> transition));
    if (newTrie -> transition == NULL) {
        goto error;
    }
    for (int **p = newTrie -> transition; 
            p < newTrie -> transition + maxNode;
            ++p) {
        *p = malloc(((int)UCHAR_MAX + 1) * sizeof **p);
        if (*p == NULL) {
            goto error;
        }
        // initialisation de la matrice à -1 (aucune transition)
        for (int *q = *p; q <= *p + UCHAR_MAX; ++q) {
            *q = -1;
        }
    }
    
    newTrie -> finite = malloc((size_t)maxNode * sizeof (*newTrie -> finite));
    if (newTrie -> finite == NULL) {
        goto error;
    }
    for (int* p = newTrie -> finite; p < newTrie -> finite + maxNode; ++p) {
        *p = 0;
    }

    newTrie -> sup = malloc((size_t)maxNode * sizeof (*newTrie -> sup));
    if (newTrie -> sup == NULL) {
        goto error;
    }
        
    goto success;
    error:
    _disposeTrie(&newTrie);
    success:
    return newTrie;
}

void insertInTrie(Trie trie, unsigned char *w) {
    struct _trie *t = trie;
    int old_state = 0;
    int curr_state = 0;
    unsigned char *p = w;
    
    // recherche du plus long préfixe de w deja present dans le trie
    while (*p != '\0' && curr_state != -1) {
        old_state = curr_state;
        curr_state = t -> transition[curr_state][*p];
        ++p;
    }
    // si w n'est pas un préfixe ajouter les noeud
    if (curr_state == -1) {
        curr_state = old_state;
        --p;
        if (strlen((char*)p) > (size_t)(t -> maxNode - t -> nextNode)) {
            printf("insertion impossible: dépassement du nombre maximum de noeud\n");
            return;
        }
        while (*p != '\0') {
            t -> transition[curr_state][*p] = t -> nextNode;
            curr_state = t -> nextNode;
            t ->nextNode++;
            ++p;
        }
    }
    
    t -> finite[curr_state]++;
}

bool isInTrie(Trie trie, unsigned char *w) {
    struct _trie *t = trie;
    int curr_state = 0;
    unsigned char *p = w;
    
    while (*p != '\0' && curr_state != -1) {
        curr_state = t -> transition[curr_state][*p];
        ++p;
    }
    return curr_state != -1 && t -> finite[curr_state];
}

void disposeTrie(Trie *trie) {
    _disposeTrie(trie);
}

static void _disposeTrie(struct _trie** trie) {
    if (*trie != NULL) {
        for (int **p = (*trie) -> transition;
                p < (*trie) -> transition + (*trie) -> maxNode;
                ++p) {
            free(*p);
        }
        free((*trie) -> transition);
        free((*trie) -> finite);
        free((*trie) -> sup);
        free(*trie);
        *trie = NULL;
    }
}
