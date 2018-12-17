#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "trie.h"

#define LOAD_FACTOR 0.75
/* taille fixe pour le tableau car aucune info sur sa taille dans la structure
   struct _trie */
#define TABLE_SIZE(maxNode) (size_t)(((maxNode) - 1) / LOAD_FACTOR + 1)

static void _disposeTrie(struct _trie** trie);
static size_t _hashFunc(int node_p, unsigned char letter);
static int _nextState(struct _trie *trie, int node, unsigned char letter);
static int _addTransition(struct _trie *trie, int startNode,
        unsigned char letter, int targetNode);
void _printTableHealth(struct _trie *trie);

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
    
    size_t tableSize = TABLE_SIZE(maxNode);
    //printf("tableSize=%lu\n", tableSize);     /*---!!!debug!!!---*/
    newTrie -> transition = malloc(tableSize * sizeof *newTrie -> transition);
    if (newTrie -> transition == NULL) {
        goto error;
    }
    for (List *t = newTrie -> transition;
            t < newTrie -> transition + tableSize; ++t) {
        *t = NULL;
    }
    
    newTrie -> finite = malloc((size_t)maxNode * sizeof (*newTrie -> finite));
    if (newTrie -> finite == NULL) {
        goto error;
    }
    for (size_t* p = newTrie -> finite; p < newTrie -> finite + maxNode; ++p) {
        *p = 0;
    }
    
    goto success;
    error:
    _disposeTrie(&newTrie);
    success:
    return newTrie;
}

size_t sizeTrie(Trie trie) {
    return (size_t) trie -> nextNode;
}

int nextTrie(Trie trie, int node, unsigned char letter) {
    return _nextState(trie, node, letter);
}

size_t nbOccTrie(Trie trie, int node) {
    return trie -> finite[node];
}

void addOccTrie(Trie trie, int node, size_t nbOcc) {
    trie -> finite[node] += nbOcc;
}

void createInitialLoopTrie(Trie trie) {
    for (size_t c = 0; c <= UCHAR_MAX; c++) {
        if (_nextState(trie, 0, (unsigned char) c) == -1) {
            _addTransition(trie, 0, (unsigned char) c, 0);
        }
    }
}

void insertInTrie(Trie trie, unsigned char *w) {
    struct _trie *t = trie;
    int old_state = 0;
    int curr_state = 0;
    unsigned char *p = w;
    
    // recherche du plus long préfixe de w deja present dans le trie
    while (*p != '\0' && curr_state != -1) {
        old_state = curr_state;
        curr_state = _nextState(trie, curr_state, *p);
        ++p;
    }
    // si w n'est pas un préfixe ajouter les noeud
    if (curr_state == -1) {
        curr_state = old_state;
        --p;
        if (strlen((char*)p) > (size_t)(t -> maxNode - t -> nextNode)) {
            printf("insertion impossible: dépassement du nombre maximum"
                    " de noeud\n");
            return;
        }
        while (*p != '\0') {
            _addTransition(t, curr_state, *p, t -> nextNode);
            curr_state = t -> nextNode;
            t -> nextNode++;
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
        curr_state = _nextState(t, curr_state, *p);
        ++p;
    }
    return curr_state != -1 && t -> finite[curr_state] > 0;
}

void disposeTrie(Trie *trie) {
    _disposeTrie(trie);
}

static void _disposeTrie(struct _trie** trie) {
    if (*trie != NULL) {
        size_t tableSize = TABLE_SIZE((*trie) -> maxNode);
        for (List *t = (*trie) -> transition;
                t < (*trie) -> transition + tableSize; ++t) {
            while (*t != NULL) {
                struct _list *tmp = *t;
                *t = (*t) -> next;
                free(tmp);
            }
        }
        free((*trie) -> transition);
        free((*trie) -> finite);
        free(*trie);
        *trie = NULL;
    }
}

static inline size_t _hashFunc(int node, unsigned char letter) {
    return (size_t)node * ((size_t)UCHAR_MAX + 1) + (size_t)letter;
}

// renvoie le prochain noeud du trie trie à partir du noeud node par la lettre
// letter. renvoie -1 si la transition n'est pas dans la table
static int _nextState(struct _trie *trie, int node, unsigned char letter) {
    size_t index = _hashFunc(node, letter) % TABLE_SIZE(trie -> maxNode);
    int next = -1;
    struct _list *t = trie -> transition[index];
    while (t != NULL && next == -1) {
        if (t -> startNode == node && t -> letter == letter) {
            next = t -> targetNode;
        }
        t = t -> next;
    }
    
    return next;
}

// ajoute une transition (startNode, letter, targetNode) dans la table de
// transitions de trie
// renvoie 0 en cas de succès et -1 sinon
static int _addTransition(struct _trie *trie, int startNode,
        unsigned char letter, int targetNode) {
    struct _list *newTransition = malloc(sizeof *newTransition);
    if (newTransition == NULL) {
        return -1;
    }
    newTransition -> startNode = startNode;
    newTransition -> targetNode = targetNode;
    newTransition -> letter = letter;
    
    size_t tableSize = TABLE_SIZE(trie -> maxNode);
    size_t index = _hashFunc(startNode, letter) % tableSize;
    newTransition -> next = trie -> transition[index];
    trie -> transition[index] = newTransition;
    //_printTableHealth(trie);    /*---!!!debug!!!---*/
    return 0;
}

void _printTableHealth(struct _trie *trie) {
    size_t tableSize = TABLE_SIZE(trie -> maxNode);
    
    size_t longestList = 0;
    size_t count = 0;
    for (struct _list **p = trie -> transition;
            p < trie -> transition + tableSize; ++p) {
        size_t len = 0;
        for (struct _list *q = *p; q != NULL; q = q -> next) {
            count++;
            len++;
        }
        if (len > longestList) {
            longestList = len;
        }
    }

    double loadFactor = ((double)count) / (double) tableSize;

    printf("table size : %lu\n"
           "load factor : %lf\n"
           "load factor max : %lf\n"
           "depth : %lu\n",
           tableSize,
           loadFactor,
           LOAD_FACTOR,
           longestList);
}
