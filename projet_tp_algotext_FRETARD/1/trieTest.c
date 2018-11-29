#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "pref-suff-fact.h"

#define NB_INSERT 5
#define NB_TEST 11
#define MAX_WORD_SIZE 30
#define MAX_NODE 12

int main(void) {
    unsigned char insert[NB_INSERT][MAX_WORD_SIZE] =
        {"a", "ac", "aba", "bon", "bonjour"};
    unsigned char test[NB_TEST][MAX_WORD_SIZE] =
        {"", "a", "b", "aa", "ab", "ac", "aaa", "aba", "bonjour", "bon", "bonjou"};
    
    Trie trie = createTrie(MAX_NODE);
    if (trie == NULL) {
        printf("impossible de créer le trie\n");
        return EXIT_FAILURE;
    }
    
    for (int k = 0; k < NB_INSERT; ++k) {
        printf("insertion: \"%s\"\n", insert[k]);
        insertInTrie(trie, insert[k]);
    }
    
    for (int k = 0; k < NB_TEST; ++k) {
        printf("\"%s\" : %s\n", test[k], isInTrie(trie, test[k]) ? "oui" : "non");
    }

    printf("\npref:\n\n");
    Trie pref = prefixes((unsigned char*)"bonjour");
    printf("\nsuff:\n\n");
    Trie suff = suffixes((unsigned char*)"bonjour");
    printf("\nfact:\n\n");
    Trie fact = factors((unsigned char*)"bonjour");
    
    disposeTrie(&trie);
    disposeTrie(&pref);
    disposeTrie(&suff);
    disposeTrie(&fact);

    return EXIT_SUCCESS;
}
