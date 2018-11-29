#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pref-suff-fact.h"

#define MAX_NODE 256

Trie prefixes(unsigned char *w) {
    Trie newTrie = createTrie(MAX_NODE);
    if (newTrie == NULL) {
        return NULL;
    }

    unsigned char wcpy[strlen((char*)w) + 1];
    strcpy((char*)wcpy, (char*)w);

    unsigned char *p = wcpy + strlen((char*)wcpy);
    // IB: *p == '\0'
    while (*wcpy != '\0') {
        printf("%s\n", wcpy);
        insertInTrie(newTrie, wcpy);
        --p;
        *p = '\0';
    }
    insertInTrie(newTrie, wcpy); // mot vide
    printf("%s\n", wcpy);

    return newTrie;
}

Trie suffixes(unsigned char *w) {
    Trie newTrie = createTrie(MAX_NODE);
    if (newTrie == NULL) {
        return NULL;
    }

    unsigned char *p = w;
    while (*p != '\0') {
        printf("%s\n", p);
        insertInTrie(newTrie, p);
        ++p;
    }
    insertInTrie(newTrie, p); // mot vide
    printf("%s\n", p);

    return newTrie;
}

Trie factors(unsigned char *w) {
    Trie newTrie = createTrie(MAX_NODE);
    
    unsigned char wcpy[strlen((char*)w) + 1];
    strcpy((char*)wcpy, (char*)w);

    unsigned char *p = wcpy + strlen((char*)wcpy);
    // IB: p[1] == '\0'
    // C(2, strlen(w) + 1)
    while (*wcpy != '\0') {
        for (unsigned char *q = wcpy; *q != '\0'; ++q) {
            printf("%s\n", q);
            insertInTrie(newTrie, q);
        }
        --p;
        *p = '\0';
    }
    insertInTrie(newTrie, wcpy); // mot vide
    printf("%s\n", wcpy);

    return newTrie;
}

